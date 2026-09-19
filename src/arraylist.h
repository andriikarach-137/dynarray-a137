#ifndef ARRAYLIST_H 
#define ARRAYLIST_H 

#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>


#define AL_ELEMENT void * // Array List element wrapper 
#define DEF_SIZE 16       // Default size of the Array List upon creation 

typedef void (*arrlst_printf) (FILE *, AL_ELEMENT, size_t pos); // This type of functions prints an element of the Array List 
typedef void (*arrlst_freef) (AL_ELEMENT);                      // This type of functions frees an element of the Array List 


// Enum that represents various error codes related to handling of the Array List 
typedef enum {
    OK, 
    RESIZE_NULL_ERR,
    RESIZE_DATA_ERR,
    INSERT_ERR,
    INDEX_ERR, 
} arrlst_status; 


// Structure that represents Array List - random-access array which can grow dynamically  
typedef struct arrlst {
    AL_ELEMENT *data;   // Array of generic values 
    uint32_t cap;       // Current capacity of the array 
    uint32_t len;    // Current actual length of the array
    arrlst_printf pef;  // Pointer to the function that prints an element of the Array List 
    arrlst_freef fef;   // Pointer to the function that frees an element of the Array List
} arrlst; 


// This function creates new Array List and returns a pointer to it 
extern arrlst *arrlst_create(uint32_t size, arrlst_printf pef, arrlst_freef fef); 

// Function which creates array list of default capacity 
extern arrlst *arrlst_create_def(arrlst_printf pef, arrlst_freef fef); 

extern arrlst_status arrlst_insert(arrlst *arrlst, uint32_t index, AL_ELEMENT elem);


#endif 