#include <stdlib.h>
typedef struct {
    char** labels;
    int size;
    int cap;
} labels_t;

labels_t* alloc_labels(int);
void free_labels(labels_t*);
