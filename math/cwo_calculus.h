#ifndef CWO_CALCULUS_H
#define CWO_CALCULUS_H

#include <stdlib.h>
#include <math.h>

/*
You can change type of calcrix variables 
 */
//#define CWO_CALC_VAL_TYPE_INT
//#define CWO_CALC_VAL_TYPE_LONG_LONG
#define CWO_CALC_VAL_TYPE_FLOAT 
//#define CWO_CALC_VAL_TYPE_DOUBLE

#if (!defined(CWO_CALC_VAL_TYPE_INT) && !defined(CWO_CALC_VAL_TYPE_LONG_LONG) && !defined(CWO_CALC_VAL_TYPE_FLOAT) && !defined(CWO_CALC_VAL_TYPE_DOUBLE))
    #error CWO_CALC_VAL_TYPE can not be defined
#endif


#ifdef CWO_CALC_VAL_TYPE_INT
    #define CWO_CALC_VAL_TYPE_ZERO 0
    #define CWO_CALC_VAL_TYPE_ONE 1
    #define CWO_CALC_VAL_TYPE_TWO 2
    #define CWO_CALC_VAL_TYPE_THREE 3
    #define CWO_CALC_VAL_TYPE_FOUR 3
    #define DIFF 1
    #define CWO_CALC_VAL_TYPE int
    #define CWO_PRINT(v) printf("%d ", (v))
#endif

#ifdef CWO_CALC_VAL_TYPE_LONG_LONG
    #define CWO_CALC_VAL_TYPE_ZERO 0
    #define CWO_CALC_VAL_TYPE_ONE 1
    #define CWO_CALC_VAL_TYPE_TWO 2
    #define CWO_CALC_VAL_TYPE_THREE 3
    #define CWO_CALC_VAL_TYPE_FOUR 4
    #define CWO_DIFF 1
    #define CWO_CALC_VAL_TYPE long long
    #define CWO_PRINT(v) printf("%lld ", (v))
#endif

#ifdef CWO_CALC_VAL_TYPE_FLOAT
    #define CWO_CALC_VAL_TYPE_ZERO 0.0f
    #define CWO_CALC_VAL_TYPE_ONE 1.0f
    #define CWO_CALC_VAL_TYPE_TWO 2.0f
    #define CWO_CALC_VAL_TYPE_THREE 3.0f
    #define CWO_CALC_VAL_TYPE_FOUR 4.0f
    #define CWO_DIFF 1e-3f
    #define CWO_CALC_VAL_TYPE float
    #define CWO_PRINT(v) printf("%.2f ", (v))
#endif

#ifdef CWO_CALC_VAL_TYPE_DOUBLE
    #define CWO_CALC_VAL_TYPE_ZERO 0.0
    #define CWO_CALC_VAL_TYPE_ONE 1.0
    #define CWO_CALC_VAL_TYPE_TWO 2.0
    #define CWO_CALC_VAL_TYPE_THREE 3.0
    #define CWO_CALC_VAL_TYPE_FOUR 4.0
    #define CWO_DIFF 1e-3
    #define CWO_CALC_VAL_TYPE double
    #define CWO_PRINT(v) printf("%.2lf ", (v))
#endif


#define PI 3.1415

CWO_CALC_VAL_TYPE cwo_calc_derivate(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE), 
                                    CWO_CALC_VAL_TYPE val);
CWO_CALC_VAL_TYPE cwo_calc_rieman(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1);
CWO_CALC_VAL_TYPE cwo_calc_trapezoid(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1);
CWO_CALC_VAL_TYPE cwo_calc_simpson(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1);

CWO_CALC_VAL_TYPE (*cwo_calc_integral)(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1) = cwo_calc_simpson;

                                    

#ifdef CWO_CALCULUS_IMPLEMENTATIONS


CWO_CALC_VAL_TYPE cwo_calc_derivate(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE), 
                                    CWO_CALC_VAL_TYPE val)
{
    CWO_CALC_VAL_TYPE delta = f(val + CWO_DIFF) - f(val);
    return delta / CWO_DIFF;
}


CWO_CALC_VAL_TYPE cwo_calc_rieman(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1)
{
    CWO_CALC_VAL_TYPE sum = CWO_CALC_VAL_TYPE_ZERO;
    for(CWO_CALC_VAL_TYPE i = x0; i < x1; i += CWO_DIFF){
        sum += f(i)*CWO_DIFF;
    }
    return sum;
}



CWO_CALC_VAL_TYPE cwo_calc_trapezoid(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1)
{
    CWO_CALC_VAL_TYPE mid = CWO_CALC_VAL_TYPE_ZERO;

    for(CWO_CALC_VAL_TYPE i = x0 + CWO_DIFF; i < x1 - CWO_DIFF; i += CWO_DIFF){
        mid += f(i);
    }
    CWO_CALC_VAL_TYPE sum = CWO_DIFF*(f(x0) + f(x1) + 
                            CWO_CALC_VAL_TYPE_TWO*mid)
                            /CWO_CALC_VAL_TYPE_TWO;
    return sum;
}


CWO_CALC_VAL_TYPE cwo_calc_simpson(CWO_CALC_VAL_TYPE (*f)(CWO_CALC_VAL_TYPE),
                                    CWO_CALC_VAL_TYPE x0, 
                                    CWO_CALC_VAL_TYPE x1)
{
    CWO_CALC_VAL_TYPE odds = CWO_CALC_VAL_TYPE_ZERO;
    CWO_CALC_VAL_TYPE evens = CWO_CALC_VAL_TYPE_ZERO;
    
    // evens
    CWO_CALC_VAL_TYPE even_gap = CWO_DIFF + CWO_DIFF;
    for(CWO_CALC_VAL_TYPE i = even_gap; i < x1 - even_gap; i += even_gap){
        evens += f(i);
    }

    // odds
    for(CWO_CALC_VAL_TYPE i = CWO_DIFF; i < x1 - CWO_DIFF; i += even_gap){
        odds += f(i);
    }

    CWO_CALC_VAL_TYPE sum = CWO_DIFF*(f(x0) + f(x1) + 
                            CWO_CALC_VAL_TYPE_FOUR*odds + 
                            CWO_CALC_VAL_TYPE_TWO*evens)
                            /CWO_CALC_VAL_TYPE_THREE;
    return sum;
}


// TODO: derivative of a function f with Taylor Series
// TODO: convergence tests for infinite sequences
// TODO: Polar and Cartesian coordinate systems
// TODO: operations on polar coordinates

#endif //CWO_CALCULUS_IMPLEMENTATIONS

#endif //CWO_CALCULUS_H