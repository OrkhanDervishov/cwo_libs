#ifndef CWO_MATRIX_H
#define CWO_MATRIX_H

#include <stdlib.h>
#include <malloc.h>

//#define CWO_MAT_VAL_TYPE_INT
//#define CWO_MAT_VAL_TYPE_LONG_LONG
#define CWO_MAT_VAL_TYPE_FLOAT
//#define CWO_MAT_VAL_TYPE_DOUBLE

#if (!defined(CWO_MAT_VAL_TYPE_INT) && !defined(CWO_MAT_VAL_TYPE_FLOAT) && !defined(CWO_MAT_VAL_TYPE_FLOAT) && !defined(CWO_MAT_VAL_TYPE_FLOAT))
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

#ifdef CWO_MATRIX_IMPLEMENTATIONS

typedef struct{
    size_t w, h;
    CWO_MAT_VAL_TYPE* elems;
} Matrix;

#define CWO_MAT_INDEX(m, i, j) (m).elems[(i)*(m).w + (j)]
#define CWO_SWAP(a, b, t) t = a, a = b, b = t;

void cwo_mat_resize(Matrix mat){
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = CWO_MAT_VAL_TYPE_ZERO;
        }
    }
}

void cwo_mat_rand_elems(Matrix mat){
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = (CWO_MAT_VAL_TYPE)rand()/(CWO_MAT_VAL_TYPE)(RAND_MAX/10);
        }
    }
}


void cwo_mat_create(Matrix* mat, size_t w, size_t h, int resize){
    mat->w = w, mat->h = h;
    mat->elems = (CWO_MAT_VAL_TYPE*)malloc(sizeof(CWO_MAT_VAL_TYPE)*h*w);
    if(resize != 0){
        cwo_mat_resize(*mat);
    }
}


void cwo_mat_make_identity(Matrix mat){
    if(mat.w != mat.h) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = CWO_MAT_VAL_TYPE_ZERO;
        }
    }
    for(size_t i = 0; i < mat.h; i++){
        CWO_MAT_INDEX(mat, i, i) = CWO_MAT_VAL_TYPE_ONE;
    }
}


void cwo_mat_print(Matrix mat){
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_PRINT(CWO_MAT_INDEX(mat, i, j));
        }
        printf("\n");
    }    
}


void cwo_mat_delete(Matrix mat){
    free(mat.elems);
}


void cwo_mat_scalar(Matrix mat, CWO_MAT_VAL_TYPE scal){

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) *= scal;
        }
    }
}


void cwo_mat_sum(Matrix dest, Matrix a){
    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            CWO_MAT_INDEX(dest, i, j) += CWO_MAT_INDEX(a, i, j);
        }
    }
}


void cwo_mat_sub(Matrix dest, Matrix a){
    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++)
            CWO_MAT_INDEX(dest, i, j) -= CWO_MAT_INDEX(a, i, j);
    }
}


void cwo_mat_transpose(Matrix mat){

    CWO_MAT_VAL_TYPE t;
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = i; j < mat.w; j++){
            CWO_SWAP(CWO_MAT_INDEX(mat, i, j), CWO_MAT_INDEX(mat, j, i), t);
        }
    }    
}


/* 
cwo_mat_dot_product function must be used 
only for numerical algebraic groups(not for non-numeric objects).
CWO_MAT_VAL_TYPE must represent this group,
and CWO_MAT_VAL_TYPE_ZERO must be identity
element of this group. 
*/
void cwo_mat_dot(Matrix dest, Matrix a, Matrix b){
    if(a.w != b.h) return;
    if(a.h != dest.h) return;
    if(b.w != dest.w) return;

    size_t n = a.w;
    CWO_MAT_VAL_TYPE sum = CWO_MAT_VAL_TYPE_ZERO;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            for(int k = 0; k < n; k++){
                sum += CWO_MAT_INDEX(a, i, k) * CWO_MAT_INDEX(b, k, j);
            }
            CWO_MAT_INDEX(dest, i, j) = sum;
            sum = CWO_MAT_VAL_TYPE_ZERO;
        }
    }
}


void cwo_mat_submatrix(Matrix mat, Matrix sub, size_t x, size_t y){

    size_t mod_x = mat.w;
    size_t mod_y = mat.h;

    for(size_t i = 0; i < sub.h; i++){
        for(size_t j = 0; j < sub.w; j++){
            CWO_MAT_INDEX(sub, i, j) = CWO_MAT_INDEX(mat, (i + y)%mod_y, (j + x)%mod_x);
        }
    }
}

/*
Under development
*/
// CWO_MAT_VAL_TYPE cwo_mat_determinant(Matrix mat){
    
//     if(mat.w == 2 && mat.h == 2)
//         return (CWO_MAT_INDEX(mat, 0, 0) * CWO_MAT_INDEX(mat, 1, 1) - CWO_MAT_INDEX(mat, 0, 1) * CWO_MAT_INDEX(mat, 1, 0));

    
//     int a = 1;
//     CWO_MAT_VAL_TYPE res = CWO_MAT_VAL_TYPE_ZERO;
//     Matrix sub; 
//     cwo_mat_create(&sub, mat.w-1, mat.h-1, 0);

//     for(size_t j = 0; j < mat.w; j++){
//         if(a == 1)
//             res +=  CWO_MAT_INDEX(mat, 0, j) * cwo_mat_determinant(sub);
//         else 
//             res -=  CWO_MAT_INDEX(mat, 0, j) * cwo_mat_determinant(sub);
//         a = -a;
//     }

//     cwo_mat_delete(sub);
//     return res;
// }


void cwo_mat_swap_rows(Matrix mat, size_t r1, size_t r2){

    CWO_MAT_VAL_TYPE t;
    for(int j = 0; j < mat.w; j++){
        CWO_SWAP(CWO_MAT_INDEX(mat, r1, j), CWO_MAT_INDEX(mat, r2, j), t);
    }
}


void cwo_mat_row_sub(Matrix mat, size_t dest, size_t r, CWO_MAT_VAL_TYPE scalar){

    for(size_t j = 0; j < mat.w; j++){
        CWO_MAT_INDEX(mat, dest, j) = CWO_MAT_INDEX(mat, dest, j) - scalar*CWO_MAT_INDEX(mat, r, j);
    }
}


void cwo_mat_gauss(Matrix mat){
    for(size_t rows = mat.h, cols = mat.w, j = 0; j <= cols; j++){
        if(rows == 0 || cols == 0) break;

        if(CWO_MAT_INDEX(mat, j, j) == CWO_MAT_VAL_TYPE_ZERO){
            for(size_t k = 0; k < rows; k++){
                if(CWO_MAT_INDEX(mat, j, k) != CWO_MAT_VAL_TYPE_ZERO){
                    cwo_mat_swap_rows(mat, 0, k);
                    break;
                }
            }
            if(CWO_MAT_INDEX(mat, j, j) == CWO_MAT_VAL_TYPE_ZERO){
                // pass this column
                continue;
            }
        }

        for(size_t i = j+1; i <= rows; i++){
            CWO_MAT_VAL_TYPE scal = CWO_MAT_INDEX(mat, i, j) / CWO_MAT_INDEX(mat, j, j);
            cwo_mat_row_sub(mat, i, j, scal);
        }
    }
}

CWO_MAT_VAL_TYPE cwo_mat_gauss_determinant(Matrix mat){

    CWO_MAT_VAL_TYPE product = 1;
    for(size_t i = 0; i < mat.h && i < mat.w; i++){
        product *= CWO_MAT_INDEX(mat, i, i);
    }

    return product;
}



// TODO: inverse of a matrix
// TODO: matrix transformations

#endif //CWO_MATRIX_IMPLEMENTATIONS

#endif //CWO_MATRIX_H