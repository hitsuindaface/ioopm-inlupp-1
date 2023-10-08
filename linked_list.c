#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct link
{
    int value;
    struct link *next;
};

struct list
{
    ioopm_link_t *head;
    ioopm_link_t *last;
    int size;
};

ioopm_list_t *ioopm_linked_list_create(void){
    return calloc(1, sizeof(ioopm_list_t));
}

ioopm_link_t *link_create(int value, ioopm_link_t *next){
    ioopm_link_t *link = calloc(1, sizeof(ioopm_link_t));
    link->value = value;
    link->next = next;
    return link;
}

void ioopm_linked_list_destroy(ioopm_list_t *list) {
    assert(list); // Check if the list exists
    ioopm_link_t *curr = list->head;

    while ( curr ) {
        ioopm_link_t *tmp = curr; // Define a temp variable so we can keep the loop going without terminating it
        curr = curr->next;
        free(tmp); // Free the link allocation
    }
    free(list); // Free the list allocation
}

void ioopm_linked_list_prepend( ioopm_list_t *list, int num ) {
    assert(list);
    list->head = link_create(num, list->head);
    list->size++;
}

void ioopm_linked_list_append( ioopm_list_t *list, int num ) {
    assert(list);
    ioopm_link_t *ins = list->last;
    ins->next = link_create(num, NULL);
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

int ioopm_linked_list_remove(ioopm_list_t *list, int index) {
    int currIndex = 0;
    ioopm_link_t *curr = list->head;
    ioopm_link_t *prev = NULL;
    ioopm_link_t *nxt = NULL;
    if ( index == 0 ) {
        list->head = curr->next
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