cmake_minimum_required(VERSION 3.16) # Updated to a more recent version for better compatibility
project(ImageSegmentationByThresholding VERSION 0.1.0 LANGUAGES CXX)

# Ensure automoc, autorcc, and autouic are enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required packages
find_package(OpenCV REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

# Standard Qt setup function (only in recent Qt6 versions, ensure you have it)
qt_standard_project_setup()

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable and list all necessary sources
qt_add_executable(ImageSegmentationByThresholding 
    main.cpp
    MainWindow.cpp
    MainWindow.h
    ui_MainWindow.h
    Icons/icons.qrc
)

# Link the necessary libraries
target_link_libraries(ImageSegmentationByThresholding PRIVATE 
    ${OpenCV_LIBS} 
    Qt6::Core
    Qt6::Widgets 
    Qt6::Gui
)

# Set properties for the target executable
set_target_properties(ImageSegmentationByThresholding PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
