cmake_minimum_required(VERSION 3.5.0)
project(ImageSegmentationByThresholding VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ImageSegmentationByThresholding main.cpp)

target_link_libraries(ImageSegmentationByThresholding ${OpenCV_LIBS})
