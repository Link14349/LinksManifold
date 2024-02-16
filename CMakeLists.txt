cmake_minimum_required(VERSION 3.6)
project(LinksManifold)
set(CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# set(OpenCV_DIR "C:\\opencv\\build\\x64\\mingw")

# find_package( OpenCV REQUIRED )

include_directories(include ${OpenCV_INCLUDE_DIRS})
link_directories(${PROJECT_SOURCE_DIR}/lib)
# link_directories("C:\\opencv\\build\\x64\\mingw\\bin")
# link_directories("C:\\opencv\\build\\bin")
find_library(GLFW_LIB glfw3 ${PROJECT_SOURCE_DIR}/lib) 

if(NOT GLFW_LIB)
    message(FATAL_ERROR "Cannot find glfw3 library")
endif()

file(GLOB SRC_FILE main.cpp src/core/*.cpp src/renderer/*.cpp)
add_executable(LinksManifold ${SRC_FILE})

target_link_libraries(LinksManifold ${GLFW_LIB})
# target_link_libraries(LinksManifold ${OpenCV_LIBS})