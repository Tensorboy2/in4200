# Obligatory assignment 2
## By Sigurd Vargdal.
This project aims to implement the 3D Gauss-Seidel algorithm and parallelizing it with MPI.

## Using cmake:
```bash
mkdir build && cd build
```
Run CMake config (compiles with default 4 threads for OpenMP):
```bash
cmake ..
```
Optional set thread count: 
```bash
cmake -DTHREAD_COUNT=2 ..
```
Run build:
```bash
cmake --build .
```

Execute serial:
```bash
./main
```
Execute mpi:
```bash
mpirun -np2 ./main_mpi
```
