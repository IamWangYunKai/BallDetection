cmake_minimum_required (VERSION 3.0)

#项目名称
SET(PROJ_NAME "Viewer")
project (${PROJ_NAME})

SET(INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include
				 "C:/Program Files/OpenNI2/Include"
                 )

# 源文件
file(GLOB SOURCE "${CMAKE_CURRENT_LIST_DIR}/src/*.*")

# 链接文件
file(GLOB LINK_DIRS "C:/Program Files/OpenNI2/Lib/OpenNI2.lib"
					${CMAKE_CURRENT_LIST_DIR}/lib/glut32.lib
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
target_link_libraries(${PROJ_NAME} ${LINK_DIRS})