cmake_minimum_required(VERSION 3.6)
project(enginimus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)
file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(enginimus ${SOURCE_FILES})

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
    message(ERROR " GLEW not found!")
endif(NOT GLEW_FOUND)
#########################################################
# FIND GLFW
#########################################################
find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_DEFINITIONS})
if(NOT GLFW_FOUND)
    message(ERROR " GLFW not found!")
endif(NOT GLFW_FOUND)
#########################################################
# FIND SOIL
#########################################################
find_package(SOIL REQUIRED)
include_directories(${SOIL_INCLUDE_DIRS})
link_directories(${SOIL_LIBRARY_DIRS})
add_definitions(${SOIL_DEFINITIONS})
if(NOT SOIL_FOUND)
    message(ERROR " SOIL not found!")
endif(NOT SOIL_FOUND)
#########################################################
# FIND assimp
#########################################################
find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIRS})
if(NOT assimp_FOUND)
    message(ERROR " assimp not found!")
endif(NOT assimp_FOUND)

SET(EXTRA_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARY} ${assimp_LIBRARIES})
target_link_libraries(enginimus ${EXTRA_LIBS})


#set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_custom_command(TARGET enginimus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:enginimus>/assets)
add_custom_command(TARGET enginimus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:enginimus>/shaders)