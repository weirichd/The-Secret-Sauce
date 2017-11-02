#ifndef MYMATH_H
#define MYMATH_H

static inline int int_abs(int a) {
    if(a >= 0)
        return a;
    return -a;
}

static inline void swap_int(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

static inline int int_signum(int a) {
    return (a > 0) - (a < 0);
}

static inline void clampf(float *x, float min, float max) {
    if(*x < min)
        *x = min;
    if(*x > max)
        *x = max;
}

// TODO: Optimize this if it becomes an issue
static inline int int_min3(int a, int b, int c) {
    int t = a;
    if (t > b) t = b;
    if (t > c) t = c;

    return t;
}

// TODO: Optimize this if it becomes an issue
static inline int int_max3(int a, int b, int c) {
    int t = a;
    if (t < b) t = b;
    if (t < c) t = c;

    return t;
}

#endif
