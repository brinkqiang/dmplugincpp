cmake_minimum_required(VERSION 3.2)

PROJECT(dmmsgpack)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMMSGPACK_VERSION_MAJOR "1")
SET(DMMSGPACK_VERSION_MINOR "0")
SET(DMMSGPACK_VERSION_PATCH "1")
SET(DMMSGPACK_VERSION "${DMMSGPACK_VERSION_MAJOR}.${DMMSGPACK_VERSION_MINOR}.${DMMSGPACK_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMMSGPACK_VERSION}")

OPTION(USE_DMMSGPACK "use dmmsgpack" OFF)

LibImport("dmmsgpack" "src/dmmsgpack")
ExeImport("test" "dmmsgpack")

#ADD_CUSTOM_COMMAND(
#TARGET dmmsgpacktest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmmsgpacktest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmmsgpack
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMMSGPACK_LIBS "dmmsgpack")
#MARK_AS_ADVANCED(${DMMSGPACK_LIBS})