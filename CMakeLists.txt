CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/CMakeUtility)
include(CMakeUtility)

Solution(ParamProtocol ON)

#设置依赖库
AddLibsAndroid(LIB_LIST
stdc++
log)

AddHDir(
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/ParamArgs 
${CMAKE_CURRENT_LIST_DIR}/Java
)
AddHDirWin32(
"$ENV{JAVA_HOME}/include"
"$ENV{JAVA_HOME}/include/win32"
${CMAKE_CURRENT_LIST_DIR}/test/c++
)
AddHDirAndroid(
$ENV{ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/include/backward
$ENV{ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.8/include/backward
)

AddLibDirsWin32(${CMAKE_CURRENT_LIST_DIR}/test/c++)

AddSrcDir(SOURCE_LIST 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/ParamArgs
${CMAKE_CURRENT_LIST_DIR}/Java)

SharedLib(ParamProtocol
SOURCE_LIST
LIB_LIST)

SET(TEST_SOURCE_LIST 
${CMAKE_CURRENT_LIST_DIR}/test/c++/test.cpp
${CMAKE_CURRENT_LIST_DIR}/test/c++/TcpServer.cpp
${CMAKE_CURRENT_LIST_DIR}/test/c++/TcpServer.h
${CMAKE_CURRENT_LIST_DIR}/test/c++/SvrConnection.cpp
${CMAKE_CURRENT_LIST_DIR}/test/c++/SvrConnection.h)

AddLibsWin32(TEST_LIB_LIST
ParamProtocol
vJoyInterface
ws2_32
)

AppPrj(testcpp
TEST_SOURCE_LIST
TEST_LIB_LIST)

