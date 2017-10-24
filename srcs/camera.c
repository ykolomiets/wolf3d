#include "camera.h"
#include "matrix_transformations.h"

void            cam_rotate_left(t_camera *cam)
{
    t_matrix2 rotation_matrix;

    m2_rotate(-ROTATE_SPEED, rotation_matrix);
    cam->dir = m2_mult_v2(rotation_matrix, cam->dir);
    cam->plane = m2_mult_v2(rotation_matrix, cam->plane);
}

void            cam_rotate_right(t_camera *cam)
{
    t_matrix2   rotation_matrix;

    m2_rotate(ROTATE_SPEED, rotation_matrix);
    cam->dir = m2_mult_v2(rotation_matrix, cam->dir);
    cam->plane = m2_mult_v2(rotation_matrix, cam->plane);
}

void            cam_move_forward(t_camera *cam)
{
    cam->pos.x += cam->dir.x * MOVE_SPEED;
    cam->pos.y += cam->dir.y * MOVE_SPEED;
}

void            cam_move_backward(t_camera *cam)
{
    cam->pos.x -= cam->dir.x * MOVE_SPEED;
    cam->pos.y -= cam->dir.y * MOVE_SPEED;
}

void            cam_move_left(t_camera *cam)
{
    t_vec2  temp;
    double  dir_length;

    temp = v2_normalize(cam->plane);
    dir_length = v2_magnitude(cam->dir);
    temp = v2_mult_by_scalar(temp, dir_length);
    cam->pos.x -= temp.x * MOVE_SPEED;
    cam->pos.y -= temp.y * MOVE_SPEED;
}

void            cam_move_right(t_camera *cam)
{
    t_vec2  temp;
    double  dir_length;

    temp = v2_normalize(cam->plane);
    dir_length = v2_magnitude(cam->dir);
    temp = v2_mult_by_scalar(temp, dir_length);
    cam->pos.x += temp.x * MOVE_SPEED;
    cam->pos.y += temp.y * MOVE_SPEED;
}

void            cam_zoom_in(t_camera *cam)
{
    cam->dir = v2_mult_by_scalar(cam->dir, 1.1);
}

void            cam_zoom_out(t_camera *cam)
{
    cam->dir = v2_mult_by_scalar(cam->dir, 0.91);
}