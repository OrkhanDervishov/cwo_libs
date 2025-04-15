#ifndef CWO_LINEAR_H
#define CWO_LINEAR_H

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>


/*
You can change type of matrix variables 
 */
//#define CWO_LIN_VAL_TYPE_INT
//#define CWO_LIN_VAL_TYPE_LONG_LONG
#define CWO_LIN_VAL_TYPE_FLOAT
//#define CWO_LIN_VAL_TYPE_DOUBLE

#if (!defined(CWO_LIN_VAL_TYPE_INT) && !defined(CWO_LIN_VAL_TYPE_LONG_LONG) && !defined(CWO_LIN_VAL_TYPE_FLOAT) && !defined(CWO_LIN_VAL_TYPE_DOUBLE))
    #error CWO_LIN_VAL_TYPE can not be defined
#endif


#ifdef CWO_LIN_VAL_TYPE_INT
    #define CWO_LIN_VAL_TYPE_ZERO 0
    #define CWO_LIN_VAL_TYPE_ONE 1
    #define CWO_LIN_VAL_TYPE int
    #define CWO_PRINT(v) printf("%d ", (v))
#endif

#ifdef CWO_LIN_VAL_TYPE_LONG_LONG
    #define CWO_LIN_VAL_TYPE_ZERO 0
    #define CWO_LIN_VAL_TYPE_ONE 1
    #define CWO_LIN_VAL_TYPE long long
    #define CWO_PRINT(v) printf("%lld ", (v))
#endif

#ifdef CWO_LIN_VAL_TYPE_FLOAT
    #define CWO_LIN_VAL_TYPE_ZERO 0.0f
    #define CWO_LIN_VAL_TYPE_ONE 1.0f
    #define CWO_LIN_VAL_TYPE float
    #define CWO_PRINT(v) printf("%.2f ", (v))
#endif

#ifdef CWO_LIN_VAL_TYPE_DOUBLE
    #define CWO_LIN_VAL_TYPE_ZERO 0.0
    #define CWO_LIN_VAL_TYPE_ONE 1.0
    #define CWO_LIN_VAL_TYPE double
    #define CWO_PRINT(v) printf("%.2lf ", (v))
#endif




typedef struct{
    size_t size;
    CWO_LIN_VAL_TYPE* elems;
} Vector;

typedef struct{
    size_t w, h;
    CWO_LIN_VAL_TYPE* elems;
} Matrix;


#define CWO_MAT_INDEX(m, i, j) (m).elems[(i)*(m).w + (j)]
#define CWO_SWAP(a, b, t) t = a, a = b, b = t;


// Vector function declarations

void cwo_lin_vec_create(Vector* vec, size_t size);
void cwo_lin_vec_delete(Vector vec);
void cwo_lin_vec_resize(Vector vec, CWO_LIN_VAL_TYPE val);
void cwo_lin_vec_rand(Vector vec);
void cwo_lin_vec_copy(Vector dest, Vector src);
void cwo_lin_vec_print(Vector vec);


void cwo_lin_vec_scale(Vector vec, CWO_LIN_VAL_TYPE scalar);
void cwo_lin_vec_sum(Vector dest, Vector vec);
void cwo_lin_vec_sub(Vector dest, Vector vec);
CWO_LIN_VAL_TYPE cwo_lin_vec_mag(Vector vec);
CWO_LIN_VAL_TYPE cwo_lin_vec_dot(Vector a, Vector b);
void cwo_lin_vec_cross(Vector norm, Vector a, Vector b);
void cwo_lin_vec_proj(Vector proj, Vector v, Vector to);
float cwo_lin_vec_angle(Vector v, Vector u);


// Matrix function declarations

void cwo_lin_mat_create(Matrix* mat, size_t w, size_t h);
void cwo_lin_mat_delete(Matrix mat);
void cwo_lin_mat_copy(Matrix dest, Matrix src);
void cwo_lin_mat_resize(Matrix mat, CWO_LIN_VAL_TYPE val);
void cwo_lin_mat_rand(Matrix mat);
void cwo_lin_mat_make_identity(Matrix mat);
void cwo_lin_mat_print(Matrix mat);


void cwo_lin_mat_scale(Matrix mat, CWO_LIN_VAL_TYPE scal);
void cwo_lin_mat_sum(Matrix dest, Matrix a);
void cwo_lin_mat_sub(Matrix dest, Matrix a);
void cwo_lin_mat_transpose(Matrix mat);
int cwo_lin_mat_issymmetric(Matrix mat);
CWO_LIN_VAL_TYPE cwo_lin_mat_trace(Matrix mat);


void cwo_lin_mat_submatrix(Matrix mat, Matrix sub, size_t x, size_t y);
void cwo_lin_mat_swap_rows(Matrix mat, size_t r1, size_t r2);
void cwo_lin_mat_swap_cols(Matrix mat, size_t c1, size_t c2);
void cwo_lin_mat_row_sub(Matrix mat, size_t dest, size_t r, CWO_LIN_VAL_TYPE scalar);
void cwo_lin_mat_row_scal(Matrix mat, size_t r, CWO_LIN_VAL_TYPE scalar);


void cwo_lin_mat_dot(Matrix dest, Matrix a, Matrix b);
CWO_LIN_VAL_TYPE cwo_lin_mat_determinant(Matrix mat);
CWO_LIN_VAL_TYPE cwo_lin_mat_laplace(Matrix mat);
void cwo_lin_mat_gauss(Matrix mat);
void cwo_lin_mat_echelon(Matrix mat);
void cwo_lin_mat_reduced(Matrix mat);
void cwo_lin_mat_inverse(Matrix inv, Matrix src);


#ifdef CWO_LINEAR_IMPLEMENTATIONS


// Vector function implementations

void cwo_lin_vec_create(Vector* vec, size_t size){
    if (vec->elems != NULL) {
        cwo_lin_vec_delete(*vec);
        printf("Vector already created, previous vector was deleted\n");
    }
    vec->size = size;
    vec->elems = (CWO_LIN_VAL_TYPE*)malloc(size * sizeof(CWO_LIN_VAL_TYPE));
    if (vec->elems == NULL) {
        printf("Memory allocation failed at cwo_lin_vec_create\n");
        exit(1);
    }
}


void cwo_lin_vec_delete(Vector vec){
    if(vec.elems != NULL){
        free(vec.elems);
        vec.elems = NULL;
    }
}


void cwo_lin_vec_resize(Vector vec, CWO_LIN_VAL_TYPE val){
    if(vec.elems == NULL) return;
    
    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] = val;
    }
}


void cwo_lin_vec_rand(Vector vec){
    if(vec.elems == NULL) return;
    
    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] = (CWO_LIN_VAL_TYPE)rand()/
                        (CWO_LIN_VAL_TYPE)(RAND_MAX/10);;
    }
}


void cwo_lin_vec_copy(Vector dest, Vector src){
    if(dest.elems == NULL || src.elems == NULL) return;
    if(dest.size != src.size) return;

    memcpy(dest.elems, src.elems, sizeof(CWO_LIN_VAL_TYPE) * src.size);
}


void cwo_lin_vec_print(Vector vec){
    if(vec.elems == NULL) return;
    
    printf("[ ");
    for(size_t i = 0; i < vec.size; i++){
        CWO_PRINT(vec.elems[i]);
        printf(" ");
    }
    printf("]");
}




void cwo_lin_vec_scale(Vector vec, CWO_LIN_VAL_TYPE scalar){
    if(vec.elems == NULL) return;

    for(size_t i = 0; i < vec.size; i++){
        vec.elems[i] *= scalar;
    }
}


void cwo_lin_vec_sum(Vector dest, Vector vec){
    if(dest.elems == NULL || vec.elems == NULL) return;
    if(dest.size != vec.size) return;

    for(size_t i = 0; i < vec.size; i++){
        dest.elems[i] += vec.elems[i];
    }
}


void cwo_lin_vec_sub(Vector dest, Vector vec){
    if(dest.elems == NULL || vec.elems == NULL) return;
    if(dest.size != vec.size) return;

    for(size_t i = 0; i < vec.size; i++){
        dest.elems[i] -= vec.elems[i];
    }
}


CWO_LIN_VAL_TYPE cwo_lin_vec_mag(Vector vec){
    if(vec.elems == NULL) return CWO_LIN_VAL_TYPE_ZERO;

    CWO_LIN_VAL_TYPE sum = CWO_LIN_VAL_TYPE_ZERO;
    for(size_t i = 0; i < vec.size; i++){
        sum += vec.elems[i] * vec.elems[i];
    }

    #ifdef CWO_LIN_VAL_TYPE_FLOAT
    return sqrtf(sum);
    #else
    return sqrt(sum);
    #endif
}


CWO_LIN_VAL_TYPE cwo_lin_vec_dot(Vector a, Vector b){
    if(a.elems == NULL || b.elems == NULL) return CWO_LIN_VAL_TYPE_ZERO;
    if(a.size != b.size) return CWO_LIN_VAL_TYPE_ZERO;

    CWO_LIN_VAL_TYPE sum = CWO_LIN_VAL_TYPE_ZERO;

    for(size_t i = 0; i < a.size; i++){
        sum += a.elems[i] * b.elems[i];
    }

    return sum;
}


void cwo_lin_vec_cross(Vector norm, Vector a, Vector b){
    if(a.elems == NULL || b.elems == NULL || norm.elems == NULL) return;
    if(a.size != 3 || b.size != 3 || norm.size != 3) return;

    norm.elems[0] = a.elems[1]*b.elems[2] - a.elems[2]*b.elems[1];
    norm.elems[1] = a.elems[0]*b.elems[2] - a.elems[2]*b.elems[0];
    norm.elems[2] = a.elems[0]*b.elems[1] - a.elems[1]*b.elems[0];
}


void cwo_lin_vec_proj(Vector proj, Vector v, Vector to){
    CWO_LIN_VAL_TYPE umag = cwo_lin_vec_dot(to, to);
    CWO_LIN_VAL_TYPE prod = cwo_lin_vec_dot(v, to);
    cwo_lin_vec_copy(proj, to);
    cwo_lin_vec_scale(proj, prod/umag);
}


float cwo_lin_vec_angle(Vector v, Vector u){
    CWO_LIN_VAL_TYPE vmag = cwo_lin_vec_mag(v);
    CWO_LIN_VAL_TYPE umag = cwo_lin_vec_mag(u);
    CWO_LIN_VAL_TYPE prod = cwo_lin_vec_dot(v, u);
    return acosf(prod/vmag/umag);
}



// Matrix function implementations


void cwo_lin_mat_copy(Matrix dest, Matrix src){
    if(dest.elems == NULL || src.elems == NULL) return;

    if(dest.h != src.h || dest.w != src.w){
        return;
    }
    memcpy(dest.elems, src.elems, sizeof(CWO_LIN_VAL_TYPE)*src.h*src.w);
}


void cwo_lin_mat_resize(Matrix mat, CWO_LIN_VAL_TYPE val){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = val;
        }
    }
}

void cwo_lin_mat_rand(Matrix mat){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = (CWO_LIN_VAL_TYPE)rand()/
                                        (CWO_LIN_VAL_TYPE)(RAND_MAX/10);
        }
    }
}


void cwo_lin_mat_create(Matrix* mat, size_t w, size_t h){
    if(w <= 0 || h <= 0) return;
    if (mat->elems != NULL) {
        printf("Matrix already created, previous matrix was deleted\n");
        cwo_lin_mat_delete(*mat);
    }
    mat->w = w;
    mat->h = h;
    mat->elems = (CWO_LIN_VAL_TYPE*)malloc(h * w * sizeof(CWO_LIN_VAL_TYPE));
    if (mat->elems == NULL) {
        printf("Memory allocation failed at cwo_lin_mat_create\n");
        exit(1);
    }
}


void cwo_lin_mat_make_identity(Matrix mat){
    if(mat.elems == NULL) return;
    if(mat.w != mat.h) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) = CWO_LIN_VAL_TYPE_ZERO;
        }
    }
    for(size_t i = 0; i < mat.h; i++){
        CWO_MAT_INDEX(mat, i, i) = CWO_LIN_VAL_TYPE_ONE;
    }
}


void cwo_lin_mat_print(Matrix mat){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_PRINT(CWO_MAT_INDEX(mat, i, j));
        }
        printf("\n");
    }    
}


void cwo_lin_mat_delete(Matrix mat){
    if(mat.elems == NULL) return;
    free(mat.elems);
    mat.elems = NULL;
}


void cwo_lin_mat_scale(Matrix mat, CWO_LIN_VAL_TYPE scal){
    if(mat.elems == NULL) return;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            CWO_MAT_INDEX(mat, i, j) *= scal;
        }
    }
}


void cwo_lin_mat_sum(Matrix dest, Matrix a){
    if(dest.elems == NULL || a.elems == NULL) return;

    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            CWO_MAT_INDEX(dest, i, j) += CWO_MAT_INDEX(a, i, j);
        }
    }
}


void cwo_lin_mat_sub(Matrix dest, Matrix a){
    if(dest.elems == NULL || a.elems == NULL) return;

    if(dest.h != a.h || dest.w != a.w) return;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++)
            CWO_MAT_INDEX(dest, i, j) -= CWO_MAT_INDEX(a, i, j);
    }
}


void cwo_lin_mat_transpose(Matrix mat){
    if(mat.elems == NULL) return;

    CWO_LIN_VAL_TYPE t;
    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = i; j < mat.w; j++){
            CWO_SWAP(CWO_MAT_INDEX(mat, i, j), CWO_MAT_INDEX(mat, j, i), t);
        }
    }    
}


int cwo_lin_mat_issymmetric(Matrix mat){
    if(mat.elems == NULL) return 0;

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = i; j < mat.w; j++){
            if(CWO_MAT_INDEX(mat, i, j) != CWO_MAT_INDEX(mat, j, i)) return 0;
        }
    }
    return 1;
}


CWO_LIN_VAL_TYPE cwo_lin_mat_trace(Matrix mat){
    if(mat.elems == NULL) return CWO_LIN_VAL_TYPE_ZERO;
    if(mat.h != mat.w) return CWO_LIN_VAL_TYPE_ZERO;

    CWO_LIN_VAL_TYPE sum = CWO_LIN_VAL_TYPE_ZERO;
    for(size_t i = 0; i < mat.h; i++){
        sum += CWO_MAT_INDEX(mat, i, i);
    }
    return sum;
}


void cwo_lin_mat_laplace_submatrix(Matrix mat, Matrix sub, size_t row_ignore, size_t col_ignore){
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

void cwo_lin_mat_submatrix(Matrix mat, Matrix sub, size_t x, size_t y){
    if(mat.elems == NULL || sub.elems == NULL) return;

    size_t mod_x = mat.w;
    size_t mod_y = mat.h;

    for(size_t i = 0; i < sub.h; i++){
        for(size_t j = 0; j < sub.w; j++){
            CWO_MAT_INDEX(sub, i, j) = CWO_MAT_INDEX(mat, (i + y)%mod_y, (j + x)%mod_x);
        }
    }
}

void cwo_lin_mat_swap_rows(Matrix mat, size_t r1, size_t r2){
    if(mat.elems == NULL) return;

    CWO_LIN_VAL_TYPE t;
    for(size_t j = 0; j < mat.w; j++){
        CWO_SWAP(CWO_MAT_INDEX(mat, r1, j), CWO_MAT_INDEX(mat, r2, j), t);
    }
}

void cwo_lin_mat_swap_cols(Matrix mat, size_t c1, size_t c2){
    if(mat.elems == NULL) return;

    CWO_LIN_VAL_TYPE t;
    for(size_t i = 0; i < mat.h; i++){
        CWO_SWAP(CWO_MAT_INDEX(mat, i, c1), CWO_MAT_INDEX(mat, i, c2), t);
    }
}

void cwo_lin_mat_row_sub(Matrix mat, size_t dest, size_t r, CWO_LIN_VAL_TYPE scalar){
    if(mat.elems == NULL) return;

    for(size_t j = 0; j < mat.w; j++){
        CWO_MAT_INDEX(mat, dest, j) -= scalar*CWO_MAT_INDEX(mat, r, j);
    }
}

void cwo_lin_mat_row_scale(Matrix mat, size_t r, CWO_LIN_VAL_TYPE scalar){

    for(size_t j = 0; j < mat.w; j++){
        CWO_MAT_INDEX(mat, r, j) *= scalar;
    }
}

/* 
cwo_lin_mat_dot_product function must be used 
only for numerical algebraic groups(not for non-numeric objects).
CWO_LIN_VAL_TYPE must represent this group,
and CWO_LIN_VAL_TYPE_ZERO must be identity
element of this group. 
*/
void cwo_lin_mat_dot(Matrix dest, Matrix a, Matrix b){
    if(dest.elems == NULL || a.elems == NULL || b.elems == NULL) return;
    if(a.w != b.h) return;
    if(a.h != dest.h) return;
    if(b.w != dest.w) return;

    size_t n = a.w;
    CWO_LIN_VAL_TYPE sum = CWO_LIN_VAL_TYPE_ZERO;

    for(size_t i = 0; i < dest.h; i++){
        for(size_t j = 0; j < dest.w; j++){
            for(size_t k = 0; k < n; k++){
                sum += CWO_MAT_INDEX(a, i, k) * CWO_MAT_INDEX(b, k, j);
            }
            CWO_MAT_INDEX(dest, i, j) = (sum == CWO_LIN_VAL_TYPE_ZERO ? CWO_LIN_VAL_TYPE_ZERO : sum);
            sum = CWO_LIN_VAL_TYPE_ZERO;
        }
    }
}


CWO_LIN_VAL_TYPE cwo_lin_mat_determinant(Matrix mat){
    if(mat.elems == NULL) return CWO_LIN_VAL_TYPE_ZERO;
    if(mat.w != mat.h) return CWO_LIN_VAL_TYPE_ZERO;

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
        CWO_LIN_VAL_TYPE product = 1;
        for(size_t i = 0; i < mat.h && i < mat.w; i++){
            product *= CWO_MAT_INDEX(mat, i, i);
        }
        return product;
    }

    return cwo_lin_mat_laplace(mat);
}


/*
cwo_lin_mat_laplace function calculates determinant 
with Laplace expansion technique
*/
CWO_LIN_VAL_TYPE cwo_lin_mat_laplace(Matrix mat){
    if(mat.elems == NULL) return CWO_LIN_VAL_TYPE_ZERO;

    if(mat.w == 2 && mat.h == 2){
        CWO_LIN_VAL_TYPE prod = (CWO_MAT_INDEX(mat, 0, 0) * CWO_MAT_INDEX(mat, 1, 1) -
                                 CWO_MAT_INDEX(mat, 0, 1) * CWO_MAT_INDEX(mat, 1, 0));
        return prod;
    }
    
    int sign = 1;
    CWO_LIN_VAL_TYPE res = CWO_LIN_VAL_TYPE_ZERO;
    Matrix sub;
    sub.elems = NULL;
    cwo_lin_mat_create(&sub, mat.w-1, mat.h-1);

    for(size_t j = 0; j < mat.w; j++){
        cwo_lin_mat_laplace_submatrix(mat, sub, 0, j);
        if(sign == 1){
            res +=  (CWO_MAT_INDEX(mat, 0, j) * cwo_lin_mat_laplace(sub));
        }
        else{
            res -=  (CWO_MAT_INDEX(mat, 0, j) * cwo_lin_mat_laplace(sub));
        }
        sign = -sign;
    }

    cwo_lin_mat_delete(sub);
    return res;    
}


/*
Performs Gaussian elimination
operation on the matrix 
 */
void cwo_lin_mat_gauss(Matrix mat){
    if(mat.elems == NULL) return;

    for(size_t rows = mat.h, cols = mat.w, j = 0; j < cols; j++){

        if(CWO_MAT_INDEX(mat, j, j) == CWO_LIN_VAL_TYPE_ZERO){
            for(size_t k = j; k < rows; k++){
                if(CWO_MAT_INDEX(mat, j, k) != CWO_LIN_VAL_TYPE_ZERO){
                    cwo_lin_mat_swap_rows(mat, 0, k);
                    break;
                }
            }
            if(CWO_MAT_INDEX(mat, j, j) == CWO_LIN_VAL_TYPE_ZERO){
                // pass this column
                continue;
            }
        }

        for(size_t i = j+1; i < rows; i++){
            CWO_LIN_VAL_TYPE scal = CWO_MAT_INDEX(mat, i, j) / CWO_MAT_INDEX(mat, j, j);
            cwo_lin_mat_row_sub(mat, i, j, scal);
        }
    }
}


void cwo_lin_mat_echelon(Matrix mat){
    if(mat.elems == NULL) return;
    cwo_lin_mat_gauss(mat);

    for(size_t i = 0; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            if(CWO_MAT_INDEX(mat, i, j) != 0){
                CWO_LIN_VAL_TYPE scal = CWO_LIN_VAL_TYPE_ONE/CWO_MAT_INDEX(mat, i, j);
                cwo_lin_mat_row_scale(mat, i, scal);
                break;
            }
        }
    }
}

void cwo_lin_mat_reduced(Matrix mat){
    if(mat.elems == NULL) return;
    cwo_lin_mat_echelon(mat);

    for(size_t i = 1; i < mat.h; i++){
        for(size_t j = 0; j < mat.w; j++){
            if(CWO_MAT_INDEX(mat, i, j) != 0){
                for(size_t k = i; k > 0; k--){
                    CWO_LIN_VAL_TYPE scal = CWO_MAT_INDEX(mat, k-1, j)/CWO_MAT_INDEX(mat, i, j);
                    cwo_lin_mat_row_sub(mat, k-1, i, scal);
                }
                break;
            }
        }
    }    
}


void cwo_lin_mat_inverse(Matrix inv, Matrix mat){
    if(inv.h != mat.h || inv.w != mat.h) return;
    if(inv.elems == NULL || mat.elems == NULL) return;

    Matrix copy;
    copy.elems = NULL;
    cwo_lin_mat_create(&copy, mat.w, mat.h);
    cwo_lin_mat_copy(copy, mat);

    cwo_lin_mat_make_identity(inv);

    for(size_t rows = mat.h, cols = mat.w, j = 0; j < cols; j++){

        if(CWO_MAT_INDEX(copy, j, j) == CWO_LIN_VAL_TYPE_ZERO){
            for(size_t k = j; k < rows; k++){
                if(CWO_MAT_INDEX(copy, j, k) != CWO_LIN_VAL_TYPE_ZERO){
                    cwo_lin_mat_swap_rows(copy, 0, k);
                    cwo_lin_mat_swap_rows(inv, 0, k);
                    break;
                }
            }
            if(CWO_MAT_INDEX(copy, j, j) == CWO_LIN_VAL_TYPE_ZERO){
                // pass this column
                continue;
            }
        }

        for(size_t i = j+1; i < rows; i++){
            CWO_LIN_VAL_TYPE scal = CWO_MAT_INDEX(copy, i, j) / CWO_MAT_INDEX(copy, j, j);
            cwo_lin_mat_row_sub(copy, i, j, scal);
            cwo_lin_mat_row_sub(inv, i, j, scal);
        }
    }

    for(size_t i = 0; i < copy.h; i++){
        for(size_t j = 0; j < copy.w; j++){
            if(CWO_MAT_INDEX(copy, i, j) != 0){
                CWO_LIN_VAL_TYPE scal = CWO_LIN_VAL_TYPE_ONE/CWO_MAT_INDEX(copy, i, j);
                cwo_lin_mat_row_scale(copy, i, scal);
                cwo_lin_mat_row_scale(inv, i, scal);
                break;
            }
        }
    }

    for(size_t i = 1; i < copy.h; i++){
        for(size_t j = 0; j < copy.w; j++){
            if(CWO_MAT_INDEX(copy, i, j) != 0){
                for(size_t k = i; k > 0; k--){
                    CWO_LIN_VAL_TYPE scal = CWO_MAT_INDEX(copy, k-1, j)/CWO_MAT_INDEX(copy, i, j);
                    cwo_lin_mat_row_sub(copy, k-1, i, scal);
                    cwo_lin_mat_row_sub(inv, k-1, i, scal);
                }
                break;
            }
        }
    }  

    cwo_lin_mat_delete(copy);
}



// Vector and Matrix function implementations


void cwo_lin_vec_mat_dot(Vector dest, Vector vec, Matrix mat, int order){
    if(vec.elems == NULL || mat.elems == NULL || dest.elems == NULL) return;

    CWO_LIN_VAL_TYPE sum = CWO_LIN_VAL_TYPE_ZERO;

    /* 
    if order is 0 vector will be multiplied
    to matrix from the left side.
    */
    if(order != 0){
        if(vec.size == mat.w && mat.h == dest.size){
            for(size_t i = 0; i < mat.h; i++){
                for(size_t j = 0; j < mat.w; j++){
                    sum += CWO_MAT_INDEX(mat, i, j) * vec.elems[j];
                }
                dest.elems[i] = sum;
                sum = CWO_LIN_VAL_TYPE_ZERO;
            }
        }
        return;
    }
    if(vec.size == mat.h && mat.w == dest.size){
        for(size_t j = 0; j < mat.w; j++){
            for(size_t i = 0; i < mat.h; i++){
                sum += CWO_MAT_INDEX(mat, i, j) * vec.elems[i];
            }
            dest.elems[j] = sum;
            sum = CWO_LIN_VAL_TYPE_ZERO;
        } 
    }
}



// TODO: matrix transformations
// TODO: finding matrix basis
// TODO: finding eigenvalue and eigenvector of a matrix
// TODO: cpp operators


#endif //CWO_LINEAR_IMPLEMENTATIONS

#endif // CWO_LINEAR_H