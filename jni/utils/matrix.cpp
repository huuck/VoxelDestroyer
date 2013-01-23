/*
 * matrix.c
 * Matrix manipulation functions.
 */

#include "matrix.h"
#include <math.h>

/* 
 * Simulates desktop's glRotatef. The matrix is returned in column-major 
 * order. 
 */
void rotate_matrix(double angle, double x, double y, double z, float *R) {
    double radians, c, s, c1, u[3], length;
    int i, j;

    radians = (angle * M_PI) / 180.0;

    c = cos(radians);
    s = sin(radians);

    c1 = 1.0 - cos(radians);

    length = sqrt(x * x + y * y + z * z);

    u[0] = x / length;
    u[1] = y / length;
    u[2] = z / length;

    for (i = 0; i < 16; i++) {
        R[i] = 0.0;
    }

    R[15] = 1.0;

    for (i = 0; i < 3; i++) {
        R[i * 4 + (i + 1) % 3] = u[(i + 2) % 3] * s;
        R[i * 4 + (i + 2) % 3] = -u[(i + 1) % 3] * s;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            R[i * 4 + j] += c1 * u[i] * u[j] + (i == j ? c : 0.0);
        }
    }
}

void rotate_matrix_y(double angle, float *R) {
	double radians, c, s;
	int i;

	for (i = 0; i < 16; i++) {
		R[i] = 0.0;
	}

	R[0] = 1.0;
	R[5] = 1.0;
	R[10] = 1.0;
	R[15] = 1.0;

	radians = (angle * M_PI) / 180.0;

	c = cos(radians);
	s = sin(radians);

	R[0] = c;
	R[2] = s;
	R[8] = -s;
	R[10] = c;
}

void rotate_then_translate_matrix(double angle, double x, double y, double z, double xt, double yt, double zt, float *R) {
    double radians, c, s, c1, u[3], length;
    int i, j;

    radians = (angle * M_PI) / 180.0;

    c = cos(radians);
    s = sin(radians);

    c1 = 1.0 - cos(radians);

    length = sqrt(x * x + y * y + z * z);

    u[0] = x / length;
    u[1] = y / length;
    u[2] = z / length;

    for (i = 0; i < 16; i++) {
        R[i] = 0.0;
    }

    R[15] = 1.0;
    R[3] = xt;
    R[7] = yt;
    R[11] = zt;

    for (i = 0; i < 3; i++) {
        R[i * 4 + (i + 1) % 3] = u[(i + 2) % 3] * s;
        R[i * 4 + (i + 2) % 3] = -u[(i + 1) % 3] * s;
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            R[i * 4 + j] += c1 * u[i] * u[j] + (i == j ? c : 0.0);
        }
    }
}
/* 
 * Simulates desktop's glRotatef. The matrix is returned in column-major 
 * order. 
 */
void translate_matrix(double xt, double yt, double zt, float *T) {
    for (int i = 0; i < 16; i++) {
        T[i] = 0.0;
    }

    T[0] = 1.0;
    T[5] = 1.0;
    T[10] = 1.0;
    T[15] = 1.0;
    T[12] = xt;
    T[13] = yt;
    T[14] = zt;
}
/* 
 * Simulates gluPerspectiveMatrix 
 */
void perspective_matrix(double fovy, double aspect, double znear, double zfar, float *P) {
    int i;
    double f;

    f = 1.0/tan(fovy * 0.5 * M_PI / 180.0f);

    for (i = 0; i < 16; i++) {
        P[i] = 0.0;
    }

    P[0] = f / aspect;
    P[5] = f;
    P[10] = (znear + zfar) / (znear - zfar);
    P[11] = -1.0;
    P[14] = (2.0 * znear * zfar) / (znear - zfar);
    P[15] = 0.0;
}

/* 
 * Multiplies A by B and writes out to C. All matrices are 4x4 and column
 * major. In-place multiplication is supported.
 */
void multiply_matrix(float *A, float *B, float *C) {
	int i, j, k;
    float aTmp[16];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            aTmp[j * 4 + i] = 0.0;

            for (k = 0; k < 4; k++) {
                aTmp[j * 4 + i] += A[k * 4 + i] * B[j * 4 + k];
            }
        }
    }

    for (i = 0; i < 16; i++) {
        C[i] = aTmp[i];
    }
}

void my_PerspectiveFOV(float fov, float aspect, float near, float far, float* mret) {
	float D2R = M_PI / 180.0;
	float yScale = 1.0 / tan(D2R * fov / 2);
	float xScale = yScale / aspect;
	float nearmfar = near - far;
	float m[] = {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, (far + near) / nearmfar, -1,
        0, 0, 2*far*near / nearmfar, 0
    };
	mret = m;
}

void setLookAtM( float eyeX, float eyeY, float eyeZ,
				 float centerX, float centerY, float centerZ,
				 float upX, float upY, float upZ,
				 float* rm)
{

	// See the OpenGL GLUT documentation for gluLookAt for a description
	// of the algorithm. We implement it in a straightforward way:

	float fx = centerX - eyeX;
	float fy = centerY - eyeY;
	float fz = centerZ - eyeZ;

	// Normalize f
	float rlf = 1.0f / sqrtf(fx * fx + fy * fy + fz * fz);
	fx *= rlf;
	fy *= rlf;
	fz *= rlf;

	// compute s = f x up (x means "cross product")
	float sx = fy * upZ - fz * upY;
	float sy = fz * upX - fx * upZ;
	float sz = fx * upY - fy * upX;

	// and normalize s
	float rls = 1.0f / sqrt(sx * sx + sy * sy + sz * sz);
	sx *= rls;
	sy *= rls;
	sz *= rls;

	// compute u = s x f
	float ux = sy * fz - sz * fy;
	float uy = sz * fx - sx * fz;
	float uz = sx * fy - sy * fx;

	rm[0] = sx;
	rm[1] = ux;
	rm[2] = -fx;
	rm[3] = 0.0f;

	rm[4] = sy;
	rm[5] = uy;
	rm[6] = -fy;
	rm[7] = 0.0f;

	rm[8] = sz;
	rm[9] = uz;
	rm[10] = -fz;
	rm[11] = 0.0f;

	rm[12] = 0.0f;
	rm[13] = 0.0f;
	rm[14] = 0.0f;
	rm[15] = 1.0f;

	float mTranslate[16];

	translate_matrix(-eyeX, -eyeY, -eyeZ, mTranslate);

	multiply_matrix(rm, mTranslate, rm);
}
