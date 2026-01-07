#ifndef _MACRO_DYNARRAY_H_
#define _MACRO_DYNARRAY_H_

// based on https://crocidb.com/post/simple-vector-implementation-in-c/
//    and https://www.youtube.com/watch?v=HvG03MY2H04

#include <stdlib.h>
#include <string.h>

#define uint64 unsigned long long

struct dynarray_header
{
    uint64 m_capacity;
    uint64 m_size;
};

// Creates a dynamic array (eg: dynarray(int) a -> int a*)
#define dynarray(T) T*

// Initializes dynamic array, allocating 8 spaces from the start
#define dynarray_init(DA) \
    { \
        uint64 initial_capacity = 8; \
        struct dynarray_header *header = malloc((sizeof(*header)) + (uint64)(initial_capacity*sizeof(**DA))); \
        header->m_capacity = initial_capacity; \
        header->m_size = 0; \
        (*DA) = (void*)(header + 1); \
    }

// Initializes dynamic array, allocating n spaces from the start
#define dynarray_init_n(DA, n) \
    { \
        uint64 initial_capacity = n; \
        struct dynarray_header *header = malloc((sizeof(*header)) + (uint64)(initial_capacity*sizeof(**DA))); \
        header->m_capacity = initial_capacity; \
        header->m_size = 0; \
        (*DA) = (void*)(header + 1); \
    }
    
// To get to the header, casts array to header type and subtracts 1
#define dynarray_get_header(DA) \
    (((struct dynarray_header*)(*DA)) - 1)

// Returns size by accessing the header
#define dynarray_size(DA) \
    ((*DA)? dynarray_get_header(DA)->m_size : 0)

// Returns capacity from the header
#define dynarray_capacity(DA) \
    ((*DA)? dynarray_get_header(DA)->m_capacity : 0)

// Resizes with realloc to the required size
#define dynarray_resize(DA, required_size) \
    { \
        struct dynarray_header *header = dynarray_get_header(DA); \
        header->m_capacity = required_size; \
        header = (struct dynarray_header*)realloc(header, (sizeof *header) + (uint64)(required_size * sizeof(**DA))); \
        (*DA) = (void*)(header + 1); \
    }

// Shifts all elements to the left by one
#define dynarray_shift_left(DA) \
    { \
        for (uint64 i = 0; i < dynarray_size(DA) - 1; i++) \
        { \
            DA[i] = DA[i+1]; \
        } \
        dynarray_get_header(DA)->m_size--; \
    }

    // TODO: Shifts left from index
#define dynarray_left_right_from(DA, index) \
    { \
        \
    } \

// TODO: Shifts right from index
#define dynarray_shift_right_from(DA, index) \
    { \
        \
    } \

// TODO: Inserts element at index
#define dynarray_insert(DA, index) \
    { \
        \
    } \

// TODO: Removes element at index
#define dynarray_del(DA, index) \
    { \
        \
    } \

// Inserts an element to the end of the list,
// multiplying capacity by 2 if needed
#define dynarray_push(DA, E) \
    { \
        if ( (dynarray_get_header(DA)->m_size * 2) > dynarray_get_header(DA)->m_capacity ) \
        { \
            uint64 new_capacity = dynarray_get_header(DA)->m_capacity * 2; \
            dynarray_resize(DA, new_capacity); \
        } \
        (*DA)[dynarray_size(DA)] = E; \
        dynarray_get_header(DA)->m_size++; \
    }

// Removes element from the end of the line,
// dividing capacity by 2 if needed
#define dynarray_remove_last(DA) \
    { \
        if (dynarray_get_header(DA)->m_size) \
        { \
            if ( dynarray_get_header(DA)->m_size < (dynarray_get_header(DA)->m_capacity / 2) ) \
            { \
                uint64 new_capacity = dynarray_get_header(DA)->m_capacity / 2; \
                dynarray_resize(DA, new_capacity); \
            } \
            dynarray_get_header(DA)->m_size--; \
        } \
    }

// Takes out element from the end of the list
#define dynarray_pop(DA, out) \
    { out = (*DA)[dynarray_size(DA)-1]; dynarray_remove_last(DA); }

// Adds to the end of the list (same as push)
#define dynarray_enqueue(DA, E) \
    dynarray_push(DA, E)

// Takes out element from the start of the list
#define dynarray_dequeue(DA, out) \
    { out = DA[0]; dynarray_shift_left(DA); }

// out is assigned the first element of the list
#define dynarray_get_first(DA, out) \
    out = DA[0]

// out is assigned the last element of the list
#define dynarray_get_last(DA, out) \
    out = DA[dynarray_size(DA)-1]

// Clears list memory
#define dynarray_free(DA) \
    if (*DA) \
    {\
        memset(*DA, 0, (uint64)dynarray_size(DA) * (sizeof(**DA))); \
        free(dynarray_get_header(DA));\
        (*DA) = NULL;\
    } \

// Clears list memory and its objects (for a list of objects in the heap)
#define dynarray_free_all(DA, F) \
    { \
    if (*DA) \
        { \
            for (uint64 i = 0; i < dynarray_size(DA); i++) \
            { \
                F((*DA)[i]); \
            } \
            memset(*DA, 0, (uint64)dynarray_size(DA) * (sizeof(**DA))); \
            free(dynarray_get_header(DA)); \
            (*DA) = NULL; \
        } \
    }

#endif
