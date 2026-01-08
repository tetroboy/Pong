cmake_minimum_required(VERSION 3.16)
project(Pong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0.2 COMPONENTS graphics window system audio QUIET)

if(NOT SFML_FOUND)
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-3.0.2/lib/cmake/SFML")
    find_package(SFML 3.0.2 REQUIRED COMPONENTS Graphics Window System Audio)
endif()

file(GLOB MAIN_SOURCES "src/main.cpp" "src/Game.cpp")
file(GLOB STATES_SOURCES "src/States/*.cpp")
file(GLOB ENTITIES_SOURCES "src/Entities/*.cpp")
file(GLOB SYSTEMS_SOURCES "src/Managers/*.cpp")
file(GLOB UTILS_SOURCES "src/Utils/*.cpp")

set(SOURCES
    ${MAIN_SOURCES}
    ${STATES_SOURCES}
    ${ENTITIES_SOURCES}
    ${SYSTEMS_SOURCES}
    ${UTILS_SOURCES}
)

file(GLOB MAIN_HEADERS "src/*.h")
file(GLOB STATES_HEADERS "src/States/*.h")
file(GLOB ENTITIES_HEADERS "src/Entities/*.h")
file(GLOB SYSTEMS_HEADERS "src/Managers/*.h")
file(GLOB UTILS_HEADERS "src/Utils/*.h")

set(HEADERS
    ${MAIN_HEADERS}
    ${STATES_HEADERS}
    ${ENTITIES_HEADERS}
    ${SYSTEMS_HEADERS}
    ${UTILS_HEADERS}
)

add_executable(Pong ${SOURCES} ${HEADERS})

target_link_libraries(Pong PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

target_include_directories(Pong PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-3.0.2/include"
)
if(WIN32)
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-3.0.2/bin"
        $<TARGET_FILE_DIR:Pong>)
endif()

add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    $<TARGET_FILE_DIR:Pong>/resources)