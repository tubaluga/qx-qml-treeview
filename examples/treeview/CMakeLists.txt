project(treeview-example VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Qml Quick Widgets)

if (WIN32)
    set(APPLICATION_TYPE WIN32)
elseif (APPLE)
    set(APPLICATION_TYPE MACOSX_BUNDLE)
endif()

set(QML_IMPORT_PATH ${OUTPUT_DIR})

add_executable(${PROJECT_NAME} ${APPLICATION_TYPE}
    src/main.cpp
	src/exampletreeitemmodel.h
	src/exampletreeitemmodel.cpp
    app.qrc
)

set_target_properties(${PROJECT_NAME} PROPERTIES

	AUTOMOC ON
	AUTORCC ON

	CXX_EXTENSIONS OFF
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
	Qt5::Widgets	
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

