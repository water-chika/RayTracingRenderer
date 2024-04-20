cmake_minimum_required(VERSION 3.20)

project(ray_tracing_renderer)

add_subdirectory(vec3)
add_subdirectory(image_outputer)
add_subdirectory(draw_pixels)
add_subdirectory(measure_duration)

add_executable(ray_tracing_renderer_test
    main.cpp
    ray.hpp
    camera.hpp
    hittable.hpp
    sphere.hpp
    hittable_list.hpp
    interval.hpp
    renderer.hpp)

set_target_properties(ray_tracing_renderer_test PROPERTIES CXX_STANDARD 23)
target_link_libraries(
    ray_tracing_renderer_test 
    PUBLIC vec3 image_outputer draw_pixels measure_duration)
target_compile_options(ray_tracing_renderer_test PUBLIC /Qpar)
