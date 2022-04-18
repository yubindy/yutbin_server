cmake_minimum_required (VERSION 3.23.1)
project(yutbin_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -pthread")
link_libraries(-pthread)
SET(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS} -g)
set( CMAKE_BUILD_TYPE "Debug" )

# find_package(gtest REQUIRED )
# aux_source_directory(../src/http WS_HTTP)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include   #确定引入文件的工作目录
)
aux_source_directory(src/base  WS_BASE)
aux_source_directory(src/net  WS_NET)
add_executable(server
        test/testlog.cpp
        ${WS_BASE}
        ${WS_net}
)
