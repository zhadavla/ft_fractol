/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_frs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:50:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 19:36:53 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

int	calculate_julia(t_fr *f)
{
	int		i;
	double	tmp;

	i = 0;
	while (i <= f->max_iterations)
	{
		if ((f->b_img * f->b_img + f->a_real * f->a_real) > 4.0)
			break ;
		tmp = 2 * f->a_real * f->b_img + f->julia_y;
		f->a_real = f->a_real * f->a_real - f->b_img * f->b_img + f->julia_x;
		f->b_img = tmp;
		i++;
	}
	return (i);
}

int	calculate_mandelbrot(t_fr *f, int x, int y)
{
	int		i;
	double	tmp;
	double	mr;
	double	mi;

	i = 0;
	mr = f->min_r + (double)x * (f->max_r - f->min_r) / f->w_size;
	mi = f->max_i + (double)y * (f->min_i - f->max_i) / f->w_size;
	f->a_real = 0;
	f->b_img = 0;
	while (i <= f->max_iterations)
	{
		if ((f->b_img * f->b_img + f->a_real * f->a_real) > 4.0)
			break ;
		tmp = 2 * f->a_real * f->b_img + mi;
		f->a_real = f->a_real * f->a_real - f->b_img * f->b_img + mr;
		f->b_img = tmp;
		i++;
	}
	return (i);
}
