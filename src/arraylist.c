#include "arraylist.h"

#define AL_ELEMENT void * // Array List element wrapper 
#define DEF_SIZE 16       // Default size of the Array List upon creation 


typedef void (*arrlst_printf) (FILE *, AL_ELEMENT, size_t pos); // This type of functions prints an element of the Array List 
typedef void (*arrlst_freef) (AL_ELEMENT);                      // This type of functions frees an element of the Array List 


// This function creates new Array List and returns a pointer to it 
arrlst *arrlst_create(uint32_t size, arrlst_printf pef, arrlst_freef fef) {
    assert(size >= 0); // Size cannot be less than 0 
    arrlst *new = malloc(sizeof(arrlst)); // Allocating space for new array list   
    if (new == NULL) {
        fprintf(stderr, "Couldn't allocate space for a new Array List\n"); 
        return NULL;
    }
    assert(new != NULL); 
    new->data = malloc(size * sizeof(AL_ELEMENT)); // Allocating space for the data of the array list
    if (new->data == NULL) {
        fprintf(stderr, "Couldn't allocate space for the data of Array List\n"); 
        return NULL; 
    }
    assert(new->data != NULL); 
    new->cap = size;                      // Setting capacity to the given capacity 
    new->len = 0;                         // Setting length to 0, because no actual data is added yet 
    new->pef = pef;                       // Setting printing function to the given parameter
    new->fef = fef;                       // Setting freeing function to the given parameter 
    return new;                           // 
}


// Function which creates array list of default capacity 
arrlst *arrlst_create_def(arrlst_printf pef, arrlst_freef fef) {
    return arrlst_create(DEF_SIZE, pef, fef); 
}

// Function which resizes array list, and returns a status code 
static arrlst_status arrlst_resize(arrlst *arrlst) {
    if (arrlst == NULL) {
        fprintf(stderr, "Tried to resize NULL Array List\n");
        return RESIZE_NULL_ERR; 
    }
    assert(arrlst != NULL); 
    uint32_t cap = arrlst->cap;  
    uint32_t new_cap = !cap ? 16 : cap * 2;  
    AL_ELEMENT new = realloc(arrlst->data, new_cap * sizeof(AL_ELEMENT)); 
    if (new == NULL) {
        fprintf(stderr, "Couldn't resize data of Array List\n");
        return RESIZE_DATA_ERR; 
    }
    assert(new != NULL);
    arrlst->cap = new_cap;
    return OK; 
}

// Function which inserts an element at specified index into array list, and returns a status code 
arrlst_status arrlst_insert(arrlst *arrlst, uint32_t index, AL_ELEMENT elem) {
    if (arrlst == NULL) {
        fprintf(stderr, "Tried to insert an element into NULL Array List\n"); 
        return INSERT_ERR; 
    }
    assert(arrlst != NULL); 

    if (index < 0 || index >= arrlst->cap) {
        frptinf(stderr, "Index is out of bounds of array list\n"); 
        return INDEX_ERR; 
    }
    assert(index >= 0 && index < arrlst->cap); 

    if (arrlst->len >= arrlst->cap) {
        arrlst_status code = arrlst_resize(arrlst); 
        if (code != OK) {
            return code; 
        }
    }
    assert(arrlst->len < arrlst->cap); 

    arrlst->data[index] = elem;
    return OK; 
}