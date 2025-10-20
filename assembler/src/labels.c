#include "../include/labels.h"
#include <stdlib.h>



int labels_realloc(labels_t* l){
    char** tmp = realloc(l->labels, sizeof(char*)*(l->cap * 2));
    if(tmp == NULL){

        return 1;
    }
    free_labels_chars(l);
    l->labels = tmp;
    return 0;

}


labels_t* alloc_labels(int capacity){

    labels_t* l = calloc(1, sizeof(labels_t));
    if(l == NULL){
        return NULL;
    }
    l->cap = capacity;
    l->labels = calloc(capacity, sizeof(char*));
    if(l->labels == NULL){
        free(l);
        return NULL;
    }
    return l;
}
void free_labels(labels_t* l){

    for(int i = 0; i<l->size; i++){
        free(l->labels[i]);
    }
    free(l->labels);
    free(l);

}
void free_labels_chars(labels_t* l){
    for(int i = 0; i<l->size; i++){
        free(l->labels[i]);
    }
    free(l->labels);
}
