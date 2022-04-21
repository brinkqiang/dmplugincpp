cmake_minimum_required(VERSION 3.8)

SET(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../dmvcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

PROJECT(dmplugincpp)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ADD_DEFINITIONS(-DASIO_STANDALONE)

ModuleImport("dmrest_rpc" "thirdparty/dmrest_rpc")
ModuleImport("dmcinatra" "thirdparty/dmcinatra")

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

LibImport("dmplugincpp" "src/dmplugincpp")

IF(WIN32)
    ExeImport("test" "dmplugincpp;${Boost_LIBRARIES}")
ELSE(UNIX)
    find_library(LIB_STD_FS stdc++fs)
    IF(LIB_STD_FS_FOUND)
        ExeImport("test" "dmplugincpp;${Boost_LIBRARIES}")
    ELSE(LIB_STD_FS_FOUND)
        ExeImport("test" "dmplugincpp;${Boost_LIBRARIES};stdc++fs")
    ENDIF(LIB_STD_FS_FOUND)
ENDIF(WIN32)
