cmake_minimum_required(VERSION 3.16)
project(TorresDeHanoi VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración automática de Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Buscar Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

# Archivos del proyecto
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    disco.cpp
    disco.h
    torre.cpp
    torre.h
    soundmanager.cpp
    soundmanager.h
)

# Crear el ejecutable
add_executable(TorresDeHanoi ${PROJECT_SOURCES})

# Enlazar con Qt6
target_link_libraries(TorresDeHanoi
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

# Configuración de compilación
target_compile_options(TorresDeHanoi PRIVATE
    -Wall
    -Wextra
)

# Mensaje de información
message(STATUS "===========================================")
message(STATUS "Configurando Torres de Hanoi Profesional")
message(STATUS "===========================================")
message(STATUS "Qt6 Core:    ${Qt6Core_VERSION}")
message(STATUS "Qt6 Widgets: ${Qt6Widgets_VERSION}")
message(STATUS "Compilador:  ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "===========================================")
