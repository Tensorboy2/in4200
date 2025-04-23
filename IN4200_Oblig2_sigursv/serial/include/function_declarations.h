


/**
 * Normal 3D Gauss Seidel algorithm. 
 * 
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 * @param imax Number of points in i direction
 * @param phi Pointer to system
 */
void GS_iteration_normal(int kmax, int jmax, int imax, double ***phi);

/**
 * Gauss Seidel 3D algorithm split into 2 chunks
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 * @param imax Number of points in i direction
 * @param phi Pointer to system
 */
void GS_iteration_2_chunks(int kmax, int jmax, int imax, double ***phi);