cmake_minimum_required(VERSION 3.16)

project(yadro_test_rfc LANGUAGES CXX)

set(headers_dir ./include)
set(source_dir ./src)

set(headers
    ${headers_dir}/signal_generator.h
    ${headers_dir}/quantizer.h
    ${headers_dir}/interpolation.h
    ${headers_dir}/utils.h
)

set(sources
    ${source_dir}/main.cpp
    ${source_dir}/signal_generator.cpp
    ${source_dir}/quantizer.cpp
    ${source_dir}/interpolation.cpp
    ${source_dir}/utils.cpp
)


add_executable(yadro_test_rfc ${headers} ${sources})

target_include_directories(yadro_test_rfc PRIVATE ./include)