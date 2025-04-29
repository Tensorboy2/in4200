cmake_minimum_required(VERSION 3.10)
project(IN4200_Oblig2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find MPI:
find_package(MPI REQUIRED)


# Include directories:
include_directories(
    ${CMAKE_SOURCE_DIR}/serial/include
    ${CMAKE_SOURCE_DIR}/mpi/include
    ${CMAKE_SOURCE_DIR}/utils/include
)

# Source files:
set(SERIAL_SOURCES
    serial/src/gs_iteration_normal.c
)

set(MPI_SOURCES
    mpi/src/gs_iteration_2_chunks_mpi.c
)

set(UTIL_SOURCES
    utils/src/helpers.c
)

# Executables:
add_executable(main main.c ${SERIAL_SOURCES} ${UTIL_SOURCES})
target_include_directories(main PUBLIC
    ${CMAKE_SOURCE_DIR}/serial/include
    ${CMAKE_SOURCE_DIR}/utils/include
)
target_link_libraries(main m)

add_executable(main_mpi main_mpi.c ${MPI_SOURCES} ${SERIAL_SOURCES} ${UTIL_SOURCES})
target_include_directories(main_mpi PUBLIC
    ${CMAKE_SOURCE_DIR}/mpi/include
    ${CMAKE_SOURCE_DIR}/serial/include
    ${CMAKE_SOURCE_DIR}/utils/include
)
target_link_libraries(main_mpi MPI::MPI_C m)
