# Obligatory assignment 1
## By Sigurd Vargdal.
This project aims to implement the iterative PageRank algorithm for graphs such as hyperlink graphs for web pages, and return the top $n$ pages in the graph. For documentation; global function used in the main files have docstring in the include/function_declarations.h file, while local functions have their docstring in the respective .c file.



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
Run build:
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


