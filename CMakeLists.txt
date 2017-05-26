cmake_minimum_required(VERSION 2.6)

#Configuration of project
project(2DM)
set(EXECUTABLE_NAME ${EXECUTABLE_NAME} "2DMotor_exe")
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

#Help find package SFML
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

#Generation of source files
file(
        GLOB_RECURSE
        source_files
        src/*
)

#Declare exe
add_executable(
        ${EXECUTABLE_NAME}
        ${source_files}
)

#add package
find_package(SFML REQUIRED COMPONENTS system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


