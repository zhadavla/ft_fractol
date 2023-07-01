#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../MLX42/include/MLX42/MLX42.h"

//  gcc src/main.c libmlx42.a -Iinclude -ldl -lglfw -pthread -lm 

typedef struct s_fractal
{
    
    mlx_image_t *img;
    int img_w;
    long long max_iterations;
    int img_h;
    mlx_t *mlx;
    int x_coord;
    int y_coord;
    double a_real;
    double b_img;
    double n;
    double julia_x;
    double julia_y;
} t_fractal;


// ================================ MANDELBROT ===========================
void draw_mandelbrot(t_fractal *fractal)
{
    double x;
    double y;
    double temp;
    int i;
    
    while (fractal->y_coord < 4 * fractal->n)
    {
        y = 2 - (fractal->y_coord / fractal->n);
        
        while (fractal->x_coord < 4 * fractal->n)
        {
            x = - 2 + (fractal->x_coord / fractal->n);
            fractal->a_real = x;
            fractal->b_img = y;
            i = 1;
            while(i <= fractal->max_iterations)
            {
                temp = fractal->a_real;
                fractal->a_real = (fractal->a_real * fractal->a_real) - (fractal->b_img * fractal->b_img) + x;
                fractal->b_img = (2 * temp * fractal->b_img) + y;
                if ((fractal->a_real * fractal->a_real) + (fractal->b_img * fractal->b_img) > 16)
                    break; 
                i++;
            }
            if (i == fractal->max_iterations + 1)
                mlx_put_pixel(fractal->img, fractal->x_coord , fractal->y_coord, 0xFFFFFFFF); //black
            else
                mlx_put_pixel(fractal->img, fractal->x_coord , fractal->y_coord, 0x000000FF); //white
            fractal->x_coord++;
        }
        fractal->x_coord = 0;
        fractal->y_coord++;
    }
}

// ================================ JULIA ===========================
void draw_julia(t_fractal *fractal)
{
    double x;
    double y;
    double temp;
    int i;
    
    while (fractal->y_coord < 4 * fractal->n)
    {
        y = 2 - (fractal->y_coord / fractal->n);
        
        while (fractal->x_coord < 4 * fractal->n)
        {
            x = - 2 + (fractal->x_coord / fractal->n);
            fractal->a_real = x;
            fractal->b_img = y;
            i = 1;
            while(i <= fractal->max_iterations)
            {
                temp = fractal->a_real;
                fractal->a_real = (fractal->a_real * fractal->a_real) - (fractal->b_img * fractal->b_img) + fractal->julia_x;
                fractal->b_img = (2 * temp * fractal->b_img) + fractal->julia_y;
                if ((fractal->a_real * fractal->a_real) + (fractal->b_img * fractal->b_img) > 16)
                    break; 
                i++;
            }
            if (i == fractal->max_iterations + 1)
                mlx_put_pixel(fractal->img, fractal->x_coord , fractal->y_coord, 0xFFFFFFFF); //black
            else
                mlx_put_pixel(fractal->img, fractal->x_coord , fractal->y_coord, 0x000000FF); //white
            fractal->x_coord++;
        }
        fractal->x_coord = 0;
        fractal->y_coord++;
    }
}

void    fractal_init(t_fractal *fractal)
{
    fractal->n = 100;
    fractal->max_iterations = 1000;
    fractal->x_coord = 0;
    fractal->y_coord = 0;
    fractal->julia_x = -0.035;
    fractal->julia_y = -0.745429;
}

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
    t_fractal fractal;

    fractal_init(&fractal);
	// mlx_set_setting(MLX_MAXIMIZED, true);
	fractal.mlx = mlx_init(fractal.n * 4, fractal.n * 4, "Fract", true);
	if (!fractal.mlx)
		ft_error();
	fractal.img = mlx_new_image(fractal.mlx, fractal.n * 4, fractal.n * 4);
	if (!fractal.img || (mlx_image_to_window(fractal.mlx, fractal.img, 0, 0) < 0))
		ft_error();

    // draw_mandelbrot(&fractal);
    draw_julia(&fractal);
    mlx_image_to_window(fractal.mlx, fractal.img, 0, 0);

	mlx_loop(fractal.mlx);
	mlx_delete_image(fractal.mlx, fractal.img);
	mlx_terminate(fractal.mlx);
	return (EXIT_SUCCESS);
}