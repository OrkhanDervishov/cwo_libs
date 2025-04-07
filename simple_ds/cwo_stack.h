// C stack library
#ifndef CWO_STACK_H
#define CWO_STACK_H

#define CWO_INVALID_STK_VAL 0
#define CWO_STK_VAL_TYPE int

#include <malloc.h>

#ifdef CWO_STACK_IMPLEMENTATIONS

struct StackNode{
    CWO_STK_VAL_TYPE val;
    struct StackNode* next;
};

#define StackNode struct StackNode
const int SN_SIZE = sizeof(StackNode);

typedef struct{
    int size;
    StackNode* head;   
} Stack;


void cwo_stack_init(Stack* stk){
    stk->size = 0;
    stk->head = NULL;
}

int cwo_stack_empty(Stack* stk){
    if(stk->head == NULL)
        return 1;
    return 0;
}

void cwo_stack_insert(Stack* stk, CWO_STK_VAL_TYPE value){
    StackNode* dummy = (StackNode*)malloc(SN_SIZE);
    if(dummy == NULL) return;
    dummy->val = value;

    if(stk->size == 0){
        dummy->next = NULL;
        stk->head = dummy;
    }
    else {
        dummy->next = stk->head;
        stk->head = dummy;
    }

    stk->size++;
}

void cwo_stack_pop(Stack* stk){
    if(stk->head == NULL) return;
    StackNode* dummy = stk->head;
    stk->head = stk->head->next;
    free(dummy);
}

CWO_STK_VAL_TYPE cwo_stack_top(Stack* stk){
    return stk->head->val;
}

void cwo_stack_delete(Stack* stk){
    if(stk->head == NULL) return;
    StackNode* dummy = stk->head;
    
    while(stk->head != NULL){
        stk->head = stk->head->next;
        free(dummy);
        dummy = stk->head;
    }
}

#endif

#endif //CWO_STACK_H