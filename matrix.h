#ifndef MATRIX_H
#define MATRIX_H

typedef struct Vector3f {
    float x, y, z;
} Vector3f;

typedef struct Matrix3x3f {
    float m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22;
} Matrix3x3f;

// Compute Av
static void matrix_vector_mul3f(Vector3f *result, Matrix3x3f *A, Vector3f *v) {
    // Use temporary variables just in case result == v
    float x = v->x;
    float y = v->y;
    float z = v->z;

    result->x = A->m00 * x + A->m10 * y + A->m20 * z;
    result->y = A->m01 * x + A->m11 * y + A->m21 * z;
    result->z = A->m02 * x + A->m12 * y + A->m22 * z;
};

// Compute Av + b
static void affine_transform3f(Vector3f *result, Matrix3x3f *A, Vector3f *b, Vector3f *v) {
    matrix_vector_mul3f(result, A, v);
    result->x += b->x;
    result->y += b->y;
    result->z += b->z;
} 

static void perspective_projection(Vector3f *dest, Vector3f *src) {
   dest->z = -1.0f / src->z;
   dest->x = src->x * dest->z;
   dest->y = src->y * dest->z;
}


#endif
