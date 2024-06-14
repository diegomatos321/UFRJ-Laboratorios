cmake_minimum_required(VERSION 3.5.0)
project(ImageSegmentationByThresholding VERSION 0.1.0 LANGUAGES CXX)

find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

include_directories(${OpenCV_INCLUDE_DIRS})

qt_add_executable(ImageSegmentationByThresholding 
    MainWindow.cpp MainWindow.h ui_MainWindow.h
    main.cpp
)

target_link_libraries(ImageSegmentationByThresholding PRIVATE 
    ${OpenCV_LIBS} 
    Qt6::Core
    Qt6::Widgets 
    Qt6::Gui
)

set_target_properties(ImageSegmentationByThresholding PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)