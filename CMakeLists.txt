cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        Image.cpp reader.cpp writer.cpp filter.cpp parser.cpp crop_filter.cpp grayscale_filter.cpp negative_filter.cpp sharp.cpp matrix_filter.cpp edge_detection.cpp gaussian_blur.cpp exceptions.cpp)
