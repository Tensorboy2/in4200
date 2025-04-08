

int main(int nargs, char **args){
    double ***arr1, ***arr2;
    int n,k,j,i, num_iters, kmax, jmax, imax;


    for (n=0; n<num_iters; n++) {
        GS_iteration_normal(kmax,jmax,imax,arr1);
        GS_iteration_2_chunks(kmax,jmax,imax,arr2);
        }

    printf("num iters=%d, kmax=%d, jmax=%d, imax=%d, diff=%g\n", num_iters, kmax, jmax, imax, euclidean_distance(kmax,jmax,imax,arr1,arr2));
    return 0;
}