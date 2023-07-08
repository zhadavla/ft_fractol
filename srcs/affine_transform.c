#include "affine_transform.h"
#include "fractol.h"

void tranform_to_cartesian(double *x, double *y, double screen_width, double screen_height)
{
    *x = *x - screen_width / 2;
    *y = screen_height / 2 - *y;
    // printf("there x: %f, y: %f\n", *x, *y);
}

void apply_affine_transform(double *x, double *y, affine_transform_t affine_transform)
{
    double temp_x = *x;
    double temp_y = *y;

    *x = affine_transform.a * temp_x + affine_transform.b * temp_y + affine_transform.c;
    *y = affine_transform.d * temp_x + affine_transform.e * temp_y + affine_transform.f;
}

void translate_by_vector(double *x, double *y, double x_translation, double y_translation)
{
    printf("traslating by x: %f, y: %f\n", x_translation, y_translation);
    affine_transform_t affine_transform = {
        .a = 1,
        .b = 0,
        .c = x_translation,
        .d = 0,
        .e = 1,
        .f = y_translation
    };

    apply_affine_transform(x, y, affine_transform);
}

void scale_by_vector(double *x, double *y, double scale)
{
    affine_transform_t affine_transform = {
        .a = scale,
        .b = 0,
        .c = 0,
        .d = 0,
        .e = scale,
        .f = 0
    };

    apply_affine_transform(x, y, affine_transform);
}