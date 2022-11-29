## 什么是EVUE

EVUE（Embedded VUE），是一个面向嵌入式平台的VUE小程序开发框架。支持HTML、CSS、JS和Python等多种语言开发。
开发资料：https://www.yuque.com/bytecode/evue-doc

##  基于Pikascript的EVUE开发

PikaScript 是一个完全重写的超轻量级 python 引擎，零依赖，零配置，可以在 Flash ≤ 32KB，RAM≤ 4KB 的平台下运行(如 stm32g030c8 和 stm32f103c8)，极易部署和扩展，具有大量的中文文档和视频资料。
开发资料：https://gitee.com/Lyon1998/pikascript

针对小资源芯片场景，采用pikascript作为python引擎，用户可以在evue脚本内编写python代码。这样既满足用户能快速开发UI界面，同时也兼顾了芯片资源受限的场景。


## quickbc使用教程

quickbc是基于Python构建的一个在线编译工具，可以将EVUE脚本编译成可执行的pikascript的字节码文件。使用quickbc之前需完成以下步骤：
+ 安装python开发环境
+ 安装windows git工具
+ 在quickbc目录下打开git bash，终端输入python  tools/quickbc/quickbc.py  test/test.evue
+ 编译成功后，会在evue脚本文件目录下生成对应的test.evue.py.o文件