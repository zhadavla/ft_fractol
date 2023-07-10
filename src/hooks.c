#include "../includes/ft_fractol.h"

void hook(void *ptr)
{
    t_fractal *f;
    f = ptr;
	double	center_r;
	double	center_i;
    double distance = 0.04;

	center_r = f->max_r - f->min_r;
	center_i = f->max_i - f->min_i;*		))
	{
		f->min_i -= center_i * distance;
		f->max_i -= center_i * distance;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
}

static void	zoom(t_fractal *f, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = f->min_r - f->max_r;
	center_i = f->max_i - f->min_i;
	f->max_r = f->max_r + (center_r - zoom * center_r) / 2;
	f->min_r = f->max_r + zoom * center_r;
	f->min_i = f->min_i + (center_i - zoom * center_i) / 2;
	f->max_i = f->min_i + zoom * center_i;
}

static void	move(t_fractal *f, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = f->max_r - f->min_r;
	center_i = f->max_i - f->min_i;
	if (direction == 'R')
	{
		f->min_r += center_r * distance;
		f->max_r += center_r * distance;
	}
	else if (direction == 'L')
	{
		f->min_r -= center_r * distance;
		f->max_r -= center_r * distance;
	}
	else if (direction == 'D')
	{
		f->min_i -= center_i * distance;
		f->max_i -= center_i * distance;
	}
	else if (direction == 'U')
	{
		f->min_i += center_i * distance;
		f->max_i += center_i * distance;
	}
}


void    scrollfunc(double xdelta, double ydelta, void* param)
{
    t_fractal *f;
    f = param;
    (void)xdelta;

    int x, y;
    mlx_get_mouse_pos(f->mlx, &(x), &(y));

	if (ydelta > 0)
	{
		zoom(f, 0.5);
		x -= (f->n*4)  / 2;
		y -= (f->n*4)  / 2;
		if (x < 0)
			move(f, (double)x * -1 / (f->n*4) , 'L');
		else if (x > 0)
			move(f, (double)x / (f->n*4) , 'R');
		if (y < 0)
			move(f, (double)y * -1 / (f->n*4) , 'U');
		else if (y > 0)	
			move (f, (double)y / (f->n*4) , 'D');
	}
	else if (ydelta < 0)
		zoom(f, 2);
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