cmake_minimum_required(VERSION 3.10...4.0)
project(tharo C)

set(CMAKE_C_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        argtable3
        GIT_REPOSITORY https://github.com/argtable/argtable3
)
FetchContent_MakeAvailable(argtable3)

add_executable(tharo
        main.c
        macros.h
        messages.h
        version.h
        config.c
        config.h
        logger.c
        logger.h
        memory.c
        memory.h
        safemem.c
        safemem.h
)

target_link_libraries(tharo PRIVATE argtable3)
