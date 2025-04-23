#include <stdio.h>
#include "function_declarations.h"

void GS_iteration_2_chunks_mpi(int my_rank, int kmax, int my_jmax, int imax, double ***phi){
    // first wavefront: only computation on left chunk at level k=1
    // ...
    for (int k=2; k<=kmax-2; k++) {
        // computation on left chunk at level k
        // ...
        // computation on right chunk at level k-1
        // ...
    }
    // last wavefront: only computation on right chunk at level k=kmax-2
    // ...
}