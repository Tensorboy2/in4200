

/// @brief Allocates the system array
/// @param kmax Number of points in k direction
/// @param jmax Number of points in j direction
/// @param imax Number of points in i direction
/// @param array 3D system array
void allocate_array3D(int kmax, int jmax, int imax, double ****array);

/// @brief Free function for system array
/// @param array 3D system array
/// @param kmax Number of points in k direction
/// @param jmax Number of points in j direction
void free_array3D(double ***array, int kmax, int jmax);


/// @brief Calculates the euclidean distance between array 1 and array 2
/// @param kmax 
/// @param jmax 
/// @param imax 
/// @param arr1 
/// @param arr2 
/// @return Euclidean distance between two matrices 
double euclidean_distance(int kmax, int jmax, int imax, double ***arr1, double ***arr2);
