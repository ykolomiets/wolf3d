#include "mathx.h"

void            m2_fill_null(t_matrix2 m)
{
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
}

void            m2_identity(t_matrix2 m)
{
    m[0] = 1;
    m[1] = 0;
    m[2] = 0;
    m[3] = 1;
}

double          m2_det(t_matrix2 m)
{
    return (m[0] * m[3] - m[1] * m[2]);
}

t_vec2  		m2_mult_v2(t_matrix2 m, t_vec2 v)
{
    t_vec2  res;

    res.x = m[0] * v.x + m[1] * v.y;
    res.y = m[2] * v.x + m[3] * v.y;
    return (res);
}