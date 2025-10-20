#include <stdlib.h>
typedef struct {
    char** labels;
    int size;
    int cap;
} labels_t;

labels_t* alloc_labels(int);
void free_labels(labels_t*);
int labels_realloc(labels_t*);
void free_labels_chars(labels_t*);
