cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
 
# set the project name and version
project(${PROJECT_NAME}
        VERSION 1.0)    
        
# opengl
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# find source and header
file(GLOB_RECURSE HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB SHADERS 
     ${CMAKE_CURRENT_SOURCE_DIR}/shader/*.glsl)

# make exe file
add_executable(${PROJECT_NAME} 
               ${SOURCES}
               ${SHADERS}
)

# Linking
target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL glfw)

# compile option for c17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)