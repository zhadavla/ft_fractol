#pragma once

//  gcc src/main.c libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "affine_transform.h"

typedef struct s_fractal
{
    double old_zoom; 
    mlx_image_t *img;
    double img_w;
    long long max_iterations;
    double img_h;
    mlx_t *mlx;
    int x_coord;
    int y_coord;
    double a_real;
    double b_img;
    double n;
    double julia_x;
    double julia_y;
    double zoom;
    double offset_x;
    double offset_y;
    double previous_offset_x;
    double previous_offset_y;
} t_fractal;

typedef struct s_color
{
    int r;
    int g;
    int b;
    int tp;
} t_color;

void draw_julia(void *p);
void draw_mandelbrot(void *p);
int get_color(int continuous_index);
void    fractal_init(t_fractal *fractal);
void my_scrollhook(double xdelta, double ydelta, void* param);
void hook(void *ptr);
void move_julia(void *ptr);