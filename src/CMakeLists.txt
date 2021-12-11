target_sources(RT1W PRIVATE main.cpp vectors.cpp ray.cpp hittables/sphere.cpp)
target_include_directories(RT1W PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} hittables)
