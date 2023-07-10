/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:26:02 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 20:30:23 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

void	draw_julia(void *p)
{
	t_fr	*f;
	int		i;
	int		x;
	int		y;

	f = p;
	y = 0;
	while (y < f->w_size)
	{
		x = 0;
		while (x < f->w_size)
		{
			f->a_real = f->min_r + (double)x * (f->max_r - f->min_r)
				/ f->w_size;
			f->b_img = f->max_i + (double)y * (f->min_i - f->max_i) / f->w_size;
			i = calculate_julia(f);
			if (i == f->max_iterations + 1)
				mlx_put_pixel(f->img, x, y, foo(i + f->color_shift));
			else
				mlx_put_pixel(f->img, x, y, foo(i + f->color_shift + 100));
			x++;
		}
		y++;
	}
	mlx_image_to_window(f->mlx, f->img, 0, 0);
}

void	draw_mandelbrot(void *p)
{
	t_fr	*f;
	int		i;
	int		x;
	int		y;

	f = p;
	y = 0;
	while (y < f->w_size)
	{
		x = 0;
		while (x < f->w_size)
		{
			i = calculate_mandelbrot(f, x, y);
			if (i == f->max_iterations + 1)
				mlx_put_pixel(f->img, x, y, foo(i + f->color_shift));
			else
				mlx_put_pixel(f->img, x, y, foo(i + f->color_shift + 200));
			x++;
		}
		y++;
	}
	mlx_image_to_window(f->mlx, f->img, 0, 0);
}

void	subrutine(double r, double *x, double *y)
{
	double	temp_x;

	if (r < 0.1)
	{
		*x = 0.0;
		*y = 0.16 * (*y);
	}
	else if (r < 0.86)
	{
		temp_x = *x;
		*x = 0.85 * *x + 0.04 * *y;
		*y = -0.04 * temp_x + 0.85 * *y + 1.6;
	}
	else if (r < 0.93)
	{
		temp_x = *x;
		*x = 0.2 * *x - 0.26 * *y;
		*y = 0.23 * temp_x + 0.22 * *y + 1.6;
	}
	else
	{
		temp_x = *x;
		*x = -0.15 * (*x) + 0.28 * *y;
		*y = 0.26 * temp_x + 0.24 * *y + 0.44;
	}
}

void	draw_leaf(void *p)
{
	t_fr	*f;
	int		i;
	double	r;
	double	x;
	double	y;

	i = 0;
	x = 0.0;
	y = 0.0;
	f = p;
	while (i++ < 100000)
	{
		r = (double)rand() / RAND_MAX;
		subrutine(r, &x, &y);
		mlx_put_pixel(f->img, 400 / 2 + (int)(x * 400 / 11), 400 - (int)(y * 400
				/ 11), 0x00ff00ff);
	}
}
