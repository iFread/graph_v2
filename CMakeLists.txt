 
cmake_minimum_required(VERSION 3.8)
project (test_gui)
set(SOURCES main.cpp base_gui_v2.cpp binder_lib.cpp point.cpp base_graph.cpp base_tool.cpp gui.cpp canvas_2.cpp test_app.cpp dynamic_axis.cpp) # Graph.cpp window.cpp
set(CMAKE_FLAGS "{CMAKE_FLAGS} -std=c++11 ")
#LINK_DIRECTORIES(${SOURCES} /usr/lib/fltk)

#set(DIST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist")
#set(FLTK "${DIST_DIR}/FLTK")

set(FLTK_DIR /usr/lib/fltk-1.4/build)
#if(NOT IS_DIRECTORY ${FLTK})
 # message("Starting add FLTK library...")
 #execute_process(COMMAND git clone https://github.com/fltk/fltk.git ${CMAKE_CURRENT_SOURCE_DIR}/dist/FLTK)
 # execute_process(COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/dist/FLTK)
#endif()

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} /dist/FLTK)

#add_executable(keyplay ${CMAKE_CURRENT_SOURCE_DIR} main.cpp)

#find_library(LibFltk libfltk.a PATHS ${CMAKE_CURRENT_SOURCE_DIR}/dist/FLTK)
add_executable (main   ${SOURCES} )

#target_link_libraries(keyplay ${LibFltk})

target_link_libraries(main  fltk fltk_images)
