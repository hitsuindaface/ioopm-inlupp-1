#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

ioopm_list_t *ioopm_linked_list_create(void){
    ioopm_list_t *lst = calloc(1, sizeof(ioopm_list_t));
    lst->head = NULL;
    lst->last = NULL;
    return lst;
}

ioopm_link_t *link_create(int value, ioopm_link_t *next){
    ioopm_link_t *link = calloc(1, sizeof(ioopm_link_t));
    link->value = value;
    link->next = next;
    return link;
}

void ioopm_linked_list_destroy(ioopm_list_t **list) {
    assert(*list); // Check if the list exists
    ioopm_link_t *curr = (*list)->head;

    while ( curr ) {
        ioopm_link_t *tmp = curr; // Define a temp variable so we can keep the loop going without terminating it
        curr = curr->next;
        free(tmp); // Free the link allocation
    }
    free(*list); // Free the list allocation
    *list = NULL;

}

void ioopm_linked_list_prepend( ioopm_list_t *list, int num ) {
    assert(list);
    list->head = link_create(num, list->head);
    list->size++;
}

void ioopm_linked_list_append( ioopm_list_t *list, int num ) {
    assert(list);
    ioopm_link_t *new_link = link_create(num, NULL);

    //if the list is empty
    if (list->head==NULL){
        list->head=new_link;
        list->last=new_link;
    }
    else {
        list->last->next = new_link;
        list->last = new_link;
    }

    list->size++;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    ioopm_link_t *lst = list->head;
    int i=0;

    if(index==list->size){
        ioopm_linked_list_append(list, value);
    }
    else{
        for (i=0; i<index; i++)
        {
            lst=lst->next;
        }
        ioopm_link_t *temp = lst; 
        lst->value = value;
        lst->next = temp;
        list->size++; 
    }
};

int ioopm_linked_list_remove(ioopm_list_t *list, int index){
    int currIndex = 0;
    ioopm_link_t *curr = list->head;
    ioopm_link_t *prev = NULL;
    ioopm_link_t *nxt = NULL;
    if ( index == 0 ) {
        list->head = curr->next;
    } else if ( index == list->size - 1) {
        curr = list->last;
        list->last = NULL;
    } else {
        while ( currIndex < index-1 ) {
            curr = curr->next;
            currIndex++;
        }
        prev = curr; // index-1
        curr = curr->next; // index
        nxt = curr->next; // index+1
        prev->next = nxt; // disconnect curr from list
    }
    int val = curr->value;
    list->size -= 1;
    free(curr);
    return val;
}

int ioopm_linked_list_get(ioopm_list_t *list, int index) {
    int currIndex = 0;
    ioopm_link_t *curr = list->head;
    if ( index == 0 ) {
        return curr->value;
    } else if ( index == list->size - 1) {
        return list->last->value;
    } else {
        while ( currIndex < index ) {
            currIndex++;
            curr = curr->next;
        }
    }
    int val = curr->value;
    return val;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, int element) {
    ioopm_link_t *curr = list->head;
    while ( curr != NULL ) {
        if ( curr->value == element ) {
            return true;
        } else {
            curr = curr->next;
        }
    }
    return false;
}

void print_list(ioopm_list_t *lst){
    ioopm_link_t *curr_elem = lst->head;
    printf("list: "); 
    while ( curr_elem != NULL ) {
        printf("%d, ", curr_elem->value);
        curr_elem = curr_elem->next;
    }
    printf("\n");
}

int ioopm_linked_list_size(ioopm_list_t *list) {
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list){
    return list->size==0;
}

void ioopm_linked_list_clear(ioopm_list_t *list){
    ioopm_link_t *curr = list->head;

    while ( curr != NULL ) { 
        ioopm_link_t *tmp = curr; // Define a temp variable so we can keep the loop going without terminating it
        curr = curr->next;
        free(tmp); // Free the link allocation
    }
    list->head = NULL;
    list->last = NULL;
    list->size = 0;
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra) {
    ioopm_link_t *curr = list->head;
    bool result = true;
    while ( curr != NULL && result )
    {
        result = result && prop(curr->value, extra);
        curr = curr->next;
    }
    return result;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra) {
    ioopm_link_t *curr = list->head;
    bool result = false;
    while( curr != NULL && !result )
    {
        result = result || prop(curr->value, extra);
        curr = curr->next; 
    }
    return result;
}

bool isSpecificInt(int val, void* extra) {
    int *temp = (int*)extra;
    int pred =  *temp;
    if ( val == pred ) {
        return true;
    } else {
        return false;
    }
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra) {
    ioopm_link_t *curr = list->head;
    while( curr != NULL )
    {
        curr->value = fun(curr->value, extra);
        curr = curr->next; 
    }
}

int add_int( int num, void *extra){
    //turning extra to type int
    int *temp = (int*)extra;
    int adder =  *temp;
    
    return num + adder;
}