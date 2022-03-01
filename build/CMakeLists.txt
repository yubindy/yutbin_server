cmake_minimum_required(VERSION 1.0.1)
project(yutbin_server)
set(CMAKE_CXX_STANDARD 17)
link_libraries(-pthread)
SET(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS} -g)

aux_source_directory(../base WS_BASE)
# aux_source_directory(../src/http WS_HTTP)
# aux_source_directory(../src/net  WS_NET)


add_executable(yutbin_server
        # ../src/httpServer.cpp
        ../test/testlog.cpp
        ${WS_BASE}
)
