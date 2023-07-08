#include "fractol.h"

int calculate_julia(t_fractal *fractal)
{
    int i = 0;
    double temp;

    while (i <= fractal->max_iterations)
    {
        temp = fractal->a_real;
        fractal->a_real = (fractal->a_real * fractal->a_real) - (fractal->b_img * fractal->b_img) + fractal->julia_x;
        fractal->b_img = (2 * temp * fractal->b_img) + fractal->julia_y;
        if ((fractal->a_real * fractal->a_real) + (fractal->b_img * fractal->b_img) > 4)
            break;
        i++;
    }
    return (i);
}

int calculate_mandelbrot(t_fractal *fractal, double y, double x)
{
    int i = 1;
    double temp;
    while (i <= fractal->max_iterations)
    {
        temp = fractal->a_real;
        fractal->a_real = (fractal->a_real * fractal->a_real) - (fractal->b_img * fractal->b_img) + x / fractal->zoom + fractal->offset_x;
        fractal->b_img = (2 * temp * fractal->b_img) + y / fractal->zoom + fractal->offset_y;
        if ((fractal->a_real * fractal->a_real) + (fractal->b_img * fractal->b_img) > 16)
            break;
        i++;
    }
    return i;
}

void draw_julia(void *p)
{
    t_fractal *fractal;
    fractal = p;

    fractal->y_coord = 0;
    fractal->x_coord = 0;
    double x;
    double y;
    double temp;
    int i;

    while (fractal->y_coord < 4 * fractal->n)
    {
        y = 2 - (fractal->y_coord / fractal->n);
        while (fractal->x_coord < 4 * fractal->n)
        {
            x = -2 + (fractal->x_coord / fractal->n);

            fractal->a_real = (x / fractal->zoom + fractal->offset_x);
            fractal->b_img = (y / fractal->zoom + fractal->offset_y);

            i = calculate_julia(fractal);
            // i = calculate_mandelbrot(fractal, y, x);
            if (i == fractal->max_iterations + 1)
                mlx_put_pixel(fractal->img, fractal->x_coord, fractal->y_coord, 0x000000FF); // black
            else
                mlx_put_pixel(fractal->img, fractal->x_coord, fractal->y_coord, get_color(i + 88)); // white
            fractal->x_coord++;
        }
        fractal->x_coord = 0;
        fractal->y_coord++;
    }
    mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
}
