cmake_minimum_required(VERSION 3.10)
project(MyGraphProject C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(MPI REQUIRED)       # MPI support

# Common source files:
set(COMMON_SOURCES
    src/
)

# Serial executable
add_executable(main main.c ${COMMON_SOURCES})
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/include)


# MPI-enabled executable
add_executable(main_mpi main_mpi.c ${COMMON_SOURCES})
target_include_directories(main_mpi PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main_mpi MPI::MPI_C)

# Optional: Define default thread count as a macro
option(THREAD_COUNT "Number of threads for execution" 4)
add_definitions(-DDEFAULT_NUM_THREADS=${THREAD_COUNT})
