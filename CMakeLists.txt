cmake_minimum_required(VERSION 3.5)
project(metadataprovider.omniyon)
enable_language(CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

find_package(OmniPlayer REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/lib
                    ${OMNIPLAYER_INCLUDE_DIR}/..)

message(STATUS "include dir: ${OMNIPLAYER_INCLUDE_DIR}/..")
message(STATUS "build addon: ${BUILD_KODI_ADDON}")
set(KODI_INCLUDE_DIR ${OMNIPLAYER_INCLUDE_DIR})

set(DEPLIBS ${CURL_LIBRARIES})
set(METADATA_SOURCES src/client.cpp
                     src/utilities/CurlFile.cpp
                     src/utilities/StringUtils.cpp)
set(METADATA_HEADERS src/client.h
                     src/utilities/CurlFile.h
                     src/utilities/StringUtils.h)

build_addon(metadataprovider.omniyon METADATA DEPLIBS)

include(CPack)
