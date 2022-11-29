import os
import sys
import json

typedef = {}
type_count = 0
modules = {}

def checkReturn(signature):
    if signature[0] == 'b':
        return 'cffi_res.i32'
    elif signature[0] == 'i':
        return 'cffi_res.i32'
    elif signature[0] == 'l':
        return 'cffi_res.i64'
    elif signature[0] == 'd':
        return 'cffi_res.f64'
    elif signature[0] == 'f':
        return 'cffi_res.f32'
    elif signature[0] == 's':
        return 'cffi_res.s'
    elif signature[0] == 'p':
        return 'cffi_res.p'

def checkParam(index, signature):
    if signature[index] == 'b':
        return 'cffi_args[' + str(index) +'].i32'
    elif signature[index] == 'i':
        return 'cffi_args[' + str(index) +'].i32'
    elif signature[index] == 'l':
        return 'cffi_args[' + str(index) +'].i64'
    elif signature[index] == 'd':
        return 'cffi_args[' + str(index) +'].f64'
    elif signature[index] == 'f':
        return 'cffi_args[' + str(index) +'].f32'
    elif signature[index] == 's':
        return 'cffi_args[' + str(index) +'].s'
    elif signature[index] == 'p':
        return 'cffi_args[' + str(index) +'].p'

def compile(info):
    global type_count
    apis = info['apis']
    module_name = info['name']
    includes = info['includes']
    content = '//This is auto-generated file\n'
    content = content + "#ifdef CONFIG_EVM_MODULE_" + module_name.upper() + "\n\n"
    for item in includes:
        content = content + '#include "' + item + '"\n'  
    content = content + '#include "evm_module.h"\n'
    content = content + '\n'
    for item in apis:
        signature = item['signature']
        name = item['name']
        size = len(signature)
        param_signature = signature[1:size]
        content = content + 'static evm_val_t evm_module_' + module_name + '_' + name + '(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {\n'
        if signature[0] != 'v':
            content = content + '  evm_cffi_val_t cffi_res;\n'
        content = content + '  evm_cffi_val_t cffi_args[' + str(size - 1) + '];\n'
        content = content + '  evm_cffi_exec_param(e, cffi_args, "' + param_signature + '", argc, v);\n'
        if signature[0] != 'v':
            content = content + '  ' +  checkReturn(signature) + ' = ' + name + '('
        else:
            content = content + '  ' + name + '('
        if size - 1 > 0:
            for i in range(0, len(param_signature)):
                content = content + checkParam(i, param_signature) + ', '
            if len(param_signature) > 0:
                content = content[0: len(content) - 2]
        content = content + ');\n'
        if signature[0] != 'v':
            content = content + '  return evm_cffi_exec_ret(e, cffi_res, "' + signature + '");\n}\n\n'
        else:
            content = content + '  return EVM_UNDEFINED;\n}\n\n'

    content = content + '\nvoid evm_module_' + module_name + '(evm_t *e) {\n'
    content = content + '  evm_val_t obj = evm_object_create(e);\n'
    for item in apis:
        signature = item['signature']
        name = item['name']
        size = len(signature) - 1
        content = content + '  evm_prop_set(e, obj, "' + name + \
        '", evm_mk_native(e, evm_module_' + module_name + '_' + name + ', "' + name + '", ' + str(size) +'));\n'
    content = content + '  evm_module_add(e, "'+ module_name+'", obj);\n}\n'
    content = content + "#endif\n"
    modules.update({"name": name, "content": content})
    return (content, module_name)
    

def loadJson(path):
    if os.path.exists(path):
        with open(path, "r", encoding="utf-8") as f:
            cfg = json.load(f)
        return cfg
    else:
        return None

def loadFile(path):
    if path.endswith('.json'):
        info = loadJson(path)
        content = compile(info)
        root = os.path.dirname(path)
        name = 'evm_module_' + content[1] + '.c'
        with open(str(os.path.join(root, name)), "w", encoding="utf-8") as f:
            f.write(content[0])

def loadDir(path):
    for root, dirs, files in os.walk(path):
        for f in files:
            file_path = str(os.path.join(root, f))
            if file_path.endswith('.json'):
                info = loadJson(file_path)
                content = compile(info)
                name = 'evm_module_' + content[1] + '.c'
                with open(str(os.path.join(root, name)), "w", encoding="utf-8") as f:
                    f.write(content[0])
        

if __name__ == "__main__":
    if sys.argv[1] == '-f':
        loadFile(sys.argv[2])
    elif sys.argv[1] == '-d':
        loadDir(sys.argv[2])
    else:
        print('''
usage:
    python cffi.py <path>
''')
        