cmake_minimum_required(VERSION 3.2)

PROJECT(dmplugincpp)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMPLUGINCPP_VERSION_MAJOR "1")
SET(DMPLUGINCPP_VERSION_MINOR "0")
SET(DMPLUGINCPP_VERSION_PATCH "1")
SET(DMPLUGINCPP_VERSION "${DMPLUGINCPP_VERSION_MAJOR}.${DMPLUGINCPP_VERSION_MINOR}.${DMPLUGINCPP_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMPLUGINCPP_VERSION}")

OPTION(USE_DMPLUGINCPP "use dmplugincpp" OFF)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/dmplugincpp_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dmplugincpp_config.h)

LibImport("dmplugincpp_module" "src/dmplugincpp_module")
ExeImport("test" "dmplugincpp_module")

#ADD_CUSTOM_COMMAND(
#TARGET dmplugincpptest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmplugincpptest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmplugincpp
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMPLUGINCPP_LIBS "dmplugincpp")
#MARK_AS_ADVANCED(${DMPLUGINCPP_LIBS})