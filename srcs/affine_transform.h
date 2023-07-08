#pragma once

/**
 * Matrix representation of an affine transform
 * | a b c |   | x |
 * | d e f | * | y | 
 * | 0 0 1 |   | 1 |
*/

/**
 * | 1 0 v1 |
 * | 0 1 v2 | > Translation by vector (v1, v2)
 * | 0 0 1  |
*/

typedef struct affine_transform {
    float a, b, c, d, e, f;
} affine_transform_t;

void tranform_to_cartesian(double *x, double *y, double screen_width, double screen_height);
void scale_by_vector(double *x, double *y, double scale);
void translate_by_vector(double *x, double *y, double x_translation, double y_translation);
void apply_affine_transform(double *x, double *y, affine_transform_t affine_transform);