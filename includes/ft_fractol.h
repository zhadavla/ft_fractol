/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:35:55 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/07/10 18:16:40 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"
# include "ft_printf.h"

typedef struct s_fractal
{ 
    mlx_image_t *img;
    mlx_t *mlx;
    double n;
    long long max_iterations;
    double a_real;
    double b_img;
    double julia_x;
    double julia_y;

	  double	min_r;
	  double	max_r;
	  double	min_i;
	  double	max_i;

    double color_shift; 
    char type;
    
} t_fractal;

typedef struct s_color
{
    int r;
    int g;
    int b;
    int tp;
}   t_color;

union       colour_u
{
  unsigned int  number;
  unsigned char channels[4];
};

void draw_julia(void *p);
void draw_mandelbrot(void *p);
void draw_mandelbox(void *p);
void    fractal_init(t_fractal *fractal);
void    ft_error(void);
void ft_print_error();
int32_t    ft_fractal(char *set);

// colors
int foo(int continuous_index);
void    color_shift(void *p);

// hooks
void hook(void *ptr);
void scrollfunc(double xdelta, double ydelta, void* param);


void move_julia(void *ptr);

#endif
