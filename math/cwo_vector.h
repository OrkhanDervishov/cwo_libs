/*
CWO vector library
Maybe in the future I will fuse 
cwo_matrix.h and cwo_vector.h together
 */
#ifndef CWO_VECTOR_H
#define CWO_VECTOR_H

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

/*
You can change type of vecrix variables 
 */
//#define CWO_VEC_VAL_TYPE_INT
//#define CWO_VEC_VAL_TYPE_LONG_LONG
#define CWO_VEC_VAL_TYPE_FLOAT 
//#define CWO_VEC_VAL_TYPE_DOUBLE

#if (!defined(CWO_VEC_VAL_TYPE_INT) && !defined(CWO_VEC_VAL_TYPE_LONG_LONG) && !defined(CWO_VEC_VAL_TYPE_FLOAT) && !defined(CWO_VEC_VAL_TYPE_DOUBLE))
    #error CWO_VEC_VAL_TYPE can not be defined
#endif


#ifdef CWO_VEC_VAL_TYPE_INT
    #define CWO_VEC_VAL_TYPE_ZERO 0
    #define CWO_VEC_VAL_TYPE_ONE 1
    #define CWO_VEC_VAL_TYPE int
    #define CWO_PRINT(v) printf("%d ", (v))
#endif

#ifdef CWO_VEC_VAL_TYPE_LONG_LONG
    #define CWO_VEC_VAL_TYPE_ZERO 0
    #define CWO_VEC_VAL_TYPE_ONE 1
    #define CWO_VEC_VAL_TYPE long long
    #define CWO_PRINT(v) printf("%lld ", (v))
#endif

#ifdef CWO_VEC_VAL_TYPE_FLOAT
    #define CWO_VEC_VAL_TYPE_ZERO 0.0f
    #define CWO_VEC_VAL_TYPE_ONE 1.0f
    #define CWO_VEC_VAL_TYPE float
    #define CWO_PRINT(v) printf("%.2f ", (v))
#endif

#ifdef CWO_VEC_VAL_TYPE_DOUBLE
    #define CWO_VEC_VAL_TYPE_ZERO 0.0
    #define CWO_VEC_VAL_TYPE_ONE 1.0
    #define CWO_VEC_VAL_TYPE double
    #define CWO_PRINT(v) printf("%.2lf ", (v))
#endif


typedef struct{
    size_t size;
    CWO_VEC_VAL_TYPE* elems;
} Vector;


void cwo_vec_create(Vector* vec, size_t size);
void cwo_vec_delete(Vector vec);
void cwo_vec_resize(Vector vec, CWO_VEC_VAL_TYPE val);
void cwo_vec_randomize(Vector vec);
void cwo_vec_copy(Vector dest, Vector src);
void cwo_vec_print(Vector vec);


void cwo_vec_scale(Vector vec, CWO_VEC_VAL_TYPE scalar);
void cwo_vec_sum(Vector dest, Vector vec);
void cwo_vec_sub(Vector dest, Vector vec);
CWO_VEC_VAL_TYPE cwo_vec_dot(Vector a, Vector b);
void cwo_vec_cross(Vector norm, Vector a, Vector b);


#ifdef CWO_VECTOR_IMPLEMENTATIONS



void cwo_vec_create(Vector* vec, size_t size){
    if (vec->elems != NULL) {
        cwo_vec_delete(*vec);
        printf("Vector already created, previous vector was deleted\n");
    }
    vec->size = size;
    vec->elems = (CWO_VEC_VAL_TYPE*)malloc(size * sizeof(CWO_VEC_VAL_TYPE));
    if (vec->elems == NULL) {
        printf("Memory allocation failed at cwo_vec_create\n");
        exit(1);
    }
}


void cwo_vec_delete(Vector vec){
    if(vec.elems != NULL){
        free(vec.elems);
        vec.elems = NULL;
    }
}


void cwo_vec_resize(Vector vec, CWO_VEC_VAL_TYPE val){
    if(vec.elems == NULL) return;
    
    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] = val;
    }
}


void cwo_vec_randomize(Vector vec){
    if(vec.elems == NULL) return;
    
    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] = (CWO_VEC_VAL_TYPE)rand()/
                        (CWO_VEC_VAL_TYPE)(RAND_MAX/10);;
    }
}


void cwo_vec_copy(Vector dest, Vector src){
    if(dest.elems == NULL || src.elems == NULL) return;
    if(dest.size != src.size) return;

    memcpy(dest.elems, src.elems, sizeof(CWO_VEC_VAL_TYPE) * src.size);
}


void cwo_vec_print(Vector vec){
    if(vec.elems == NULL) return;
    
    printf("[ ");
    for(size_t i = 0; i < vec.size; i++){
        CWO_PRINT(vec.elems[i]);
        printf(" ");
    }
    printf("]");
}




void cwo_vec_scale(Vector vec, CWO_VEC_VAL_TYPE scalar){
    if(vec.elems == NULL) return;

    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] *= scalar;
    }
}


void cwo_vec_sum(Vector dest, Vector vec){
    if(dest.elems == NULL || vec.elems == NULL) return;
    if(dest.size != vec.size) return;

    for(size_t i = 0; i < vec.size; i++){
        dest.elems[i] += vec.elems[i];
    }
}


CWO_VEC_VAL_TYPE cwo_vec_mag(Vector vec){
    if(vec.elems == NULL) return CWO_VEC_VAL_TYPE_ZERO;

    CWO_VEC_VAL_TYPE sum = CWO_VEC_VAL_TYPE_ZERO;
    for(size_t i = 0; i < vec.size; i++){
        sum += vec.elems[i] * vec.elems[i];
    }

    #ifdef CWO_VEC_VAL_TYPE_FLOAT
    return sqrtf(sum);
    #else
    return sqrt(sum);
    #endif
}


void cwo_vec_sub(Vector dest, Vector vec){
    if(dest.elems == NULL || vec.elems == NULL) return;
    if(dest.size != vec.size) return;

    for(size_t i = 0; i < vec.size; i++){
        dest.elems[i] -= vec.elems[i];
    }
}


CWO_VEC_VAL_TYPE cwo_vec_dot(Vector a, Vector b){
    if(a.elems == NULL || b.elems == NULL) return CWO_VEC_VAL_TYPE_ZERO;
    if(a.size != b.size) return CWO_VEC_VAL_TYPE_ZERO;

    CWO_VEC_VAL_TYPE sum = CWO_VEC_VAL_TYPE_ZERO;

    for(size_t i = 0; i < a.size; i++){
        sum += a.elems[i] * b.elems[i];
    }

    return sum;
}


void cwo_vec_cross(Vector norm, Vector a, Vector b){
    if(a.elems == NULL || b.elems == NULL || norm.elems == NULL) return;
    if(a.size != 3 || b.size != 3 || norm.size != 3) return;

    norm.elems[0] = a.elems[1]*b.elems[2] - a.elems[2]*b.elems[1];
    norm.elems[1] = a.elems[0]*b.elems[2] - a.elems[2]*b.elems[0];
    norm.elems[2] = a.elems[0]*b.elems[1] - a.elems[1]*b.elems[0];
}



#ifdef __cplusplus


#endif //__cplusplus


#endif //CWO_VECTOR_IMPLEMENTATIONS

#endif //CWO_VECTOR_H