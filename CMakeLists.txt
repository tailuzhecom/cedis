cmake_minimum_required(VERSION 3.8)
project(cedis)

set(LINK_LIST boost_system pthread)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Connector.cpp Connector.h RWHandler.cpp RWHandler.h CedisClient.cpp CedisClient.h Parser.cpp Parser.h)
add_executable(cedis ${SOURCE_FILES})
target_link_libraries(cedis ${LINK_LIST})