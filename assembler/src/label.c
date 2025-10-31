
#include "../include/label.h"



label_table_t* label_table_init(int init_cap){

    label_table_t* lt = calloc(1,sizeof(label_table_t));
    if(lt == NULL){
        return NULL;
    }
    lt->labels = calloc(init_cap, sizeof(label_t));
    if(lt->labels == NULL){
        free(lt);
        return NULL;
    }
    lt->cap = init_cap;
    return lt;

}

void label_table_free(label_table_t* lt){
    int sz = lt->size;
    int i;
    for(i = 0; i<sz; i++){
        free(lt->labels[i].name);
    }
    free(lt->labels);
    free(lt);
}

int add_label(label_table_t* lt, char* name, int addr){
    if(lt->cap == lt->size && label_table_resize(lt)){
        return 1;
    }

    lt->labels[lt->size] = label_create(name,addr);
    lt->size++;
    return 0;
}

int label_table_resize(label_table_t* lt){
    lt->cap *= 2;
    lt->labels = realloc(lt->labels, lt->cap);
    if(lt->labels == NULL){
        return 1;
    }
    return 0;
}

label_t label_create(char* name, int addr){
    label_t l = {name,addr};
    return l;
}
