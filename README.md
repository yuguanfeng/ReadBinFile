# ReadBinFile

> Read bin file from CeleX5

阅读[CeleX5_MIPI](https://github.com/CelePixel/CeleX5-MIPI)后，由于原仓库涵盖太多，其中sample也分的有点乱，自己摘取了读取bin文件的代码，并重新整理，形成这个简单的仓库。

[introduction](#introduction)

[build and run](#build-and-run)

[issues](#issues)

## introduction

***该仓库包括[`build`](build)、[`include`](include)、[`lib`](lib)、[`src`](src)、CMakeLists和README。下面分别介绍各文件夹内容。***

 - [`build`](build)：编译文件夹，可执行文件所在文件夹。
 - [`include`](include)：与CeleX相关的头文件所在文件夹，可以从原仓库中**Samples/Samples/include**中复制。
 - [`lib`](lib)：与CeleX相关的库文件所在文件夹，可以从原仓库中**Samples/Samples/lib/linux/x64**中复制。
 - [`src`](src)：源代码所在文件夹。
 
 ## build and run
 
 1.git
 
  ```bash
  git clone https://github.com/yuguanfeng/ReadBinFile.git
  ```
 
 2.build 
 
  ```bash
  cd ReadBinFile/build
  cmake ..
  make
  ```
  
 3.run

 ```bash
 ./readBinile
 ```
 
## issues

1. 如果出现编译错误，检查lib中的libCeleX.so是否替换为符合本地opencv版本的，解决办法可以从原官方仓库的API源码重新编译生成libCeleX.so然后替换掉。
2. 注意修改src/readBinFile.cpp中的FPN和bin文件目录。
3. 在编写CMakeLists.txt过程中总结出：set_targrt_properties中OUTPUT_NAME ./build/readBinFile这里的./build/readBinFile是相对于cmake后生成的Makefile所在目录，而不是CMakeLists.txt所在目录。
