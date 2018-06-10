#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Vector3f {
    float x, y, z;
} Vector3f;

typedef struct Matrix3x3f {
    float m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22;
} Matrix3x3f;

// Compute Av
static void matrix_vector_mul3f(Vector3f *result, const Matrix3x3f *const A, const Vector3f *const v) {
    // Use temporary variables just in case result == v
    float x = v->x;
    float y = v->y;
    float z = v->z;

    result->x = A->m00 * x + A->m10 * y + A->m20 * z;
    result->y = A->m01 * x + A->m11 * y + A->m21 * z;
    result->z = A->m02 * x + A->m12 * y + A->m22 * z;
};

// Compute Av + b
static void affine_transform3f(Vector3f *result, const Matrix3x3f *const A, const Vector3f *const b, const Vector3f *const v) {
    matrix_vector_mul3f(result, A, v);
    result->x += b->x;
    result->y += b->y;
    result->z += b->z;
} 

static void perspective_projection(Vector3f *dest, const Vector3f *const src) {
   dest->z = -1.0f / src->z;
   dest->x = src->x * dest->z;
   dest->y = src->y * dest->z;
}

static void load_identity_matrix(Matrix3x3f *dest) {
   memset(dest, 0, sizeof(Matrix3x3f)); 
   dest->m00 = dest->m11 = dest->m22 = 1.0f;
}

// Operate in place on an array of verticies by an affine transform. 
// If b is NULL, then only matrix multiply
static void transform_vectors(Vector3f *vs, size_t count, const Matrix3x3f *const A, const Vector3f *const b) {
    for(int i = 0; i < count; i++) {
        if(b) 
            affine_transform3f(&vs[i], A, b, &vs[i]);
        else
            matrix_vector_mul3f(&vs[i], A, &vs[i]);
         
    }
}

static void print_vect(const Vector3f *v) {
    printf("(%f, %f, %f)", v->x, v->y, v->z);
}


#endif
