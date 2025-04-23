

/**
 * Allocates the system array
 * 
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 * @param imax Number of points in i direction
 * @param array 3D system array
 */
void allocate_array3D(int kmax, int jmax, int imax, double ****array);

/**
 * Free function for system array
 * @param array 3D system array
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 */
void free_array3D(double ***array, int kmax, int jmax);

/**
 * Fill the array with random values but zero at the boundaries
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 * @param imax Number of points in i direction
 * @param array 3D system array
 */
void fill_array(int kmax, int jmax, int imax, double ****array);

/**
 * Calculates the euclidean distance between array 1 and array 2
 * 
 * @param kmax Number of points in k direction
 * @param jmax Number of points in j direction
 * @param imax Number of points in i direction
 * @param arr1 3D system array 1
 * @param arr2 3D system array 2
 */
double euclidean_distance(int kmax, int jmax, int imax, double ***arr1, double ***arr2);
