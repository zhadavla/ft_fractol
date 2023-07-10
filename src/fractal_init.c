#include "../includes/ft_fractol.h"

void    fractal_init(t_fractal *fractal)
{
    fractal->n = 100;
    fractal->max_iterations = 1000;
    fractal->julia_x = -0.7269;
    fractal->julia_y = 0.1889;

    fractal->min_i = -2.0;
	fractal->min_r = -2.0;
	fractal->max_r = 2.0;
    fractal->max_i = 2.0;

    fractal->color_shift = 0;
}


// 0.285 + 0.01
// −0.7269 + 0.1889