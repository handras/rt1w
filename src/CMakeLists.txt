target_sources(RT1W PRIVATE main.cpp vectors.cpp ray.cpp camera.cpp)
target_include_directories(RT1W PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} hittables utils materials)

add_subdirectory(hittables)
add_subdirectory(utils)
