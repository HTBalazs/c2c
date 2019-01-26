cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -O3 -fPIC")
project(c2c)

link_directories(/usr/local/lib/prolog)

#Look for source and header files recursively in the src/ directory
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

#Generate list of header files and include them
set (HEADERS_DIRS "")
foreach (_headerFile ${HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND HEADERS_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES HEADERS_DIRS)
include_directories(${HEADERS_DIRS})

#List header files
message(${HEADERS_DIRS})

# Define library and include directories
set(STATIC_LIB_DIR /usr/local/lib/c2c)
set(INCLUDE_DIR /usr/local/include/c2c)
# set archive output to <project_directory>/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib/)
# generate libc2c.a file
add_library(c2c STATIC ${SOURCES})

# install lib and include directories
install(TARGETS c2c DESTINATION ${STATIC_LIB_DIR})
install(FILES ${HEADERS} DESTINATION ${INCLUDE_DIR})
