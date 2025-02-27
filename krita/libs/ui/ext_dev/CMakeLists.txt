cmake_minimum_required(VERSION 3.16)

# 修改项目名为库名称（避免与主项目冲突）
project(ext_dev LANGUAGES CXX DESCRIPTION "ext for krita")

#启用Qt元对象编译器(MOC)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(ext_dev_SOURCES
    main.cpp
    #extres.qrc
    extglobal.cpp
    extglobal.h
    extmainframe.cpp
    extmainframe.h
    Gallery/gallerywidget.cpp
    Gallery/gallerywidget.h
    Gallery/gallerywidget.ui
    HSBColorPicker/hsbcolorpicker.cpp
    HSBColorPicker/hsbcolorringpicker.cpp
    HSBColorPicker/hsbcolorsliderpicker.cpp
    HSBColorPicker/selectcolorwidget.cpp
    HSBColorPicker/hsbcolorpicker.h
    HSBColorPicker/hsbcolorringpicker.h
    HSBColorPicker/hsbcolorsliderpicker.h
    HSBColorPicker/selectcolorwidget.h
    PaintWidget/lefttool.cpp
    PaintWidget/lefttool.h
    PaintWidget/lefttool.ui
    PaintWidget/paintwidget.cpp
    PaintWidget/paintwidget.h
    PaintWidget/paintwidget.ui
    Utils/qttoolbuttonex.cpp
    Utils/qttoolbuttonex.h
    Utils/qttools.cpp
    Utils/qttools.h
)

kis_add_library(ext_dev SHARED ${ext_dev_SOURCES})

#包含当前目录头文件路径
target_include_directories(ext_dev
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
# 链接Qt依赖
target_link_libraries(ext_dev PRIVATE
    Qt${QT_DEFAULT_MAJOR_VERSION}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_definitions(ext_dev PRIVATE EXT_DEV_LIBRARY)
#安装目标
install(TARGETS ext_dev DESTINATION lib)
