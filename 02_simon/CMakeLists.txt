cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

option(SIMON "Create Simon Block Cipher" OFF)
option(SPECK "Create Speck Block Cipher" OFF)

if (SIMON)
    add_definitions( -DSIMON)
    message(STATUS "Simon cipher will be generated")
    set(CIPHER "simon")
elseif(SPECK)
    add_definitions( -DSPECK)
    message(STATUS "Speck cipher will be generated")
    set(CIPHER "speck")
else()
    message(FATAL_ERROR "Please mention between Speck or Simon.")
endif()

PROJECT(${CIPHER})

find_package( Boost 1.46 COMPONENTS program_options)
link_directories(${Boost_LIBRARY_DIRS})

add_compile_options( -g)


add_executable(${CIPHER}
    main.cpp
    ciphers.cpp)

target_link_libraries(${CIPHER}
${Boost_PROGRAM_OPTIONS_LIBRARY}
)



