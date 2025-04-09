#ifndef CWO_CALCULUS_H
#define CWO_CALCULUS_H

#include <stdlib.h>
#include <math.h>

/*
You can change type of matrix variables 
 */
//#define CWO_MAT_VAL_TYPE_INT
//#define CWO_MAT_VAL_TYPE_LONG_LONG
#define CWO_MAT_VAL_TYPE_FLOAT 
//#define CWO_MAT_VAL_TYPE_DOUBLE

#if (!defined(CWO_MAT_VAL_TYPE_INT) && !defined(CWO_MAT_VAL_TYPE_LONG_LONG) && !defined(CWO_MAT_VAL_TYPE_FLOAT) && !defined(CWO_MAT_VAL_TYPE_DOUBLE))
    #error CWO_MAT_VAL_TYPE can not be defined
#endif


#ifdef CWO_MAT_VAL_TYPE_INT
    #define CWO_MAT_VAL_TYPE_ZERO 0
    #define CWO_MAT_VAL_TYPE_ONE 1
    #define CWO_MAT_VAL_TYPE int
    #define CWO_PRINT(v) printf("%d ", (v))
#endif

#ifdef CWO_MAT_VAL_TYPE_LONG_LONG
    #define CWO_MAT_VAL_TYPE_ZERO 0
    #define CWO_MAT_VAL_TYPE_ONE 1
    #define CWO_MAT_VAL_TYPE long long
    #define CWO_PRINT(v) printf("%lld ", (v))
#endif

#ifdef CWO_MAT_VAL_TYPE_FLOAT
    #define CWO_MAT_VAL_TYPE_ZERO 0.0f
    #define CWO_MAT_VAL_TYPE_ONE 1.0f
    #define CWO_MAT_VAL_TYPE float
    #define CWO_PRINT(v) printf("%.2f ", (v))
#endif

#ifdef CWO_MAT_VAL_TYPE_DOUBLE
    #define CWO_MAT_VAL_TYPE_ZERO 0.0
    #define CWO_MAT_VAL_TYPE_ONE 1.0
    #define CWO_MAT_VAL_TYPE double
    #define CWO_PRINT(v) printf("%.2lf ", (v))
#endif


#define PI 3.14

CWO_MAT_VAL_TYPE cwo_calc_derivate(CWO_MAT_VAL_TYPE (*func));
CWO_MAT_VAL_TYPE cwo_calc_integral(CWO_MAT_VAL_TYPE (*func));


#ifdef CWO_CALCULUS_IMPLEMENTATIONS





// TODO: derivative of a function f
// TODO: integral of a function f

#endif //CWO_CALCULUS_IMPLEMENTATIONS

#endif //CWO_CALCULUS_H