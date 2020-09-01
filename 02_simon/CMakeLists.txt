cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

PROJECT(simon)

add_compile_options( -g)


find_package( Boost 1.46 COMPONENTS program_options)
link_directories(${Boost_LIBRARY_DIRS})


add_executable(simon
    main.cpp
    simon.cpp)

target_link_libraries(simon
${Boost_PROGRAM_OPTIONS_LIBRARY}
)



