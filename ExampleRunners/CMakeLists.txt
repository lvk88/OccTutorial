#OpenCASCADE tutorial by Laszlo Kudela
#November 2015

project(occtutorialrunners)

ADD_EXECUTABLE(runChapter1 runChapter1.cpp)
TARGET_LINK_LIBRARIES(runChapter1 chapter1runners chapter1 TKernel TKMath)
