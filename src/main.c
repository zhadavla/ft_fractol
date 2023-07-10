/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:55:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/07/10 20:33:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_fractol.h"

int32_t	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!(ft_strncmp(argv[1], "J1", 3)) || !(ft_strncmp(argv[1], "J2", 3))
			|| !(ft_strncmp(argv[1], "J3", 3)) || !(ft_strncmp(argv[1], "M", 2))
			|| !(ft_strncmp(argv[1], "L", 2)))
			return (ft_fr(argv[1]));
		else
			ft_print_error();
	}
	else
		ft_print_error();
	return (0);
}
