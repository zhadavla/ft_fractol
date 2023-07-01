#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
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
    double zoom;
    double offset_x;
    double offset_y;
} t_fractal;

typedef struct s_color
{
    int r;
    int g;
    int b;
    int tp;
}   t_color;

void draw_julia(void *p);

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
                mlx_put_pixel(fractal->img, fractal->x_coord , fractal->y_coord, 0x000000FF * i); //white
            fractal->x_coord++;
        }
        fractal->x_coord = 0;
        fractal->y_coord++;
    }
    mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
}


//////////////////////////////// tmp ////////////////////////////

union       colour_u
{
  unsigned int  number;
  unsigned char channels[4];
};


int foo(int continuous_index){
    union colour_u     c;

    c.channels[0] = (unsigned char)(sin(0.016 * continuous_index + 4) * 230 + 25);
    c.channels[1] = (unsigned char)(sin(0.013 * continuous_index + 2) * 230 + 25);
    c.channels[2] = (unsigned char)(sin(0.01 * continuous_index + 1) * 230 + 25);
    c.channels[3] = 255; //alpha bit

    return c.number;
}

//////////////////////////////// tmp ////////////////////////////

void my_scrollhook(double xdelta, double ydelta, void* param)
{
    t_fractal *fractal;

    fractal = param;

    int x, y;
    // mlx_get_mouse_pos(fractal->mlx, &(x), &(y));


    // if (ydelta < 0 && fractal->zoom > 1 && x >= 0
	// 	&& x <= 511 && y >= 0 && y <= 511)
	// {
	// 	fractal->zoom -= 1;
	// 	fractal->offset_x *= 1.25;
	// }
	// if (ydelta > 0 && fractal->zoom < 256 && x >= 0
	// 	&& x <= 511 && y >= 0 && y <= 511)
	// {
	// 	fractal->zoom += 1;
	// 	fractal->offset_y *= 1.25;
	// }

    // fractal->offset_x =  x/1000.;
    // fractal->offset_y=  y/1000.;
    // printf(" x = %, y = %d\n", fractal->x_coord , fractal->y_coord );
	// // Simple up or down detection.
	if (ydelta > 0)
    {
        // puts("Up!");
		fractal->zoom --;
        // printf("%f", fractal->zoom);
    }
	else if (ydelta < 0)
    {
        // puts("Down!");
		fractal->zoom ++;
    }
    // fractal->y_coord = 0;
    // fractal->x_coord = 0; 
    // draw_julia(fractal);
	// // Can also detect a mousewheel that goes along the X (e.g: MX Master 3)
	// if (xdelta < 0)
	// 	puts("Sliiiide to the left!");
	// else if (xdelta > 0)
	// 	puts("Sliiiide to the right!");
}

void hook(void *ptr){
    t_fractal *fr;
    fr = ptr;

    if (mlx_is_key_down(fr->mlx, MLX_KEY_LEFT)){
        fr->offset_x += 0.4;
        printf("%f", fr->offset_x );
		puts("MLX_KEY_LEFT ");
    }
    else    if (mlx_is_key_down(fr->mlx, MLX_KEY_RIGHT)){
        fr->offset_x -= 0.4;
        
        puts("MLX_KEY_RIGHT ");
    }
    else if (mlx_is_key_down(fr->mlx, MLX_KEY_UP)){
        fr->offset_y += 0.4;
        puts("MLX_KEY_UP ");
    }
     else if (mlx_is_key_down(fr->mlx, MLX_KEY_DOWN)){
        fr->offset_y -= 0.4;
        puts("MLX_KEY_DOWN ");
    }

}

// void my_keyhook(mlx_key_data_t keydata, void* param)
// {
// 	// I
//     t_fractal *fr;
//     fr = param;


// 	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS){
//         fr->offset_x += 0.4;
//         printf("%f", fr->offset_x );
// 		puts("MLX_KEY_LEFT ");
//     }
//     else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS){
//         fr->offset_x -= 0.4;
        
//         puts("MLX_KEY_RIGHT ");
//     }
//     else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS){
//         fr->offset_y += 0.4;
//         puts("MLX_KEY_UP ");
//     }
//     else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS){
//         fr->offset_y -= 0.4;
//         puts("MLX_KEY_DOWN ");
//     }
//     // draw_julia(fr);
// }

// ================================ JULIA ===========================
void draw_julia(void *p)
{
    t_fractal *fractal;
    fractal = p;

    fractal->y_coord = 0;
    fractal->x_coord = 0; 
    double x;
    double y;
    double temp;
    int i;
    
    printf("++++");
    while (fractal->y_coord < 4 * fractal->n)
    {
        y = 2 - (fractal->y_coord / fractal->n);
        while (fractal->x_coord < 4 * fractal->n)
        {
            x = - 2 + (fractal->x_coord / fractal->n);
            
            fractal->a_real = x/fractal->zoom - fractal->offset_x;
            fractal->b_img = y/fractal->zoom - fractal->offset_y;
            i = 1;
            while(i <= fractal->max_iterations)
            {
                printf("x: %f, y: %f--------------\n", fractal->offset_x, fractal->offset_y);
                temp = fractal->a_real;
                fractal->a_real = (fractal->a_real * fractal->a_real) - (fractal->b_img * fractal->b_img) + fractal->julia_x;
                fractal->b_img = (2 * temp * fractal->b_img) + fractal->julia_y;
                if ((fractal->a_real * fractal->a_real) + (fractal->b_img * fractal->b_img) > 4)
                    break; 
                i++;
            }
            if (i == fractal->max_iterations + 1)
                mlx_put_pixel(fractal->img, fractal->x_coord, fractal->y_coord, 0x000000FF); //black
            else
                mlx_put_pixel(fractal->img, fractal->x_coord, fractal->y_coord,  0xFFFFFFFF); //white
                // mlx_put_pixel(fractal->img, fractal->x_coord, fractal->y_coord,  foo(i + 250)); //white
            fractal->x_coord++;
        }
        fractal->x_coord = 0;
        fractal->y_coord++;
    }
    mlx_image_to_window(fractal->mlx, fractal->img, 0, 0);
}

void    fractal_init(t_fractal *fractal)
{
    fractal->n = 110;
    fractal->max_iterations = 42;
    fractal->x_coord = 0;
    fractal->y_coord = 0;
    fractal->julia_x = -0.70176;
    fractal->julia_y = -0.3842;
    fractal->zoom = 1;
    fractal->offset_y = 0;
    fractal->offset_x = 0;
}

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(int argc, char **argv)
{
    t_fractal *fractal;

    fractal = malloc(sizeof(t_fractal));

    fractal_init(fractal);
	// mlx_set_setting(MLX_MAXIMIZED, true);
	fractal->mlx = mlx_init(fractal->n * 4, fractal->n * 4, "Fract", true);
	if (!fractal->mlx)
		ft_error();
	fractal->img = mlx_new_image(fractal->mlx, fractal->n * 4, fractal->n * 4);
	if (!fractal->img || (mlx_image_to_window(fractal->mlx, fractal->img, 0, 0) < 0))
		ft_error();

    // draw_mandelbrot(&fractal);

    // mlx_loop_hook(fractal->mlx, mouse_hook, &fractal);

    // mlx_key_hook(fractal->mlx, &my_keyhook, &fractal);
    mlx_scroll_hook(fractal->mlx, &my_scrollhook, &fractal);
    // draw_julia(&fractal);
    mlx_loop_hook(fractal->mlx, draw_julia, fractal);
    mlx_loop_hook(fractal->mlx, hook, fractal);
	mlx_loop(fractal->mlx);
	// mlx_delete_image(fractal->mlx, fractal->img);
	mlx_terminate(fractal->mlx);
	return (EXIT_SUCCESS);
}