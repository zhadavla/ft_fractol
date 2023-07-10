/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:09:57 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 18:32:24 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

//  colors
int	foo(int continuous_index)
{
	union colour_u	c;

	c.channels[0] = (unsigned char)(sin(0.016 * continuous_index + 4) * 125
		+ 223);
	c.channels[1] = (unsigned char)(sin(0.013 * continuous_index + 2) * 125
		+ 223);
	c.channels[2] = (unsigned char)(sin(0.01 * continuous_index + 1) * 125
		+ 223);
	c.channels[3] = 255; // alpha bit
	return (c.number);
}

void	color_shift(void *p)
{
	t_fractal *f;
	f = p;

	if (mlx_is_key_down(f->mlx, MLX_KEY_SPACE))
		f->color_shift++;
}