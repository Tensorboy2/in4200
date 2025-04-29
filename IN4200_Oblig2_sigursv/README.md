# Obligatory assignment 2
## By Sigurd Vargdal.
This project aims to implement the 3D Gauss-Seidel algorithm and parallelizing it with MPI.

## Using cmake:
```bash
mkdir build && cd build
```
Run CMake config:
```bash
cmake ..
```
Run build:
```bash
cmake --build .
```

Both executables expect 4 commandline arguments:
- n  (Int) Numbers of Gauss-Seidel iterations
- kmax (Int) number of k dimensions
- jmax (Int) number of j dimensions
- imax (Int) number of i dimensions

Execute serial:
```bash
./main 10 10 10 10
```

Execute mpi (even jmax example):
```bash
mpirun -np 2 ./main_mpi 10 10 10 10
```
Execute mpi (odd jmax example):
```bash
mpirun -np 2 ./main_mpi 9 9 9 9
```
