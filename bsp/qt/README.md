###准备

下载qt5：

	http://mirrors.ustc.edu.cn/qtproject/archive/qt/5.14/5.14.2/qt-opensource-windows-x86-5.14.2.exe

下载qtcreator：

    http://mirrors.ustc.edu.cn/qtproject/archive/qtcreator/4.11/4.11.2/qt-creator-opensource-windows-x86_64-4.11.2.exe


###编译

使用qtcreator打开bsp/qt/app/app.pro，在pro文件中选择对应引擎，例如：

	DEFINES += EVM_USE_PIKASCRIPT

###编译pikascript

进入bsp/qt/pikascript，运行before-build.bat。然后打开app工程，选择EVM_USE_PIKASCRIPT

