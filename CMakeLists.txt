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
ExeImport("test" "dmplugincpp;${Boost_LIBRARIES}")
