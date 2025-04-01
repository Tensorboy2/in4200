cmake_minimum_required(VERSION 3.10)
project(MyGraphProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED) # Find OpenMP

# Common source files:
set(COMMON_SOURCES
    src/read_graph_from_file1.c
    src/read_graph_from_file2.c
    src/PageRank_iterations1.c
    src/PageRank_iterations2.c
    src/top_n_webpages.c
)


add_executable(main main.c ${COMMON_SOURCES}) # Standard serial executable


add_executable(main_omp main_omp.c ${COMMON_SOURCES})# OpenMP-enabled executable

target_include_directories(main  PUBLIC ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(main_omp OpenMP::OpenMP_C)# Link OpenMP only to main_omp

option(THREAD_COUNT "Number of threads for execution" 4)
add_definitions(-DDEFAULT_NUM_THREADS=${THREAD_COUNT})

target_include_directories(main_omp  PUBLIC ${CMAKE_SOURCE_DIR}/include)