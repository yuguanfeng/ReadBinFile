# ReadBinFile

> Read bin file from CeleX5

阅读[CeleX5_MIPI](https://github.com/CelePixel/CeleX5-MIPI)后，由于原仓库涵盖太多，其中sample也分的有点乱，自己摘取了读取bin文件的代码，并重新整理，形成这个简单的仓库。

[Introduction](#introduction)

[Build and Run](#build-and-run)

[Issues](#issues)

## introduction

***该仓库包括[`build`](build)、[`include`](include)、[`lib`](lib)、[`src`](src)、CMakeLists和README。下面分别介绍各文件夹内容。***

 - [`build`](build)：编译文件夹，可执行文件所在文件夹。
 - [`include`](include)：与CeleX相关的头文件所在文件夹，可以从原仓库中**Samples/Samples/include**中复制。
 - [`lib`](lib)：与CeleX相关的库文件所在文件夹，可以从原仓库中**Samples/Samples/lib/linux/x64**中复制。
 - [`src`](src)：源代码所在文件夹。(其中readBinFile.cpp为原官方示例，my_readBinFile.cpp没有采用回调，看上去易懂些）
 
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
 ./readBinile //或者./my_readBinFile
 ```
 
## issues

1. 如果出现编译错误，检查lib中的libCeleX.so是否替换为符合本地opencv版本的，解决办法可以从原官方仓库的API源码重新编译生成libCeleX.so然后替换掉。
2. 注意修改src/readBinFile.cpp中的FPN和bin文件目录。
3. 在编写CMakeLists.txt过程中总结出：set_targrt_properties中OUTPUT_NAME ./build/readBinFile这里的./build/readBinFile是相对于cmake后生成的Makefile所在目录，而不是CMakeLists.txt所在目录。
4. 在反复阅读sample里所有示例的代码总结出：有两种方式获得传感器数据，一种直接法，一种回调。两者之间差别可以从GetLoopModeFrameBuffer(直接)与GetFrameBufferByCallback(回调)可以看出。个人觉得回调代码有点难懂，暂时也不知道回调有什么好处(求解答)。原readBinFile.cpp采用的是回调的方式，现自己写了个直接的my_readBinFile，代码逻辑较清晰点。