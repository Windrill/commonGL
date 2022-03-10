cmake_minimum_required(VERSION 3.20)
project(common_GL)

include(project_build/functions.cmake)

# GLFW must bee added before OpenGL, or else OpenGL will not be properly included in the GLFW subdirectory
# and this /home/windrill/CLionProjects/test/glfw/examples/gears.c:66: undefined reference to `glShadeModel', and
# dso missing from command line will happen
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)


FIND_ALL_LIBRARIES(modules/
        ALL_MODULES
        EMPTY_DIR
        EMPTY_DIR)

