


/// @brief Normal 3D Gauss Seidel algorithm.
/// @param kmax 
/// @param jmax 
/// @param imax 
/// @param phi 
void GS_iteration_normal(int kmax, int jmax, int imax, double ***phi);


/// @brief Gauss Seidel 3D algorithm split into 2 chunks
/// @param kmax 
/// @param jmax 
/// @param imax 
/// @param phi 
void GS_iteration_2_chunks(int kmax, int jmax, int imax, double ***phi);