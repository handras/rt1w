cmake_minimum_required(VERSION 3.15)

# set the project name
project(RT1W)

include_directories(D:/progik/c_libraries/SDL2-devel-2.0.18-mingw/x86_64-w64-mingw32/include/SDL2
        D:/progik/c_libraries/cmocka-1.1.5/include
        src
)

link_directories(D:/progik/c_libraries/SDL2-devel-2.0.18-mingw/x86_64-w64-mingw32/lib)

SET(SOURCES src/main.cpp src/vectors.cpp src/ray.cpp)
SET(TST_SOURCES src/vectors.cpp tst/cmocka.c tst/tst_main.c tst/test_vectors.c)

add_executable(RT1W ${SOURCES})
add_executable(Tests ${TST_SOURCES})

target_link_libraries(RT1W SDL2main SDL2)
