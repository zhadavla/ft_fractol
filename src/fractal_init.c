/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:49:57 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 19:36:53 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

void	fr_init(t_fr *fr)
{
	fr->w_size = 400;
	fr->max_iterations = 1000;
	fr->julia_x = -0.7269;
	fr->julia_y = 0.1889;
	fr->min_i = -2.0;
	fr->min_r = -2.0;
	fr->max_r = 2.0;
	fr->max_i = 2.0;
	fr->color_shift = 0;
}
