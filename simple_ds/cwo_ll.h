// C linked list library
#ifndef CWO_LINKED_LIST_H
#define CWO_LINKED_LIST_H

#define INVALID_LL_CWO_VAL 0
#define CWO_LL_VAL_TYPE int


#include <stdio.h>
#include <malloc.h>

// Include singly linked list library implementations 
#ifdef CWO_SINGLY_LINKED_LIST_IMPLEMENTATIONS

struct ListNode{
    CWO_LL_VAL_TYPE val;
    struct ListNode* next;
};

#define ListNode struct ListNode

typedef struct 
{
    size_t size;
    ListNode* head;
    ListNode* tail;
} LinkedList;


const int LN_SIZE = sizeof(ListNode);


void cwo_init_list(LinkedList* list){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

size_t cwo_list_size(LinkedList* list){
    return list->size;
}


void cwo_add_to_head(LinkedList* list, CWO_LL_VAL_TYPE value){
    ListNode* dummy = (ListNode*)malloc(LN_SIZE);
    if(dummy == NULL) return;
    dummy->val = value;

    if(list->size == 0){
        dummy->next = NULL;
        list->head = dummy;
        list->tail = dummy;
    }
    else {
        dummy->next = list->head;
        list->head = dummy;
    }

    list->size++;
}

void cwo_add_to_tail(LinkedList* list, CWO_LL_VAL_TYPE value){
    ListNode* dummy = (ListNode*)malloc(LN_SIZE);
    dummy->val = value;

    if(list->size == 0){
        dummy->next = NULL;
        list->head = dummy;
        list->tail = dummy;
    }
    else {
        dummy->next = NULL;
        list->tail->next = dummy;
        list->tail = dummy;
    }

    list->size++;
}


void cwo_delete_node(LinkedList* list, int index){
    if(index < 0) index = list->size + index - 1;
    if(list->size == 0) return;
    if(index > list->size - 1) return;

    ListNode* pre = NULL;
    ListNode* dummy = list->head;
    while(index >= 0){
        if(index == 0){
            if(pre == NULL){
                free(dummy);
                break;
            }
            pre->next = dummy->next;
            free(dummy);
        }
        pre = dummy;
        dummy = dummy->next;
        index--;
    }
    list->size--;
}


CWO_LL_VAL_TYPE cwo_get_value(LinkedList* list, int index){
    if(index < 0) index = list->size + index - 1;
    if(list->size == 0) return INVALID_LL_CWO_VAL;
    if(index > list->size - 1) return INVALID_LL_CWO_VAL;

    ListNode* pre = NULL;
    ListNode* dummy = list->head;
    while(index >= 0){
        if(index == 0){
            return dummy->val;
        }
        pre = dummy;
        dummy = dummy->next;
        index--;
    }
}


void cwo_print_list(LinkedList* list){
    if(list->head == NULL) return;

    ListNode* dummy = list->head;
    while(dummy != NULL){
        printf("%d ", dummy->val);
        dummy = dummy->next;
    }
}


void cwo_change_node_value(LinkedList* list, int index, CWO_LL_VAL_TYPE value){
    if(index < 0) index = list->size + index - 1;
    if(list->size == 0) return;
    if(index > list->size - 1) return;

    ListNode* pre = NULL;
    ListNode* dummy = list->head;
    while(index >= 0){
        if(index == 0){
            dummy->val = value;
        }
        pre = dummy;
        dummy = dummy->next;
        index--;
    }    
}


void cwo_delete_list(LinkedList* list){
    if(list->head == NULL) return;
    ListNode* dummy = list->head;
    
    while(list->head != list->tail){
        list->head = list->head->next;
        free(dummy);
        dummy = list->head;
    }
    free(list->head);
}

#endif //CWO_SINGLY_LINKED_LIST_IMPLEMENTATIONS


// Include doubly linked list library implementations 
#ifdef CWO_DOUBLY_LINKED_LIST_IMPLEMENTATIONS

typedef struct{
    int value;
    ListNode* next;
    ListNode* prev;
} ListNode;

#endif //CWO_DOUBLY_LINKED_LIST_IMPLEMENTATIONS

#endif //CWO_LINKED_LIST_H