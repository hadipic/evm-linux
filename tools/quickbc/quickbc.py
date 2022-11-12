# -*- coding: utf-8 -*-
import os
import sys
import requests
import json
import logging
from logging.handlers import RotatingFileHandler
import os
import traceback
logPath = os.getcwd() + os.path.sep + "quickbclogs"
if not os.path.exists(logPath):
    os.makedirs(logPath)

fh = RotatingFileHandler("quickbclogs/quickbc.log", maxBytes=10 * 1024 * 1024, backupCount=100)
fh.setLevel(logging.DEBUG)
#log write in console
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
#log formatter
formatter = logging.Formatter(
    '%(asctime)s %(levelname)8s [%(filename)25s%(funcName)20s%(lineno)06s] %(message)s')
fh.setFormatter(formatter)
ch.setFormatter(formatter)

logger = logging.root
logger.setLevel(logging.INFO)
logger.addHandler(fh)
logger.addHandler(ch)

isDebug = False

def loadJson(path):
    if os.path.exists(path):
        with open(path, "r", encoding="utf-8") as f:
            cfg = json.load(f)
        return cfg
    else:
        return None

def compile(fpath):
    url = "http://qbc.evmiot.com:60066/compile"
        
    if os.path.exists("quickbc.json"):
        try:
            userInfo = loadJson("quickbc.json")
            if userInfo is None:
                logger.error("quickbc.json format error")
                return
            else:
                if not checkData(userInfo):
                    return

            filename = os.path.basename(fpath)
            with open(fpath, "r", encoding="utf-8") as f:
                content = f.read()
            data = {}
            data['username'] = userInfo['username']
            data['filename'] = filename
            data['key'] = userInfo['key']
            data['content'] = content
            mode = userInfo['mode']
            url = "%s/%s" % (url, mode)
            logger.info("start compile......")
            response = requests.post(url, json=data, timeout=100, stream=True)
            if 'filename' in response.headers:
                filename = response.headers['filename']
                result_path = os.path.abspath(os.sep.join([os.path.dirname(fpath), filename]))
                logger.info(result_path)
                with open(result_path, "wb") as f:
                    f.write(response.content)
                logger.info("compile [%s]-->[%s] successfully!" % (fpath, result_path))
            else:
                logger.info(response.text)
                logger.error("compile [%s] failed!" % (fpath))

        except Exception as e:
            logger.error("%s" % (traceback.format_exc(e)))
    else:
        logger.error("quickbc.json is not found!")


def main(fpath: str):
    if os.path.isfile(fpath):
        if fpath.endswith(".evue"):
            compile(fpath)
        else:
            logger.info("Please input the correct file [%s]: ['File is not support!']" % fpath)
    else:
        logger.info("Please input the correct file [%s]: ['File is not exists']" % fpath)

def checkData(data):
    if 'username' not in data:
        logger.error("quickbc.json field [username] is missing, Please add [username]!")
        return False
    elif 'key' not in data:
        logger.error("quickbc.json field [company] is missing, Please add [key]")
        return False
    elif 'mode' not in data:
        logger.error("quickbc.json field [mode] is missing, Please add [mode]")
        return False
    return True


if __name__ == "__main__":
    if sys.argv[1] in ["-h", "--help"]:
        print('''
usage:
    ./quickbc.exe xxx.evue
''')
    else:
        main(sys.argv[1])
            
