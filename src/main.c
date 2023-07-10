#include "../includes/ft_fractol.h"

// ================================ JULIA ===========================

void draw_julia(void *p)
{
    t_fractal *f;
    f = p;

    int x, y;
    int i;
    double	tmp;

    y = 0;
    while (y < 4 * f->n)
    {
        x = 0;
        while (x < 4 * f->n)
        {
			f->a_real = f->min_r + (double)x * (f->max_r - f->min_r) / (f->n * 4);
			f->b_img = f->max_i + (double)y * (f->min_i - f->max_i) / (f->n * 4);

            i = 1;
            while (i <= f->max_iterations)
            {
                if ((f->b_img * f->b_img + f->a_real * f->a_real) > 4.0)
                    break ;
                tmp = 2 * f->a_real * f->b_img + f->julia_y;
                f->a_real = f->a_real * f->a_real - f->b_img * f->b_img + f->julia_x;
                f->b_img = tmp;
                i++;
            }
            if (i == f->max_iterations + 1)
                mlx_put_pixel(f->img, x, y, foo(i + f->color_shift)); //black
            else
                mlx_put_pixel(f->img, x, y,  foo(i + f->color_shift + 100)); //colored
            x++;
        }
        y++;
    }
    mlx_image_to_window(f->mlx, f->img, 0, 0);
}


// ================================ MANDELBROT ===========================

void draw_mandelbrot(void *p)
{
    t_fractal *f;
    f = p;

    int x, y;
    int i;
    double	tmp;
    double mr, mi;

    y = 0;
    while (y < 4 * f->n)
    {
        x = 0;
        while (x < 4 * f->n)
        {
			mr = f->min_r + (double)x * (f->max_r - f->min_r) / (f->n * 4);
			mi = f->max_i + (double)y * (f->min_i - f->max_i) / (f->n * 4);
            f->a_real = 0;
            f->b_img = 0;
            i = 1;
            while (i <= f->max_iterations)
            {
                if ((f->b_img * f->b_img + f->a_real * f->a_real) > 4.0)
                    break ;
                tmp = 2 * f->a_real * f->b_img + mi;
                f->a_real = f->a_real * f->a_real - f->b_img * f->b_img + mr;
                f->b_img = tmp;
                i++;
            }
            if (i == f->max_iterations + 1)
                mlx_put_pixel(f->img, x, y, foo(i + f->color_shift)); //black
            else
                mlx_put_pixel(f->img, x, y,  foo(i + f->color_shift + 200)); //colored
            x++;
        }
        y++;
    }
    mlx_image_to_window(f->mlx, f->img, 0, 0);
}

// =========================== MANDELBOX ==========================

// v = s*ballFold(r, f*boxFold(v)) + c

double boxFold(double v)
{
    if (v > 1.0)
        v = 2.0 - v;
    else if (v < -1.0)
        v = - 2.0 - v;
    return (v);
}

double magnitude(double m, double v)
{
    double scale = -1.1;
    if (m < 0.5)
        v *= 4;
    else if (m < 1.0)
        v = v / (m * m);
    else
        v = scale * v;
    return (v);
}

void draw_mandelbox(void *p)
{
    t_fractal *f;
    f = p;
    int x, y;
    int i;
    double mr, mi;
    double vx, vy;
    double scale = 2.0;
    double mag;

    y = 0;
    while (y < 4 * f->n)
    {
        x = 0;
        while (x < 4 * f->n)
        {
			mr = f->min_r + (double)x * (f->max_r - f->min_r) / (f->n * 4);
			mi = f->max_i + (double)y * (f->min_i - f->max_i) / (f->n * 4);
            vx = mr;
            vy = mi;
            i = 1;
            while (i <= f->max_iterations)
            {
                vx = boxFold(vx);
                vy = boxFold(vy);
                mag = sqrt(vx*vx + vy*vy);
                if (vx*vx + vy*vy > 4.0)
                    break;
                vx = scale * magnitude(mag, vx) + mr;
                vy = scale * magnitude(mag, vy) + mi;
                i++;
            }
            if (i == f->max_iterations + 1)
                mlx_put_pixel(f->img, x, y, foo(i + f->color_shift)); //black
            else
                mlx_put_pixel(f->img, x, y,  foo(i + f->color_shift + 100)); //colored
            x++;
        }
        y++;
    }
    mlx_image_to_window(f->mlx, f->img, 0, 0);
}


int32_t    ft_fractal(char *set)
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

    mlx_loop_hook(fractal->mlx, hook, fractal);

    if (set[0] == 'J'){

        if (set[1] == '1')
        {
            fractal->julia_x = 0.285;
            fractal->julia_y = 0.01;
        } else if (set[1] == '2')
        {
            fractal->julia_x = 0.0;
            fractal->julia_y = 0.8;
        } else if (set[1] == '3'){
            fractal->julia_x = -0.8;
            fractal->julia_y = 0.156;
        }
        fractal->type = 'J';
        mlx_loop_hook(fractal->mlx, draw_julia, fractal);
    }
    else if (set[0] == 'M')
    {
        fractal->type = 'M';
        mlx_loop_hook(fractal->mlx, draw_mandelbrot, fractal);
    }
    else if (set[0] == 'B')
    {
        fractal->type = 'B';
        mlx_loop_hook(fractal->mlx, draw_mandelbox, fractal);
    }
        
    mlx_scroll_hook(fractal->mlx, scrollfunc, fractal);
    mlx_loop_hook(fractal->mlx, color_shift, fractal);
    mlx_loop_hook(fractal->mlx, move_julia, fractal);
	mlx_loop(fractal->mlx);
	mlx_delete_image(fractal->mlx, fractal->img);
    mlx_close_window(fractal->mlx);
	mlx_terminate(fractal->mlx);
    free(fractal);
    return (EXIT_SUCCESS);
}

void ft_print_error()
{
    ft_printf("\nWrong input!\n");
    ft_printf("\n===== Available Fractal Sets =====\n\n");    
    ft_printf("Type M to display Mandelbrot set\n");
    ft_printf("Type J1, J2 or J3 to display Julia set\n");
    ft_printf("Type B to display Mandelbox set\n\n"); 

    ft_printf("===== Additional features ======\n]n");
    ft_printf("Z, X, C and V: change Julia set parameters\n");
    ft_printf("SPACE KEY: color shift\n");
    ft_printf("ARROWS KEYS: move the view\n");
    ft_printf("MOUSE SCROLL: zoom in and out\n\n");
}

int32_t	main(int argc, char **argv)
{
    if (argc == 2)
    {
        if (!(ft_strncmp(argv[1], "J1", 3)) || !(ft_strncmp(argv[1], "J2", 3)) 
            || !(ft_strncmp(argv[1], "J3", 3)) 
            || !(ft_strncmp(argv[1], "M", 2)) || !(ft_strncmp(argv[1], "B", 2)))
            return(ft_fractal(argv[1]));
        else 
            ft_print_error();
    }
    else 
        ft_print_error();
    return (0);
}

