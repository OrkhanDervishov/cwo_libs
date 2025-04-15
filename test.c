#define CWO_LINEAR_IMPLEMENTATIONS
#include "math/cwo_linear.h"

#include <stdio.h>  

#define NL printf("\n")

void ll_tests();
void stack_tests();
void linear_tests();
//void calc_tests();


int main(){
    linear_tests();
    return 0;
}


float f(float x){
    return x;
}


#ifdef CWO_LINEAR_IMPLEMENTATIONS
void linear_tests(){
    Vector vec;
    Vector dest;
    Matrix mat;
    cwo_lin_vec_create(&vec, 3);
    cwo_lin_vec_create(&dest, 3);
    cwo_lin_mat_create(&mat, 3, 3);

    cwo_lin_vec_rand(vec);
    cwo_lin_mat_rand(mat);

    cwo_lin_vec_mat_dot(dest, vec, mat, 1);

    cwo_lin_vec_print(vec);
    NL;
    cwo_lin_mat_print(mat);
    NL;
    cwo_lin_vec_print(dest);
    NL;
}
#endif


#ifdef CWO_CALCULUS_IMPLEMENTATIONS
void calc_tests(){

    printf("Integral: %f\n", cwo_calc_integral(f, 0.0f, 1.0f));
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

