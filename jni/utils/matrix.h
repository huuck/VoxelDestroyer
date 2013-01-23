#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

void rotate_matrix(double angle, double x, double y, double z, float *R);
void rotate_then_translate_matrix(double angle, double x, double y, double z, double xt, double yt, double zt, float *R);
void translate_matrix(double xt, double yt, double zt, float *T);
void perspective_matrix(double fovy, double aspect, double znear, double zfar, float *P);
void multiply_matrix(float *A, float *B, float *C);
void rotate_matrix_y(double angle, float *T);
void my_PerspectiveFOV(float fov, float aspect, float near, float far, float* mret);
void setLookAtM(float eyeX, float eyeY, float eyeZ,float centerX, float centerY, float centerZ,float upX, float upY, float upZ, float* rm);

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif /* M_PI */

#endif
