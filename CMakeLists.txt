cmake_minimum_required(VERSION 2.8.0)
project(test_qt5_ros)

add_compile_options(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)#added
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)#deleted qt_build added rviz
find_package(Qt5 REQUIRED Core Widgets)#added
set(QT_LIBRARIES Qt5::Widgets)#added
include_directories(
    ${catkin_INCLUDE_DIRS}
    INCLUDE_DIRS include)

catkin_package(INCLUDE_DIRS include CATKIN_DEPENDS roscpp std_msgs) #rosbuild_prepare_qt4(QtCore QtGui) #deleted

#GLOB选项将会为所有匹配查询表达式的文件生成一个文件list，并将该list存储进变量variable里
#文件名查询表达式与正则表达式类似，如果为一个表达式指定了RELATIVE标志，返回的结果将会是相对于给定路径的相对路径
# file(GLOB variable [RELATIVE path] [globbing expressions])

#GLOB_RECURSE选项将会生成一个类似于通常的GLOB选项的list，只是它会寻访所有那些匹配目录的子路径并同时匹配查询表达式的文件
#作为符号链接的子路径只有在给定FOLLOW_SYMLINKS选项时，才会被寻访到
# file(GLOB_RECURSE variable [RELATIVE path] [FOLLOW_SYMLINKS] [globbing expressions])

file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
# file(GLOB CPP_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.hpp *.h)
file(GLOB QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)#added *.h

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) #change QT4 to QT5

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
add_executable(test_qt5_ros ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(test_qt5_ros ${QT_LIBRARIES} ${catkin_LIBRARIES})
install(TARGETS test_qt5_ros RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
