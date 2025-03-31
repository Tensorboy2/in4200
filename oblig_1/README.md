# Obligatory assignment 1
## By Sigurd Vargdal.




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
cmake -DTHREAD_COUNT=8 ..
```

```bash
cmake --build .
```

## Execution:
To use executable here are examples with the graphs stored as txt files in the directory "graphs":

Main:
```bash
./main ../graphs/simple-webgraph.txt ../graphs/100nodes_graph.txt 0.85 1e-6 8
```

OpenMP main:
```bash
./main_omp ../graphs/100nodes_graph.txt 0.85 1e-6 8
```


