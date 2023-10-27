cmake_minimum_required(VERSION 3.16)
project(projet_hooke)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(projet_hooke src/main.cpp
        src/engine.cpp
        include/engine.hpp
        src/character.cpp
        include/character.hpp
        src/entity.cpp
        include/entity.hpp
        src/level.cpp
        include/level.hpp
        src/hook.cpp
        include/hook.hpp
        src/tile_map.cpp
        include/tile_map.hpp
        src/game.cpp
        include/game.hpp
)
target_include_directories(projet_hooke PRIVATE src include)
target_link_libraries(projet_hooke PRIVATE sfml-graphics)
target_compile_features(projet_hooke PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET projet_hooke
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:projet_hooke>
            VERBATIM)
endif()

install(TARGETS projet_hooke)