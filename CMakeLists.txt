cmake_minimum_required(VERSION 3.20)

project(ray_tracing_renderer)

add_subdirectory(vec3)
add_subdirectory(image_outputer)

add_executable(ray_tracing_renderer_test
    main.cpp
    ray.hpp)

set_target_properties(ray_tracing_renderer_test PROPERTIES CXX_STANDARD 23)
target_link_libraries(ray_tracing_renderer_test PUBLIC vec3 image_outputer)
