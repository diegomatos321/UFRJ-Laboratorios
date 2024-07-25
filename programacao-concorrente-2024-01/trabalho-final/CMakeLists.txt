cmake_minimum_required(VERSION 3.16) # Updated to a more recent version for better compatibility
project(ImageSegmentationByThresholding VERSION 0.1.0 LANGUAGES CXX)

# Ensure automoc, autorcc, and autouic are enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required packages
find_package(OpenCV 4.10 REQUIRED COMPONENTS imgcodecs imgproc highgui)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)

# Standard Qt setup function (only in recent Qt6 versions, ensure you have it)
qt_standard_project_setup()

# Adicionar o diretório de origem
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/headers")
set(ICONS_DIR "${CMAKE_SOURCE_DIR}/Icons")

# Adicionar arquivos fonte e cabeçalhos
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${HEADERS_DIR}/*.h")
file(GLOB_RECURSE ICONS "${ICONS_DIR}/*")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${HEADERS_DIR})

# Add executable and list all necessary sources
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${ICONS})

# Link the necessary libraries
target_link_libraries(ImageSegmentationByThresholding PRIVATE 
    ${OpenCV_LIBS} 
    Qt6::Core
    Qt6::Widgets 
    Qt6::Gui
    Qt6::Concurrent
)

# Set properties for the target executable
set_target_properties(ImageSegmentationByThresholding PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
