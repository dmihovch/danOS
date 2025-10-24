#include <stdlib.h>

typedef struct {
    char* name;
    int addr;
} label_t;


typedef struct {
    label_t* labels;
    int size;
    int cap;
} label_table_t;

void label_table_free(label_table_t*);
label_table_t* label_table_init(int);
int add_label(label_table_t*, char*, int);
int label_table_resize(label_table_t*);
label_t label_create(char*, int);
