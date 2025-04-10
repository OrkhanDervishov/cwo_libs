#define CWO_MATRIX_IMPLEMENTATIONS
//#define CWO_VECTOR_IMPLEMENTATIONS
#include "math/cwo_matrix.h"
#include "math/cwo_vector.h"

void ll_tests();
void stack_tests();
void matrix_tests();
void vector_tests();


int main(){
    matrix_tests();
    return 0;
}


#ifdef CWO_VECTOR_IMPLEMENTATIONS
void vector_tests(){
    Vector a;
    Vector b;
    cwo_vec_create(&a, 3);
    cwo_vec_create(&b, 3);
    cwo_vec_randomize(a);
    cwo_vec_randomize(b);

    cwo_vec_print(a);
    printf("\n");
    cwo_vec_print(b);
    printf("\n");
    printf("\nDot: %f\n", cwo_vec_dot(a, b));

    Vector norm;
    cwo_vec_create(&norm, 3);
    printf("\nCross: ");
    cwo_vec_cross(norm, a, b);
    cwo_vec_print(norm);
    printf("\n");
}
#endif


#ifdef CWO_MATRIX_IMPLEMENTATIONS
void matrix_tests(){
    Matrix mat;
    Matrix mat2;
    Matrix inv;

    cwo_mat_create(&mat, 3, 3);
    cwo_mat_create(&mat2, 3, 3);
    cwo_mat_create(&inv, 3, 3);
    
    // cwo_mat_make_identity(mat);
    // cwo_mat_scalar(mat, 3.0f);
    cwo_mat_randomize(mat);
    cwo_mat_print(mat);
    printf("\n------------------------------\n");
    // //cwo_mat_print(mat);
    // cwo_mat_copy(mat2, mat);
    // cwo_mat_gauss(mat2);
    // cwo_mat_print(mat2);
    // printf("\n------------------------------\n");
    // cwo_mat_echelon(mat2);
    // printf("\n------------------------------\n");
    // cwo_mat_print(mat2);

    // cwo_mat_reduced(mat2);
    // printf("\n------------------------------\n");
    // cwo_mat_print(mat2);

    //printf("\n\ndetermiant: %f\n", cwo_mat_determinant(mat2));
    // printf("\n\ndetermiant: %f\n", cwo_mat_determinant(mat));
    printf("\n------------------------------\n");

    cwo_mat_inverse(inv, mat);
    printf("\n------------------------------\n");
    cwo_mat_print(inv);

    printf("\n------------------------------\n");
    cwo_mat_dot(mat2, mat, inv);
    cwo_mat_print(mat2);




    // cwo_mat_create(&mat2, 5, 5, 1);
    // cwo_mat_rand_elems(mat2);
    // cwo_mat_print(mat2);

    // printf("\n------------------------------\n");

    // cwo_mat_sum(mat, mat2);
    // cwo_mat_print(mat);

    // printf("\n------------------------------\n");

    // cwo_mat_gauss(mat);
    // cwo_mat_print(mat);

    cwo_mat_delete(inv);
    cwo_mat_delete(mat);
    cwo_mat_delete(mat2);
}
#endif


#ifdef CWO_STACK_IMPLEMENTATIONS
void stack_tests(){
    // Stack s;
    // cwo_stack_init(&s);
    // cwo_stack_insert(&s, 1);
    // cwo_stack_insert(&s, 2);
    // cwo_stack_insert(&s, 3);
    // cwo_stack_insert(&s, 4);
    // cwo_stack_insert(&s, 5);

    // cwo_stack_pop(&s);
    // cwo_stack_pop(&s);

    // printf("%d", cwo_stack_top(&s));

    // cwo_stack_delete(&s);
}
#endif


#ifdef CWO_SINGLY_LINKED_LIST_IMPLEMENTATIONS
void ll_tests(){
    // LinkedList list;
    // cwo_init_list(&list);
    // //printf("%d %d %d", list.size, (list.head == NULL), (list.tail == NULL));

    // cwo_add_to_head(&list, 1);
    // cwo_add_to_head(&list, 2);
    // cwo_add_to_head(&list, 3);
    // printf("\n");

    // cwo_print_list(&list);

    // cwo_delete_list(&list);
}
#endif

