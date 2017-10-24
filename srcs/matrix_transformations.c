#include "matrix_transformations.h"
#include <math.h>

void    m2_rotate(double angle, t_matrix2 res)
{
    res[0] = cos(angle);
    res[2] = sin(angle);
    res[1] = res[2];
    res[3] = res[0];
}