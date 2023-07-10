/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:49:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 19:49:23 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

void	hook(void *ptr)
{
	t_fr	*f;

	f = ptr;
	if (mlx_is_key_down(f->mlx, MLX_KEY_LEFT))
	{
		f->min_r -= (f->max_r - f->min_r) * 0.04;
		f->max_r -= (f->max_r - f->min_r) * 0.04;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_RIGHT))
	{
		f->min_r += (f->max_r - f->min_r) * 0.04;
		f->max_r += (f->max_r - f->min_r) * 0.04;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_UP))
	{
		f->min_i += (f->max_i - f->min_i) * 0.04;
		f->max_i += (f->max_i - f->min_i) * 0.04;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_DOWN))
	{
		f->min_i -= (f->max_i - f->min_i) * 0.04;
		f->max_i -= (f->max_i - f->min_i) * 0.04;
	}
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
}

static void	zoom(t_fr *f, double zoom)
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

static void	move(t_fr *f, double distance, char direction)
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

void	scrollfunc(double xdelta, double ydelta, void *param)
{
	t_fr	*f;
	int		x;
	int		y;

	f = param;
	(void)xdelta;
	mlx_get_mouse_pos(f->mlx, &(x), &(y));
	if (ydelta > 0)
	{
		zoom(f, 0.5);
		x -= f->w_size / 2;
		y -= f->w_size / 2;
		if (x < 0)
			move(f, (double)x * -1 / f->w_size, 'L');
		else if (x > 0)
			move(f, (double)x / f->w_size, 'R');
		if (y < 0)
			move(f, (double)y * -1 / f->w_size, 'U');
		else if (y > 0)
			move(f, (double)y / f->w_size, 'D');
	}
	else if (ydelta < 0)
		zoom(f, 2);
}

void	move_julia(void *ptr)
{
	t_fr	*fr;

	fr = ptr;
	if (mlx_is_key_down(fr->mlx, MLX_KEY_Z))
		fr->julia_x -= 0.005;
	if (mlx_is_key_down(fr->mlx, MLX_KEY_X))
		fr->julia_x += 0.005;
	if (mlx_is_key_down(fr->mlx, MLX_KEY_C))
		fr->julia_y += 0.01;
	if (mlx_is_key_down(fr->mlx, MLX_KEY_V))
		fr->julia_y -= 0.01;
}
