#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi_function_declarations.h"
#include <mpi.h>


void GS_iteration_2_chunks_mpi(int my_rank, int kmax, int my_jmax, int imax, double ***my_phi){
    
    MPI_Status status;
    int tag = 0;
    // First k is only a left chunk computation, but the left most row from right chunk is needed. This we send from rank 1, and receive with rank 0. 
    int k = 1;
    if (my_rank == 1){
        MPI_Send(my_phi[k][1], imax, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
    if (my_rank == 0){
        // First computation
        MPI_Recv(my_phi[k][my_jmax], imax, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int j = 1; j <= my_jmax - 1; j++){
            for (int i = 1; i < imax - 1; i++){
                my_phi[k][j][i] =  (my_phi[k - 1][j][i] + my_phi[k][j - 1][i]
                    + my_phi[k][j][i - 1] + my_phi[k][j][i + 1]
                    + my_phi[k][j + 1][i] + my_phi[k + 1][j][i]) / 6.0; // Will use rank 1 values for last right most neighbors. 
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD); // wait for each process
    // Now rest of the k's with rank 1 working on k-1. Both ranks must first send and receive the array needed by the other rank, then they can do their respective computation.
    for (int k = 2; k < kmax - 1; k++){
        int k_2 = k - 1;

        if (my_rank == 0){ 
            MPI_Sendrecv(
                my_phi[k_2][my_jmax-1], imax, MPI_DOUBLE, 1, tag,
                my_phi[k][my_jmax], imax, MPI_DOUBLE, 1, tag,
                MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("rank: %d, my_jmax: %d\n",my_rank,my_jmax);
            
            for (int j = 1; j <= my_jmax - 1; j++){
                for (int i = 1; i < imax - 1; i++){
                    my_phi[k][j][i] =  (my_phi[k - 1][j][i] + my_phi[k][j - 1][i]
                        + my_phi[k][j][i - 1] + my_phi[k][j][i + 1]
                        + my_phi[k][j + 1][i] + my_phi[k + 1][j][i]) / 6.0; 
                    } 
                }
            }
            
            if (my_rank == 1){
                MPI_Sendrecv(
                    my_phi[k][1], imax, MPI_DOUBLE, 0, tag,
                    my_phi[k_2][0], imax, MPI_DOUBLE, 0, tag,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    // printf("rank: %d, sendt: %d, recv: %d\n",my_rank, 0,1);
            for (int j = 1; j < my_jmax - 1; j++){
                for (int i = 1; i < imax - 1; i++){
                    my_phi[k_2][j][i] = (my_phi[k_2 - 1][j][i] + my_phi[k_2][j - 1][i]
                        + my_phi[k_2][j][i - 1] + my_phi[k_2][j][i + 1]
                        + my_phi[k_2][j + 1][i] + my_phi[k_2 + 1][j][i]) / 6.0; 
                } 
            }
        } 
        
        MPI_Barrier(MPI_COMM_WORLD); // wait for each process
    }


    
    // Lastly the final k of the right chunk is computed by rank 1 with the boundary values sent from rank 0.
    k = kmax-2; // k=5 for kmax = 7 which should be correct.
    if (my_rank == 0){ 
        MPI_Send(my_phi[k][my_jmax-1], imax, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
    }
    if (my_rank == 1){
        MPI_Recv(my_phi[k][0], imax, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int j = 1; j < my_jmax - 1; j++){
            for (int i = 1;  i < imax - 1; i++){
                my_phi[k][j][i] = (my_phi[k - 1][j][i] + my_phi[k][j - 1][i]
                    + my_phi[k][j][i - 1] + my_phi[k][j][i + 1]
                    + my_phi[k][j + 1][i] + my_phi[k + 1][j][i]) / 6.0; // Will use rank 0 values for first left most neighbors. 
            }
        }   
    }
}

