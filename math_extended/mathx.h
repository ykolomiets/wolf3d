/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 14:55:18 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 14:55:19 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHX_H
# define MATHX_H

# define PI 3.141592653589793f
# define ROUND(a) ((int)(a + 0.5))
# define ABS(a) ((a) < 0 ? -(a) : (a))
# define IN_RANGE(x, min, max) ((x) >= (min) && (x) <= (max))
# define MAX(x, y) ((x) < (y) ? (y) : (x))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define CLAMP_255(x) (unsigned char)((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))
# define v3(x, y, z)  (t_vec3){x, y, z}
# define v2(x, y)   (t_vec2){x, y}

typedef struct	s_vec2
{
    double	x;
    double	y;
}				t_vec2;

typedef struct	s_vec3
{
    double x;
    double y;
    double z;
}				t_vec3;

typedef struct	s_hvec
{
    double x;
    double y;
    double z;
    double w;
}				t_hvec;

typedef struct	s_cnum
{
	double r;
	double i;
}				t_cnum;

typedef double  t_matrix2[4];
typedef double	t_matrix3[9];
typedef double	t_matrix4[16];

t_vec2			v2_add(t_vec2 a, t_vec2 b);
t_vec2			v2_sub(t_vec2 a, t_vec2 b);
int				v2_mult_by_scalar(t_vec2 *a, double c);
int				v2_div_by_scalar(t_vec2 *a, double c);
double			v2_dot_product(t_vec2 *a, t_vec2 *b);
double			v2_magnitude(t_vec2 *a);
t_vec2			v2_normalize(t_vec2 a);

void            m2_fill_null(t_matrix2 m);
void            m2_identity(t_matrix2 m);
double          m2_det(t_matrix2 m);

t_vec2  		m2_mult_v2(t_matrix2 m, t_vec2 v);

t_vec3			v3_add(t_vec3 a, t_vec3 b);
t_vec3			v3_sub(t_vec3 a, t_vec3 b);
t_vec3			v3_mult_c(t_vec3 a, double c);
t_vec3			v3_div_by_scalar(t_vec3 a, double c, int *err);
double			v3_dot(t_vec3 a, t_vec3 b);
t_vec3			v3_cross_product(t_vec3 a, t_vec3 b);
double			v3_magnitude(t_vec3 a);
t_vec3			v3_normalize(t_vec3 v);

t_hvec			hv_create_point(double x, double y, double z);
t_hvec			hv_create_direction(double x, double y, double z);
t_hvec			hv_normalize(t_hvec v);

void			m3_fill_null(t_matrix3 m);
void			m3_identity(t_matrix3 m);
double			m3_det(t_matrix3 m);
int				m3_inverse(t_matrix3 m, t_matrix3 res);

t_vec3			m3_mult_v3(t_matrix3 m, t_vec3 v);

void			m4_fill_null(t_matrix4 m);
void			m4_identity(t_matrix4 m);
void			m4_mult(t_matrix4 a, t_matrix4 b, t_matrix4 res);
void			m4_add(t_matrix4 a, t_matrix4 b, t_matrix4 res);
void			m4_sub(t_matrix4 a, t_matrix4 b, t_matrix4 res);
void			m4_submat(t_matrix4 m, t_matrix3 sub, int i, int j);
double			m4_det(t_matrix4 m);
int				m4_inverse(t_matrix4 m, t_matrix4 res);

t_hvec			m4_mult_hv(t_matrix4 m, t_hvec *v);

t_cnum			cn_create(double re, double im);
t_cnum			cn_add(t_cnum *a, t_cnum *b);
t_cnum			cn_sub(t_cnum *a, t_cnum *b);
t_cnum			cn_mult(t_cnum *a, t_cnum *b);
int				cn_div(t_cnum *a, t_cnum *b, t_cnum *res);
t_cnum			cn_pow(t_cnum *c, double pow);

#endif
