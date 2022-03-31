cmake_minimum_required(VERSION 3.1)

project(game)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

aux_source_directory(src/server SERVER_SOURCES)
aux_source_directory(src/shared SERVER_SOURCES)

aux_source_directory(src/client CLIENT_SOURCES)
aux_source_directory(src/shared CLIENT_SOURCES)

add_executable(game_server ${SERVER_SOURCES})
add_executable(game_client ${CLIENT_SOURCES})
