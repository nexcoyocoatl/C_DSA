
#ifndef _MACRO_FIXEDYNARRAY_H_
#define _MACRO_FIXEDYNARRAY_H_

// based on https://crocidb.com/post/simple-vector-implementation-in-c/
//    and https://www.youtube.com/watch?v=HvG03MY2H04

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

struct fixedynarray_header
{
    uint64_t m_capacity;
    uint64_t m_size;
};

// Creates a fixed dynamic array (eg: fixedynarray(int) a -> int a*)
#define fixedynarray(T) T*

// Initializes fixed dynamic array, allocating n spaces
#define fixedynarray_init(DA, n) \
    do { \
        if (*(DA) != NULL) { \
            fixedynarray_free(DA); \
        } \
        uint64_t capacity = n; \
        uint64_t size = sizeof(struct fixedynarray_header) + (uint64_t)(capacity*sizeof(**(DA))); \
        struct fixedynarray_header *header = (struct fixedynarray_header*) calloc(1, size); \
        if (header == NULL) { \
            fprintf(stderr, "fixedynarray error: calloc failed\n"); \
        } \
        else \
        { \
            header->m_capacity = capacity; \
            header->m_size = 0; \
            (*(DA)) = (void*)(header + 1); \
        } \
    } while(0)
    
// To get to the header, casts array to header type and subtracts 1
#define fixedynarray_get_header(DA) \
    (((struct fixedynarray_header*)(*(DA))) - 1)

// Returns size by accessing the header
#define fixedynarray_size(DA) \
    ((*(DA))? fixedynarray_get_header(DA)->m_size : 0)

// Returns capacity from the header
#define fixedynarray_capacity(DA) \
    ((*(DA))? fixedynarray_get_header(DA)->m_capacity : 0)

// Shifts left from end to index
#define fixedynarray_shift_left_to(DA, index) \
    do { \
        for (uint64_t i = index; i < fixedynarray_size(DA) - 1; i++) \
        { \
            (*(DA))[i] = (*(DA))[i+1]; \
        } \
    } while(0)

// Shifts right from index
#define fixedynarray_shift_right_from(DA, index) \
    do { \
        for (uint64_t i = fixedynarray_size(DA); i > index; i--) \
        { \
            (*(DA))[i] = (*(DA))[i-1]; \
        } \
    } while(0)

// Shifts all elements to the left by one
#define fixedynarray_shift_left(DA) \
    do { \
        fixedynarray_shift_left_to(DA, 0); \
    } while(0)

// Shifts all elements to the right by one
#define fixedynarray_shift_right(DA) \
    do { \
        fixedynarray_shift_right_from(DA, 0); \
    } while(0)

// Inserts element at index
#define fixedynarray_push(DA, E, index) \
    do { \
        if (fixedynarray_size(DA) >= fixedynarray_capacity(DA)) \
        { \
            fprintf(stderr, "fixedynarray error: array full\n"); \
        } \
        else \
        { \
            fixedynarray_shift_right_from(DA, index); \
            (*(DA))[index] = E; \
            fixedynarray_get_header(DA)->m_size++; \
        } \
    } while(0)

// Removes element at index
#define fixedynarray_remove(DA, index) \
    do { \
        if (fixedynarray_size(DA)) \
        { \
            fixedynarray_shift_left_to(DA, index); \
            fixedynarray_get_header(DA)->m_size--; \
        } \
        else \
        { \
            fprintf(stderr, "fixedynarray error: array empty\n"); \
        } \
    } while(0)

// Returns the i element of the list
#define fixedynarray_get(DA, i) \
    (assert((i) < fixedynarray_size((DA)) && "fixedynarray: out of bounds!"), (*(DA))[(i)])

// Returns the ADDRESS of the i-th element
#define fixedynarray_at(DA, i) \
    (assert((i) < fixedynarray_size((DA)) && "fixedynarray: out of bounds!"), &(*(DA))[(i)])

// Returns the first element of the list
#define fixedynarray_get_first(DA) \
    (assert(fixedynarray_size((DA)) > 0 && "fixedynarray: empty!"), (*(DA))[0])

// Returns the last element of the list
#define fixedynarray_get_last(DA) \
    (assert(fixedynarray_size((DA)) > 0 && "fixedynarray: empty!"), (*(DA))[(fixedynarray_size(DA)-1)])

// Adds to the start of the list
#define fixedynarray_push_first(DA, E) \
    do { \
        fixedynarray_push(DA, E, 0); \
    } while(0)

// Inserts an element to the end of the list,
#define fixedynarray_push_last(DA, E) \
    do { \
        if (fixedynarray_size(DA) >= fixedynarray_capacity(DA)) \
        { \
            fprintf(stderr, "fixedynarray error: array full\n"); \
        } \
        else \
        { \
            (*(DA))[fixedynarray_size(DA)] = E; \
            fixedynarray_get_header(DA)->m_size++; \
        } \
    } while(0)

// Removes element from the start of the list,
#define fixedynarray_remove_first(DA) \
    do { \
        if (fixedynarray_size(DA)) \
        { \
            fixedynarray_shift_left(DA); \
            fixedynarray_get_header(DA)->m_size--; \
        } \
        else \
        { \
            fprintf(stderr, "fixedynarray error: array empty\n"); \
        } \
    } while(0)

// Removes element from the end of the list,
#define fixedynarray_remove_last(DA) \
    do { \
        if (fixedynarray_size(DA)) \
        { \
            fixedynarray_get_header(DA)->m_size--; \
        } \
        else \
        { \
            fprintf(stderr, "fixedynarray error: array empty\n"); \
        } \
    } while(0)

// Takes out element from the end of the list
#define fixedynarray_pop_last(DA, out) \
    do { \
        assert(fixedynarray_size(DA) > 0); \
        out = (*(DA))[fixedynarray_size(DA)-1]; \
        fixedynarray_remove_last(DA); \
    } while(0)

// Takes out element from the start of the list
#define fixedynarray_pop_first(DA, out) \
    do { \
        assert(fixedynarray_size(DA) > 0); \
        out = (*(DA))[0]; \
        fixedynarray_remove_first(DA); \
    } while(0)

// Clears list memory
#define fixedynarray_free(DA) \
do { \
    if (*(DA)) \
    {\
        struct fixedynarray_header *header = fixedynarray_get_header(DA); \
        memset(*(DA), 0, ((uint64_t)header->m_capacity * sizeof(**(DA)))); \
        free(header);\
        (*(DA)) = NULL;\
    } \
} while(0)

// Clears list memory and its objects (for a list of objects in the heap)
#define fixedynarray_free_all(DA, F) \
    do { \
    if (*(DA)) \
        { \
            for (uint64_t i = 0; i < fixedynarray_size(DA); i++) \
            { \
                F((*(DA))[i]); \
            } \
            fixedynarray_free(DA); \
        } \
    } while(0)

#endif
