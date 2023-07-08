#include "fractol.h"

void draw_julia(void *p);

// ================================ MANDELBROT ===========================

//////////////////////////////// tmp ////////////////////////////

union colour_u
{
  unsigned int number;
  unsigned char channels[4];
};

int get_color(int continuous_index)
{
  union colour_u c;

  c.channels[0] = (unsigned char)(sin(0.016 * continuous_index + 4) * 230 + 25);
  c.channels[1] = (unsigned char)(sin(0.013 * continuous_index + 2) * 230 + 25);
  c.channels[2] = (unsigned char)(sin(0.01 * continuous_index + 1) * 230 + 25);
  c.channels[3] = 255; // alpha bit

  return c.number;
}



//////////////////////////////// tmp ////////////////////////////

// Oh, found a GIF. Try this:
// mOffset = event->pos() - float(mZoomLevel) / float(oldZoomLevel) * (event->pos() - mOffset);

//
// void hook_tmp(void *ptr){
//     t_fractal *fr;
//     fr = ptr;
//     int x, y;
//     mlx_get_mouse_pos(fr->mlx, &(x), &(y));
//     if (x < 0 || y < 0 || x > 600 || y > 600)
//         return ;
//     printf("x = %d, y = %d\n", x, y);
//     // double x1 = x - 300;
//     // double y1 = y - 300;
//     // printf("x = %f, y = %f\n", x1, y1);

//     // double middle_point_y =  fr->img_h / 2;
//     // double middle_point_x =  fr->img_w / 2;

//     // printf("middle_point_x = %f, middle_point_y = %f\n", middle_point_x, middle_point_y);
//     if (mlx_is_key_down(fr->mlx, MLX_KEY_A))
//     {
//         fr->zoom ++;
//         // fr->offset_x += 469 / fr->zoom / 600.;
//         // fr->offset_y += 260 / fr->zoom / 600.;
//         // fr->zoom ++;
//         // fr->offset_x += x1 / 600.;
//         // fr->offset_y += y1 / 600.;
//         // printf("offset_x = %f, offset_y = %f\n", fr->offset_x, fr->offset_y);
//         draw_julia(fr);
//     }
// }
// 469 260

static void ft_error(void)
{
  fprintf(stderr, "%s", mlx_strerror(mlx_errno));
  exit(EXIT_FAILURE);
}

void tmp_hook(void *ptr){
  t_fractal *fractal;

  fractal = ptr;
  if (mlx_is_key_down(fractal->mlx, MLX_KEY_A))
  {
   translate_by_vector(&(fractal->offset_x), &(fractal->offset_y), 0.54, 0.45);
  }
}

int32_t main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

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

  mlx_loop_hook(fractal->mlx, tmp_hook, fractal);
  mlx_scroll_hook(fractal->mlx, &my_scrollhook, fractal);
  mlx_loop_hook(fractal->mlx, move_julia, fractal);
  mlx_loop_hook(fractal->mlx, hook, fractal);
  mlx_loop_hook(fractal->mlx, draw_julia, fractal);
  mlx_loop(fractal->mlx);
  // mlx_delete_image(fractal->mlx, fractal->img);
  mlx_terminate(fractal->mlx);
  return (EXIT_SUCCESS);
}