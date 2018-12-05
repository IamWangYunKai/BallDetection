cmake_minimum_required (VERSION 3.0)

#项目名称
SET(PROJ_NAME "pointcloud")
project (${PROJ_NAME})

find_package(Qt5 COMPONENTS QuickControls2)

SET(INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include
				 ${CMAKE_CURRENT_LIST_DIR}/samples
                 ${CMAKE_CURRENT_LIST_DIR}/third-party/glfw-imgui/include
                 ${CMAKE_CURRENT_LIST_DIR}/include/opencv
                 ${CMAKE_CURRENT_LIST_DIR}/include/opencv2
                 ${CMAKE_CURRENT_LIST_DIR}/actionmodule.h
                 ${CMAKE_CURRENT_LIST_DIR}/singleton.hpp
                 ${Qt5Core_INCLUDE_DIRS}
                 ${Qt5Network_INCLUDE_DIRS}
                 )

# 源文件
file(GLOB SOURCE ${CMAKE_CURRENT_LIST_DIR}/rs-align.cpp
                 ${CMAKE_CURRENT_LIST_DIR}/actionmodule.cpp
                 )

# 链接文件
file(GLOB LINK_DIRS ${CMAKE_CURRENT_LIST_DIR}/lib/x64/realsense2.lib
					${CMAKE_CURRENT_LIST_DIR}/lib/x64/glfw-imgui.lib
					${CMAKE_CURRENT_LIST_DIR}/lib/opencv_world343.lib
					)

# 添加头文件
include_directories(${INCLUDE_DIRS})

# 添加源文件
add_executable(${PROJ_NAME} ${SOURCE})

# 编译输出路径
if ( MSVC )
    set_target_properties( ${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin )
    set_target_properties( ${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin )
    set_target_properties( ${PROJ_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin )
endif ( MSVC )

# 添加链接库
target_link_libraries(${PROJ_NAME} ${LINK_DIRS}
                                   glu32.lib
                                   opengl32.lib
                                   "C:/Qt/Qt5.10.1/5.10.1/msvc2015_64/lib/Qt5QuickControls2.lib"
                                   "C:/Qt/Qt5.10.1/5.10.1/msvc2015_64/lib/Qt5Network.lib"
                                   "C:/Qt/Qt5.10.1/5.10.1/msvc2015_64/lib/Qt5Core.lib"
                                   )