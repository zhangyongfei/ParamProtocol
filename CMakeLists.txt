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

#AddDefs("-DSCTP_DEBUG -DINET")

AddHDir(${CMAKE_CURRENT_LIST_DIR}/ParamArgs)

AddSrcDir(SOURCE_LIST 
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/ParamArgs)

StaticLib(ParamProtocol 
SOURCE_LIST
LIB_LIST)

