CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(occtutorials)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

INCLUDE(cmake/CreateExecutable.cmake)
INCLUDE(cmake/CreateLibrary.cmake)

#Find opencascade libraries

FIND_PACKAGE(OCE REQUIRED)
INCLUDE_DIRECTORIES(${OCE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ENABLE_TESTING()

ADD_SUBDIRECTORY(Chapter0_Test)
ADD_SUBDIRECTORY(Chapter1_Basics)
ADD_SUBDIRECTORY(Chapter2_Geom)
ADD_SUBDIRECTORY(OtherExamples)
