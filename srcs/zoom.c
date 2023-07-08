#include "fractol.h"

void fractal_init(t_fractal *fractal)
{
    // fractal->i = 0;
    fractal->old_zoom = 1;
    fractal->a_real = 0;
    fractal->b_img = 0;
    fractal->n = 150;
    fractal->max_iterations = 100;
    fractal->x_coord = 0;
    fractal->y_coord = 0;
    fractal->julia_x = -0.70176;
    fractal->julia_y = -0.4842;
    fractal->zoom = 1;
    fractal->img_h = fractal->n * 4;
    fractal->img_w = fractal->n * 4;
    fractal->offset_y = 0;
    fractal->offset_x = 0;
}

void move_julia(void *ptr)
{
    t_fractal *fractal;
    fractal = ptr;

    if (mlx_is_key_down(fractal->mlx, MLX_KEY_Z))
        fractal->julia_x -= 0.005;

    if (mlx_is_key_down(fractal->mlx, MLX_KEY_X))
        fractal->julia_x += 0.005;

    if (mlx_is_key_down(fractal->mlx, MLX_KEY_C))
        fractal->julia_y += 0.01;

    if (mlx_is_key_down(fractal->mlx, MLX_KEY_V))
        fractal->julia_y -= 0.01;
}

// Oh, found a GIF. Try this:
// mOffset = event->pos() - float(mZoomLevel) / float(oldZoomLevel) * (event->pos() - mOffset);
void my_scrollhook(double xdelta, double ydelta, void *param)
{
    t_fractal *fractal;

    fractal = param;

    int x, y;
    double x1, y1;
    mlx_get_mouse_pos(fractal->mlx, &x, &y);
    x1 = x;
    y1 = y;
    tranform_to_cartesian(&x1, &y1, fractal->n * 4, fractal->n * 4);
    x1 /= (fractal->n * 4);
    y1 /= (fractal->n * 4);
    printf("x1: %f, y1: %f\n", x1, y1);

    if (ydelta == 1)
    {
        // translate_by_vector(&(fractal->offset_x), &(fractal->offset_y), -x1, -y1);
        scale_by_vector(&(fractal->zoom), &(fractal->zoom), 2);
        // translate_by_vector(&(fractal->offset_x), &(fractal->offset_y), (x1 * 2), (y1 * 2));
    }
    // printf("x1: %f, y1: %f\n", x1, y1);
    else
    {
        translate_by_vector(&(fractal->offset_x), &(fractal->offset_y), x1, y1);
        scale_by_vector(&(fractal->zoom), &(fractal->zoom), 0.5);
        translate_by_vector(&(fractal->offset_x), &(fractal->offset_y), -(x1 * 2), -(y1 * 2));
    }
}

void hook(void *ptr)
{

    t_fractal *fr;
    fr = ptr;

    int x, y;
    double x1, y1;
    mlx_get_mouse_pos(fr->mlx, &x, &y);
    x1 = x;
    y1 = y;
    tranform_to_cartesian(&x1, &y1, fr->n * 4, fr->n * 4);
    x1 /= (fr->n * 4);
    y1 /= (fr->n * 4);

    if (mlx_is_key_down(fr->mlx, MLX_KEY_1))
    {
        fr->previous_offset_x = x1;
        fr->previous_offset_y = y1;
        translate_by_vector(&(fr->offset_x), &(fr->offset_y), x1, y1);
    }
    if (mlx_is_key_down(fr->mlx, MLX_KEY_2))
        scale_by_vector(&(fr->zoom), &(fr->zoom), 1.1);
    if (mlx_is_key_down(fr->mlx, MLX_KEY_3))
    {

        translate_by_vector(&(fr->offset_x), &(fr->offset_y), -fr->previous_offset_x, -fr->previous_offset_y);
    }
    // printf("x1: %f, y1: %f\n", x1, y1);
    // if (ydelta == 1){

    if (mlx_is_key_down(fr->mlx, MLX_KEY_LEFT))
    {
        translate_by_vector(&(fr->offset_x), &(fr->offset_y), -0.1, 0);
    }
    else if (mlx_is_key_down(fr->mlx, MLX_KEY_RIGHT))
    {
        translate_by_vector(&(fr->offset_x), &(fr->offset_y), 0.1, 0);
    }
    else if (mlx_is_key_down(fr->mlx, MLX_KEY_UP))
    {
        translate_by_vector(&(fr->offset_x), &(fr->offset_y), 0, 0.1);
    }
    else if (mlx_is_key_down(fr->mlx, MLX_KEY_DOWN))
    {
        translate_by_vector(&(fr->offset_x), &(fr->offset_y), 0, -0.1);
    }
}