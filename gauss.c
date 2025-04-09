#define CWO_MATRIX_IMPLEMENTATIONS
#include "math/cwo_matrix.h"
#include <string.h>


#define ROWS 4
#define COLS 5

int main(){
    Matrix mat;
    cwo_mat_create(&mat, COLS, ROWS);

    // your matrix
    CWO_MAT_VAL_TYPE mymatrix[ROWS * COLS] = {
        3.2f, 3.0f, 4.0f, 5.0f, 4.0f,
        5.1f, 1.3f, 2.6f, 3.5f, 3.2f,
        0.0f, 8.0f, 9.8f, 0.4f, 5.6f,
        2.8f, 8.7f, 9.0f, 15.4f, 4.9f
    };

    memcpy(mat.elems, mymatrix, sizeof(CWO_MAT_VAL_TYPE) * ROWS * COLS);

    cwo_mat_print(mat);
    printf("\n-----------------------\n");
    cwo_mat_gauss(mat);
    cwo_mat_print(mat);
    //printf("\n\ndetermiant: %f\n", cwo_mat_determinant(mat));
}