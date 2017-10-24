#ifndef CAMERA_H
# define CAMERA_H

# include "mathx.h"

typedef struct  s_camera
{
    t_vec2  pos;
    t_vec2  dir;
    t_vec2  plane;
}               t_camera;

void            cam_rotate_left(t_camera *cam);
void            cam_rotate_right(t_camera *cam);
void            cam_move_forward(t_camera *cam);
void            cam_move_backward(t_camera *cam);
void            cam_zoom_in(t_camera *cam);
void            cam_zoom_out(t_camera *cam);

#endif
