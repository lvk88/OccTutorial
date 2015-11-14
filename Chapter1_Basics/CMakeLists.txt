CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Chapter0)

ADD_EXECUTABLE(chapter1_1 chapter1_1.cpp)
TARGET_LINK_LIBRARIES(chapter1_1 TKernel TKMath)

ADD_EXECUTABLE(chapter1_2 chapter1_2.cpp)
TARGET_LINK_LIBRARIES(chapter1_2 TKernel TKMath)

ADD_EXECUTABLE(chapter1_2_exercise chapter1_2_exercise.cpp)
TARGET_LINK_LIBRARIES(chapter1_2_exercise TKernel TKMath)

ADD_CUSTOM_COMMAND(TARGET chapter1_2
		   POST_BUILD
		   COMMAND ${CMAKE_COMMAND} -E copy_directory
		   "${CMAKE_CURRENT_SOURCE_DIR}/python"
		   "${CMAKE_CURRENT_BINARY_DIR}")
