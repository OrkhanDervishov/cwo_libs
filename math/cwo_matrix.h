#ifndef CWO_MATRIX_H
#define CWO_MATRIX_H

#include <stdlib.h>
#include <malloc.h>
#include <string.h>


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


typedef struct{
    size_t w, h;
    CWO_MAT_VAL_TYPE* elems;
} Matrix;

#define CWO_MAT_INDEX(m, i, j) (m).elems[(i)*(m).w + (j)]
#define CWO_SWAP(a, b, t) t = a, a = b, b = t;

void cwo_mat_create(Matrix* mat, size_t w, size_t h);
void cwo_mat_delete(Matrix mat);
void cwo_mat_copy(Matrix dest, Matrix src);
void cwo_mat_resize(Matrix mat, CWO_MAT_VAL_TYPE val);
void cwo_mat_randomize(Matrix mat);
void cwo_mat_make_identity(Matrix mat);
void cwo_mat_print(Matrix mat);


void cwo_mat_scale(Matrix mat, CWO_MAT_VAL_TYPE scal);
void cwo_mat_sum(Matrix dest, Matrix a);
void cwo_mat_sub(Matrix dest, Matrix a);
void cwo_mat_transpose(Matrix mat);


void cwo_mat_submatrix(Matrix mat, Matrix sub, size_t x, size_t y);
void cwo_mat_swap_rows(Matrix mat, size_t r1, size_t r2);
void cwo_mat_swap_cols(Matrix mat, size_t c1, size_t c2);
void cwo_mat_row_sub(Matrix mat, size_t dest, size_t r, CWO_MAT_VAL_TYPE scalar);
void cwo_mat_row_scal(Matrix mat, size_t r, CWO_MAT_VAL_TYPE scalar);


void cwo_mat_dot(Matrix dest, Matrix a, Matrix b);
CWO_MAT_VAL_TYPE cwo_mat_determinant(Matrix mat);
CWO_MAT_VAL_TYPE cwo_mat_laplace(Matrix mat);
void cwo_mat_gauss(Matrix mat);
void cwo_mat_echelon(Matrix mat);
void cwo_mat_reduced(Matrix mat);
void cwo_mat_inverse(Matrix inv, Matrix src);


#ifdef CWO_MATRIX_IMPLEMENTATIONS

void cwo_mat_copy(Matrix dest, Matrix src){
    if(dest.elems == NULL || src.elems == NULL) return;

    if(dest.h != src.h || dest.w != src.w){
        return;
    }
    memcpy(dest.elems, src.elems, sizeof(CWO_MAT_VAL_TYPE)*src.h*src.w);
}


void cwo_mat_resize(Matrix mat, CWO_MAT_VAL_TYPE val){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = val;
        }
    }
}

void cwo_mat_randomize(Matrix mat){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = (CWO_MAT_VAL_TYPE)rand()/
                                        (CWO_MAT_VAL_TYPE)(RAND_MAX/10);
        }
    }
}


void cwo_mat_create(Matrix* mat, size_t w, size_t h){
    if(w <= 0 || h <= 0) return;
    if (mat->elems != NULL) {
        printf("Matrix already created, previous matrix was deleted\n");
        cwo_mat_delete(*mat);
    }
    mat->w = w;
    mat->h = h;
    mat->elems = (CWO_MAT_VAL_TYPE*)malloc(h * w * sizeof(CWO_MAT_VAL_TYPE));
    if (mat->elems == NULL) {
        printf("Memory allocation failed at cwo_mat_create\n");
        exit(1);
    }
}


void cwo_mat_make_identity(Matrix mat){
    if(mat.elems == NULL) return;
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
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_PRINT(CWO_MAT_INDEX(mat, i, j));
        }
        printf("\n");
    }    
}


void cwo_mat_delete(Matrix mat){
    if(mat.elems == NULL) return;
    free(mat.elems);
    mat.elems = NULL;
}


void cwo_mat_scale(Matrix mat, CWO_MAT_VAL_TYPE scal){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) *= scal;
        }
    }
}


void cwo_mat_sum(Matrix dest, Matrix a){
    if(dest.elems == NULL || a.elems == NULL) return;

    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            CWO_MAT_INDEX(dest, i, j) += CWO_MAT_INDEX(a, i, j);
        }
    }
}


void cwo_mat_sub(Matrix dest, Matrix a){
    if(dest.elems == NULL || a.elems == NULL) return;

    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++)
            CWO_MAT_INDEX(dest, i, j) -= CWO_MAT_INDEX(a, i, j);
    }
}


void cwo_mat_transpose(Matrix mat){
    if(mat.elems == NULL) return;

    CWO_MAT_VAL_TYPE t;
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = i; j < mat.w; j++){
            CWO_SWAP(CWO_MAT_INDEX(mat, i, j), CWO_MAT_INDEX(mat, j, i), t);
        }
    }    
}





void cwo_mat_laplace_submatrix(Matrix mat, Matrix sub, size_t row_ignore, size_t col_ignore){
    if(mat.elems == NULL || sub.elems == NULL) return;

    size_t sub_i = 0;
    size_t sub_j = 0;
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            if(i != row_ignore && j != col_ignore){
                CWO_MAT_INDEX(sub, sub_i, sub_j) = CWO_MAT_INDEX(mat, i, j);
                sub_j++;
                if(sub_j >= sub.w){
                    sub_j = 0;
                    sub_i++;
                }
            }
        }
    }
}

void cwo_mat_submatrix(Matrix mat, Matrix sub, size_t x, size_t y){
    if(mat.elems == NULL || sub.elems == NULL) return;

    size_t mod_x = mat.w;
    size_t mod_y = mat.h;

    for(size_t i = 0; i < sub.h; i++){
        for(size_t j = 0; j < sub.w; j++){
            CWO_MAT_INDEX(sub, i, j) = CWO_MAT_INDEX(mat, (i + y)%mod_y, (j + x)%mod_x);
        }
    }
}

void cwo_mat_swap_rows(Matrix mat, size_t r1, size_t r2){
    if(mat.elems == NULL) return;

    CWO_MAT_VAL_TYPE t;
    for(size_t j = 0; j < mat.w; j++){
        CWO_SWAP(CWO_MAT_INDEX(mat, r1, j), CWO_MAT_INDEX(mat, r2, j), t);
    }
}

void cwo_mat_swap_cols(Matrix mat, size_t c1, size_t c2){
    if(mat.elems == NULL) return;

    CWO_MAT_VAL_TYPE t;
    for(size_t i = 0; i < mat.h; i++){
        CWO_SWAP(CWO_MAT_INDEX(mat, i, c1), CWO_MAT_INDEX(mat, i, c2), t);
    }
}

void cwo_mat_row_sub(Matrix mat, size_t dest, size_t r, CWO_MAT_VAL_TYPE scalar){
    if(mat.elems == NULL) return;

    for(size_t j = 0; j < mat.w; j++){
        CWO_MAT_INDEX(mat, dest, j) -= scalar*CWO_MAT_INDEX(mat, r, j);
    }
}

void cwo_mat_row_scale(Matrix mat, size_t r, CWO_MAT_VAL_TYPE scalar){

    for(size_t j = 0; j < mat.w; j++){
        CWO_MAT_INDEX(mat, r, j) *= scalar;
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
    if(dest.elems == NULL || a.elems == NULL || b.elems == NULL) return;
    if(a.w != b.h) return;
    if(a.h != dest.h) return;
    if(b.w != dest.w) return;

    size_t n = a.w;
    CWO_MAT_VAL_TYPE sum = CWO_MAT_VAL_TYPE_ZERO;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            for(size_t k = 0; k < n; k++){
                sum += CWO_MAT_INDEX(a, i, k) * CWO_MAT_INDEX(b, k, j);
            }
            CWO_MAT_INDEX(dest, i, j) = (sum == CWO_MAT_VAL_TYPE_ZERO ? CWO_MAT_VAL_TYPE_ZERO : sum);
            sum = CWO_MAT_VAL_TYPE_ZERO;
        }
    }
}


CWO_MAT_VAL_TYPE cwo_mat_determinant(Matrix mat){
    if(mat.elems == NULL) return CWO_MAT_VAL_TYPE_ZERO;
    if(mat.w != mat.h) return CWO_MAT_VAL_TYPE_ZERO;

    /*
    Returns product of diagonal elements if
    matrix is processed by Gaussian elimination
     */
    int eliminated = 1;
    for(size_t i = mat.h-1; i > 0; i--){
        for(size_t j = 0; j < i; j++){
            if(CWO_MAT_INDEX(mat, i, j) == 0) continue;
            eliminated = 0;
        }
    }

    if(eliminated == 1){
        CWO_MAT_VAL_TYPE product = 1;
        for(size_t i = 0; i < mat.h && i < mat.w; i++){
            product *= CWO_MAT_INDEX(mat, i, i);
        }
        return product;
    }

    return cwo_mat_laplace(mat);
}


/*
cwo_mat_laplace function calculates determinant 
with Laplace expansion technique
*/
CWO_MAT_VAL_TYPE cwo_mat_laplace(Matrix mat){
    if(mat.elems == NULL) return CWO_MAT_VAL_TYPE_ZERO;

    if(mat.w == 2 && mat.h == 2){
        CWO_MAT_VAL_TYPE prod = (CWO_MAT_INDEX(mat, 0, 0) * CWO_MAT_INDEX(mat, 1, 1) -
                                 CWO_MAT_INDEX(mat, 0, 1) * CWO_MAT_INDEX(mat, 1, 0));
        return prod;
    }
    
    int sign = 1;
    CWO_MAT_VAL_TYPE res = CWO_MAT_VAL_TYPE_ZERO;
    Matrix sub;
    sub.elems = NULL;
    cwo_mat_create(&sub, mat.w-1, mat.h-1);

    for(size_t j = 0; j < mat.w; j++){
        cwo_mat_laplace_submatrix(mat, sub, 0, j);
        if(sign == 1){
            res +=  (CWO_MAT_INDEX(mat, 0, j) * cwo_mat_laplace(sub));
        }
        else{
            res -=  (CWO_MAT_INDEX(mat, 0, j) * cwo_mat_laplace(sub));
        }
        sign = -sign;
    }

    cwo_mat_delete(sub);
    return res;    
}


/*
Performs Gaussian elimination
operation on the matrix 
 */
void cwo_mat_gauss(Matrix mat){
    if(mat.elems == NULL) return;

    for(size_t rows = mat.h, cols = mat.w, j = 0; j < cols; j++){

        if(CWO_MAT_INDEX(mat, j, j) == CWO_MAT_VAL_TYPE_ZERO){
            for(size_t k = j; k < rows; k++){
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

        for(size_t i = j+1; i < rows; i++){
            CWO_MAT_VAL_TYPE scal = CWO_MAT_INDEX(mat, i, j) / CWO_MAT_INDEX(mat, j, j);
            cwo_mat_row_sub(mat, i, j, scal);
        }
    }
}


void cwo_mat_echelon(Matrix mat){
    if(mat.elems == NULL) return;
    cwo_mat_gauss(mat);

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            if(CWO_MAT_INDEX(mat, i, j) != 0){
                CWO_MAT_VAL_TYPE scal = CWO_MAT_VAL_TYPE_ONE/CWO_MAT_INDEX(mat, i, j);
                cwo_mat_row_scale(mat, i, scal);
                break;
            }
        }
    }
}

void cwo_mat_reduced(Matrix mat){
    if(mat.elems == NULL) return;
    cwo_mat_echelon(mat);

    for(size_t i = 1; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            if(CWO_MAT_INDEX(mat, i, j) != 0){
                for(size_t k = i; k > 0; k--){
                    CWO_MAT_VAL_TYPE scal = CWO_MAT_INDEX(mat, k-1, j)/CWO_MAT_INDEX(mat, i, j);
                    cwo_mat_row_sub(mat, k-1, i, scal);
                }
                break;
            }
        }
    }    
}


void cwo_mat_inverse(Matrix inv, Matrix mat){
    if(inv.h != mat.h || inv.w != mat.h) return;
    if(inv.elems == NULL || mat.elems == NULL) return;

    Matrix copy;
    copy.elems = NULL;
    cwo_mat_create(&copy, mat.w, mat.h);
    cwo_mat_copy(copy, mat);

    cwo_mat_make_identity(inv);
    
    cwo_mat_print(copy);
    printf("\n\n");

    
    cwo_mat_print(inv);
    printf("\n\n");


    for(size_t rows = mat.h, cols = mat.w, j = 0; j < cols; j++){

        if(CWO_MAT_INDEX(copy, j, j) == CWO_MAT_VAL_TYPE_ZERO){
            for(size_t k = j; k < rows; k++){
                if(CWO_MAT_INDEX(copy, j, k) != CWO_MAT_VAL_TYPE_ZERO){
                    cwo_mat_swap_rows(copy, 0, k);
                    cwo_mat_swap_rows(inv, 0, k);
                    break;
                }
            }
            if(CWO_MAT_INDEX(copy, j, j) == CWO_MAT_VAL_TYPE_ZERO){
                // pass this column
                continue;
            }
        }

        for(size_t i = j+1; i < rows; i++){
            CWO_MAT_VAL_TYPE scal = CWO_MAT_INDEX(copy, i, j) / CWO_MAT_INDEX(copy, j, j);
            cwo_mat_row_sub(copy, i, j, scal);
            cwo_mat_row_sub(inv, i, j, scal);
        }
    }

    
    cwo_mat_print(copy);
    printf("\n\n");


    for(size_t i = 0; i < copy.h; i++){
        for(size_t j = 0; j < copy.w; j++){
            if(CWO_MAT_INDEX(copy, i, j) != 0){
                CWO_MAT_VAL_TYPE scal = CWO_MAT_VAL_TYPE_ONE/CWO_MAT_INDEX(copy, i, j);
                cwo_mat_row_scale(copy, i, scal);
                cwo_mat_row_scale(inv, i, scal);
                break;
            }
        }
    }
    
    cwo_mat_print(copy);
    printf("\n\n");

    for(size_t i = 1; i < copy.h; i++){
        for(size_t j = 0; j < copy.w; j++){
            if(CWO_MAT_INDEX(copy, i, j) != 0){
                for(size_t k = i; k > 0; k--){
                    CWO_MAT_VAL_TYPE scal = CWO_MAT_INDEX(copy, k-1, j)/CWO_MAT_INDEX(copy, i, j);
                    cwo_mat_row_sub(copy, k-1, i, scal);
                    cwo_mat_row_sub(inv, k-1, i, scal);
                }
                break;
            }
        }
    }  
    
    cwo_mat_print(copy);
    cwo_mat_delete(copy);
}

// Some cpp operators
#ifdef __cplusplus



#endif //__cplusplus



// TODO: inverse of a matrix
// TODO: matrix transformations
// TODO: finding matrix basis
// TODO: finding eigenvalue and eigenvector of a matrix
// TODO: cpp operators

#endif //CWO_MATRIX_IMPLEMENTATIONS

#endif //CWO_MATRIX_H