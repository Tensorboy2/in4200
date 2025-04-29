#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "mpi_function_declarations.h"
#include "serial_function_declarations.h"
#include "helpers.h"
#include <time.h>

int main(int argc, char **argv){

    // Initialize MPI:
    int rank, size; 
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    
    // Get numbers from command line:
    int num_iters, kmax, jmax, imax;
    if (rank == 0) { 
        num_iters = atoi(argv[1]);
        kmax = atoi(argv[2]);
        jmax = atoi(argv[3]);
        imax = atoi(argv[4]);
    }

    // Broadcast:
    MPI_Bcast(&num_iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&kmax,      1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&jmax,      1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&imax,      1, MPI_INT, 0, MPI_COMM_WORLD);


    // Split domain:
    int j_split = jmax / 2;
    int my_jmax;
    if (jmax % 2 != 0 ) {
        j_split += (rank == 0) ? 1 : 0;
        my_jmax = (rank == 0) ? j_split : jmax - j_split;
    } else {
        my_jmax = (rank == 0) ? j_split : jmax - j_split + 1;
    }
    


    // Array allocation pluss neighbour row: 
    double ***my_phi;
    allocate_array3D(kmax, my_jmax + 1, imax, &my_phi);


    double ***array_mpi;
    if (rank == 0){
        // Allocate full array:
        allocate_array3D(kmax,jmax,imax,&array_mpi);
        
        // Fill first chunk into rank 0:
        for (int k = 0; k < kmax; k++) {
            for (int j = 0; j < j_split; j++) {
                for (int i = 0; i < imax; i++) {
                    my_phi[k][j][i] = array_mpi[k][j][i];
                }
            }
        }
        
        // Send second chunk to rank 1:
        int send_size = kmax * (jmax - j_split) * imax;
        double *send_buffer = malloc(send_size * sizeof(double));

        int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = j_split; j < jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    send_buffer[idx++] = array_mpi[k][j][i];
                }
            }
        }
        MPI_Send(send_buffer, send_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        free(send_buffer);
    } 

    
    if (rank == 1) { 
        // Receive dimensions and fill the rank 1 array :
        int recv_size = kmax * my_jmax * imax;
        double *receive_buffer = malloc(recv_size * sizeof(double));
        MPI_Recv(receive_buffer, recv_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);

        int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = 1; j < my_jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    my_phi[k][j][i] = receive_buffer[idx++];
                }
            }
        }
        free(receive_buffer);
    }
    
    MPI_Barrier(MPI_COMM_WORLD); 
    
    // Perform 2 chunk Gauss Seidel with mpi: 
    double t_start = MPI_Wtime(); // Use MPI Wall time for timing simulation
    for (int n = 0; n < num_iters; n++){
        GS_iteration_2_chunks_mpi(rank, kmax, my_jmax, imax, my_phi);
    }
    
    double t_end = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD); // wait for each process
    
    
    if (rank == 1){
        // Send result from rank 1 to rank 0:
        int send_size = kmax * (my_jmax - 1) * imax;
        double *send_buffer = malloc(send_size * sizeof(double));
        int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = 1; j < my_jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    send_buffer[idx++] = my_phi[k][j][i];
                }
            }
        }
        
        MPI_Send(send_buffer, send_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        free(send_buffer);    
    }
    
    if (rank == 0){
        // Receive results from rank 1:
        int other_jmax = jmax - j_split;
        int recv_size = kmax * other_jmax * imax;
        double *receive_buffer = malloc(recv_size* sizeof(double));
        MPI_Recv(receive_buffer, recv_size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);

        // Fill first chunk:
        int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = 0; j < j_split; j++) {
                for (int i = 0; i < imax; i++) {
                    array_mpi[k][j][i] = my_phi[k][j][i];
                }
            }
        }

        // Fill second chunk:
        idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = j_split; j < jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    array_mpi[k][j][i] = receive_buffer[idx++];
                }
            }
        }
        
        free(receive_buffer);      
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0){
        // Serial version:
        double ***array_serial;
        allocate_array3D(kmax, jmax, imax, &array_serial);
        clock_t start = clock();
        for (int n = 0; n < num_iters; n++) {
            GS_iteration_2_chunks(kmax,jmax,imax,array_serial);
        }
        clock_t end = clock();
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        
        // Compare results:
        printf("num iters=%d, kmax=%d, jmax=%d, imax=%d, diff=%g\n", 
            num_iters, kmax, jmax, imax, 
            euclidean_distance(kmax,jmax,imax,array_mpi,array_serial));
        printf("Execution time for MPI: %f seconds\n", t_end - t_start);
        printf("Serial time: %f seconds\n", time_spent);
    }

    MPI_Finalize();
    return 0;
}