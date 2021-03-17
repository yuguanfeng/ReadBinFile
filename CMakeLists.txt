cmake_minimum_required(VERSION 3.5)
project(Test)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(CeleX_LIB CeleX)

include_directories(./include)
link_directories(./lib)

add_executable(Test ./src/readBinFile.cpp)

#specify the executable directory 
set_target_properties(Test PROPERTIES OUTPUT_NAME ../build/readBinFile)

target_link_libraries(Test ${OpenCV_LIBS})
target_link_libraries(Test ${CeleX_LIB})

#my_test
add_executable(my_Test ./src/my_readBinFile.cpp)

set_target_properties(my_Test PROPERTIES OUTPUT_NAME ../build/my_readBinFile)

target_link_libraries(my_Test ${OpenCV_LIBS})
target_link_libraries(my_Test ${CeleX_LIB})

