INCLUDEPATH += $$PWD/../pikascript/pikascript-core
INCLUDEPATH += $$PWD/../pikascript/pikascript-api

SOURCES += \
        $$PWD/../../../engines/pikascript/evm.c

SOURCES += \
    $$PWD/../pikascript/pikascript-api/__asset_pikaModules_py_a.c \
    $$PWD/../pikascript/pikascript-api/pikaScript.c \
    $$PWD/../pikascript/pikascript-api/__pikaBinding.c

SOURCES += \
    $$PWD/../pikascript/pikascript-core/BaseObj.c \
    $$PWD/../pikascript/pikascript-core/dataArg.c \
    $$PWD/../pikascript/pikascript-core/dataArgs.c \
    $$PWD/../pikascript/pikascript-core/dataLink.c \
    $$PWD/../pikascript/pikascript-core/dataLinkNode.c \
    $$PWD/../pikascript/pikascript-core/dataMemory.c \
    $$PWD/../pikascript/pikascript-core/dataQueue.c \
    $$PWD/../pikascript/pikascript-core/dataQueueObj.c \
    $$PWD/../pikascript/pikascript-core/dataStack.c \
    $$PWD/../pikascript/pikascript-core/dataString.c \
    $$PWD/../pikascript/pikascript-core/dataStrs.c \
    $$PWD/../pikascript/pikascript-core/PikaCompiler.c \
    $$PWD/../pikascript/pikascript-core/PikaObj.c \
    $$PWD/../pikascript/pikascript-core/PikaParser.c \
    $$PWD/../pikascript/pikascript-core/PikaPlatform.c \
    $$PWD/../pikascript/pikascript-core/PikaVM.c \
    $$PWD/../pikascript/pikascript-core/TinyObj.c

SOURCES += \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaDebuger_Debuger.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_ByteArray.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_Dict.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_FILEIO.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_List.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_String.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_Tuple.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdData_Utils.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdLib_MemChecker.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdLib_RangeObj.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdLib_StringObj.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdLib_SysObj.c \
    $$PWD/../pikascript/pikascript-lib/PikaStdLib/PikaStdTask_Task.c

