#ifndef MYMATH_H
#define MYMATH_H

static inline int int_abs(int a) {
    if( a >= 0)
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

#endif
