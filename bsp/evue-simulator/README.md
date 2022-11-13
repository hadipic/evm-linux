###准备

下载qt5：

	http://mirrors.ustc.edu.cn/qtproject/archive/qt/5.14/5.14.2/qt-opensource-windows-x86-5.14.2.exe

下载qtcreator：

    http://mirrors.ustc.edu.cn/qtproject/archive/qtcreator/4.11/4.11.2/qt-creator-opensource-windows-x86_64-4.11.2.exe


###编译

使用qtcreator打开bsp/evue-simulator/app/app.pro，在pro文件中选择对应引擎，例如：

	DEFINES += EVM_USE_PIKASCRIPT

###编译pikascript

进入bsp/evue-simulator/pikascript，运行before-build.bat。然后打开app工程，选择EVM_USE_PIKASCRIPT


###运行pikascript文件

进入bsp/evue-simulator/pikascript，编辑main.py文件。完成后运行rust-msc-lastest-win10.exe。
在qtcreator -> 项目 -> Run -> Command line arguments中输入main.py路径作为运行参数，并点击运行。

如果要运行字节码文件，在pikascript-api目录中找打main.py.o文件，并输入到运行参数中。

