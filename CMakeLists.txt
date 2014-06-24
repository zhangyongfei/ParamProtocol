CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/CMakeUtility)
include(CMakeUtility)

Solution(ParamProtocol ON)

#设置依赖库
SET(LIB_LIST)
#AddLibsWin32(LIB_LIST
#usrsctplib
#ws2_32)
#AddLibsLinux(LIB_LIST
#usrsctplib
#pthread)

#AddDefsWin32(/wd4200)

AddHDir("$ENV{JAVA_HOME}/include"
"$ENV{JAVA_HOME}/include/win32"
${CMAKE_CURRENT_LIST_DIR}/ParamArgs 
${CMAKE_CURRENT_LIST_DIR}/Java)

AddSrcDir(SOURCE_LIST 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/ParamArgs
${CMAKE_CURRENT_LIST_DIR}/Java)

SharedLib(ParamProtocol
SOURCE_LIST
LIB_LIST)

SET(SOURCE_LIST)
AddSrc(SOURCE_LIST
test/c++/test.cpp)

AddLibsWin32(LIB_LIST
ParamProtocol)

AppPrj(testcpp
SOURCE_LIST
LIB_LIST)

