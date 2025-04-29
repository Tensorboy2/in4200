#include <stdio.h>
#include "serial_function_declarations.h"

void GS_iteration_normal(int kmax, int jmax, int imax, double ***phi){
    int k,j,i;
    for (k=1;k<kmax-1;k++){
        for (j=1;j<jmax-1;j++){
            for (i=1;i<imax-1;i++){
                phi[k][j][i] = (phi[k-1][j][i] + phi[k][j-1][i]
                                +phi[k][j][i-1] + phi[k][j][i+1]
                                +phi[k][j+1][i] + phi[k+1][j][i])/6.0;
            }
        }
    }
}

void GS_iteration_2_chunks(int kmax, int jmax, int imax, double ***phi){
    // first wavefront: only computation on left chunk at level k=1
    int jmid = jmax/2;

    int k = 1;
    for (int j = 1; j < jmid; j++){
        for (int i = 1; i < imax - 1; i++){
            phi[k][j][i] = (phi[k - 1][j][i] + phi[k][j - 1][i]
                + phi[k][j][i - 1] + phi[k][j][i + 1]
                + phi[k][j + 1][i] + phi[k + 1][j][i]) / 6.0;
        }
    }

    for (k = 2; k < kmax - 1; k++) {
        // Computation on left chunk at level k:
        for (int j = 1; j < jmid; j++){
            for (int i = 1; i < imax - 1; i++){
                phi[k][j][i] = (phi[k - 1][j][i] + phi[k][j - 1][i]
                    + phi[k][j][i - 1] + phi[k][j][i + 1]
                    + phi[k][j + 1][i] + phi[k + 1][j][i]) / 6.0;
            }
        }
        // Computation on right chunk at level k-1:
        int k_2 = k - 1;
        for (int j = jmid; j < jmax - 1; j++){
            for (int i = 1; i < imax - 1; i++){
                phi[k_2][j][i] = (phi[k_2 - 1][j][i] + phi[k_2][j - 1][i]
                    + phi[k_2][j][i - 1] + phi[k_2][j][i + 1]
                    + phi[k_2][j + 1][i] + phi[k_2 + 1][j][i]) / 6.0;
            }
        }
    }

    // last wavefront: only computation on right chunk at level k=kmax-2
    k = kmax - 2;
    for (int j = jmid; j < jmax - 1; j++){
        for (int i = 1; i < imax - 1;i++){
            phi[k][j][i] = (phi[k - 1][j][i] + phi[k][j - 1][i]
                + phi[k][j][i - 1] + phi[k][j][i + 1]
                + phi[k][j + 1][i] + phi[k + 1][j][i]) / 6.0;
        }
    }
}