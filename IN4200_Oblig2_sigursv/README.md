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
./main 100 100 100 100
```
Expected output:
```bash
num iters=100, kmax=100, jmax=100, imax=100, diff=0
Time spent normal: 1.284010 seconds
Time spent 2 chunks: 1.289453 seconds
```

Execute mpi (even jmax example):
```bash
mpirun -np 2 ./main_mpi 100 100 100
```
Expected output:
```bash
num iters=100, kmax=100, jmax=100, imax=100, diff=0
Execution time for MPI: 0.829974 seconds
Serial time: 1.285701 seconds
```


Execute mpi (odd jmax example):
```bash
mpirun -np 2 ./main_mpi 99 99 99 99
```
Expected output:
```bash
num iters=99, kmax=99, jmax=99, imax=99, diff=0
Execution time for MPI: 0.770302 seconds
Serial time: 1.228599 seconds
```
