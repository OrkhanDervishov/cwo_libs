#define CWO_MATRIX_IMPLEMENTATIONS
#include "math/cwo_matrix.h"

void ll_tests();
void stack_tests();
void matrix_tests();

int main(){
    matrix_tests();

    return 0;
}



void matrix_tests(){
    Matrix mat;
    Matrix mat2;

    cwo_mat_create(&mat, 3, 3, 1);
    cwo_mat_make_identity(mat);
    cwo_mat_scalar(mat, 3.0f);
    cwo_mat_print(mat);

    printf("\n------------------------------\n");

    // cwo_mat_create(&mat2, 5, 5, 1);
    // cwo_mat_rand_elems(mat2);
    // cwo_mat_print(mat2);

    // printf("\n------------------------------\n");

    // cwo_mat_sum(mat, mat2);
    // cwo_mat_print(mat);

    // printf("\n------------------------------\n");

    // cwo_mat_gauss(mat);
    // cwo_mat_print(mat);

    // cwo_mat_delete(mat);
}

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