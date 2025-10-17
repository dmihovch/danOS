#include "../include/labels.h"


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
