/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:09:57 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 19:44:38 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

int	foo(int continuous_index)
{
	union u_colour	c;

	c.channels[0] = (unsigned char)(sin(0.016 * continuous_index + 4) * 125);
	c.channels[1] = (unsigned char)(sin(0.013 * continuous_index + 2) * 125);
	c.channels[2] = (unsigned char)(sin(0.01 * continuous_index + 1) * 125);
	c.channels[3] = 255;
	return (c.number);
}

void	color_shift(void *p)
{
	t_fr	*f;

	f = p;
	if (mlx_is_key_down(f->mlx, MLX_KEY_SPACE))
		f->color_shift++;
}
