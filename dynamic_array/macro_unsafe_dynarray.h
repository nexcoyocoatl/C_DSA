#ifndef _MACRO_UNSAFE_DYNARRAY_H_
#define _MACRO_UNSAFE_DYNARRAY_H_

// based on https://crocidb.com/post/simple-vector-implementation-in-c/
//    and https://www.youtube.com/watch?v=HvG03MY2H04

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct unsafe_dynarray_header
{
    uint64_t m_capacity;
    uint64_t m_size;
};

// Creates a dynamic array (eg: unsafe_dynarray(int) a -> int a*)
#define unsafe_dynarray(T) T*

// Initializes dynamic array, allocating 8 spaces from the start
#define unsafe_dynarray_init(DA) \
    { \
        uint64_t initial_capacity = 8; \
        struct unsafe_dynarray_header *header = malloc((sizeof(*header)) + (uint64_t)(initial_capacity*sizeof(**(DA)))); \
        header->m_capacity = initial_capacity; \
        header->m_size = 0; \
        (*(DA)) = (void*)(header + 1); \
    }

// Initializes dynamic array, allocating n spaces from the start
#define unsafe_dynarray_init_n(DA, n) \
    { \
        uint64_t initial_capacity = n; \
        struct unsafe_dynarray_header *header = malloc((sizeof(*header)) + (uint64_t)(n*sizeof(**(DA)))); \
        header->m_capacity = n; \
        struct unsafe_dynarray_header *header = malloc((sizeof(*header)) + (uint64_t)(initial_capacity*sizeof(**(DA)))); \
        header->m_capacity = initial_capacity; \
        header->m_size = 0; \
        (*(DA)) = (void*)(header + 1); \
    }

// To get to the header, casts array to header type and subtracts 1
#define unsafe_dynarray_get_header(DA) \
    (((struct unsafe_dynarray_header*)(*(DA))) - 1)

// Returns size by accessing the header
#define unsafe_dynarray_size(DA) \
    ((*(DA))? unsafe_dynarray_get_header(DA)->m_size : 0)

// Returns capacity from the header
#define unsafe_dynarray_capacity(DA) \
    ((*(DA))? unsafe_dynarray_get_header(DA)->m_capacity : 0)

// Resizes with realloc to the required size
#define unsafe_dynarray_resize(DA, required_size) \
    { \
        struct unsafe_dynarray_header *header = unsafe_dynarray_get_header(DA); \
        header->m_capacity = required_size; \
        header = (struct unsafe_dynarray_header*)realloc(header, (sizeof *header) + (uint64_t)(required_size * sizeof(**(DA)))); \
        (*(DA)) = (void*)(header + 1); \
    }

// Multiplies capacity by 2 if needed
#define unsafe_dynarray_check_enlarge(DA) \
{ \
    if ( (unsafe_dynarray_get_header(DA)->m_size * 2) > unsafe_dynarray_get_header(DA)->m_capacity ) \
    { \
        uint64_t new_capacity = unsafe_dynarray_get_header(DA)->m_capacity * 2; \
        unsafe_dynarray_resize(DA, new_capacity); \
    } \
}

// Divides capacity by 2 if needed
#define unsafe_dynarray_check_reduce(DA) \
{ \
    if ( unsafe_dynarray_get_header(DA)->m_size < (unsafe_dynarray_get_header(DA)->m_capacity / 2) ) \
    { \
        uint64_t new_capacity = unsafe_dynarray_get_header(DA)->m_capacity / 2; \
        unsafe_dynarray_resize(DA, new_capacity); \
    } \
}

// Shifts left from end to index
#define unsafe_dynarray_shift_left_to(DA, index) \
    { \
        for (uint64_t i = index; i < unsafe_dynarray_size(DA) - 1; i++) \
        { \
            (*(DA))[i] = (*(DA))[i+1]; \
        } \
    } \

// Shifts right from index
#define unsafe_dynarray_shift_right_from(DA, index) \
    { \
        for (uint64_t i = unsafe_dynarray_size(DA); i > index; i--) \
        { \
            (*(DA))[i] = (*(DA))[i-1]; \
        } \
    } \

// Shifts all elements to the left by one
#define unsafe_dynarray_shift_left(DA) \
    { \
        unsafe_dynarray_shift_left_to(DA, 0); \
    }

// Shifts all elements to the right by one
#define unsafe_dynarray_shift_right(DA) \
    { \
        unsafe_dynarray_shift_right_from(DA, 0); \
    }

// Inserts element at index
#define unsafe_dynarray_push(DA, E, index) \
    { \
        unsafe_dynarray_check_enlarge(DA); \
        unsafe_dynarray_shift_right_from(DA, index); \
        (*(DA))[index] = E; \
        unsafe_dynarray_get_header(DA)->m_size++; \
    } \

// Removes element at index
#define unsafe_dynarray_remove(DA, index) \
    { \
        unsafe_dynarray_shift_left_to(DA, index) \
        unsafe_dynarray_check_reduce(DA); \
        unsafe_dynarray_get_header(DA)->m_size--; \
    } \

// out is assigned the i element of the list
#define unsafe_dynarray_get(DA, i, out) \
    out = (*(DA))[i]

// out is assigned the first element of the list
#define unsafe_dynarray_get_first(DA, out) \
    out = (*(DA))[0]

// out is assigned the last element of the list
#define unsafe_dynarray_get_last(DA, out) \
    out = (*(DA))[unsafe_dynarray_size(DA)-1]

// Adds to the start of the list
#define unsafe_dynarray_push_first(DA, E) \
    { \
        unsafe_dynarray_push(DA, E, 0); \
    }

// Inserts an element to the end of the list,
#define unsafe_dynarray_push_last(DA, E) \
    { \
        unsafe_dynarray_check_enlarge(DA); \
        (*(DA))[unsafe_dynarray_size(DA)] = E; \
        unsafe_dynarray_get_header(DA)->m_size++; \
    }

// Removes element from the start of the list,
#define unsafe_dynarray_remove_first(DA) \
    { \
        if (unsafe_dynarray_get_header(DA)->m_size) \
        { \
            unsafe_dynarray_shift_left(DA); \
            unsafe_dynarray_check_reduce(DA); \
            unsafe_dynarray_get_header(DA)->m_size--; \
        } \
    }

// Removes element from the end of the list,
#define unsafe_dynarray_remove_last(DA) \
    { \
        if (unsafe_dynarray_get_header(DA)->m_size) \
        { \
            unsafe_dynarray_get_header(DA)->m_size--; \
            unsafe_dynarray_check_reduce(DA); \
        } \
    }

// Takes out element from the end of the list
#define unsafe_dynarray_pop_last(DA, out) \
    { out = (*(DA))[unsafe_dynarray_size(DA)-1]; unsafe_dynarray_remove_last(DA); }

// Takes out element from the start of the list
#define unsafe_dynarray_pop_first(DA, out) \
    { out = (*(DA))[0]; unsafe_dynarray_remove_first(DA); }

// Clears list memory
#define unsafe_dynarray_free(DA) \
    if (*(DA)) \
    {\
        memset(*(DA), 0, (uint64_t)unsafe_dynarray_size(DA) * (sizeof(**(DA)))); \
        free(unsafe_dynarray_get_header(DA));\
        (*(DA)) = NULL;\
    } \

// Clears list memory and its objects (for a list of objects in the heap)
#define unsafe_dynarray_free_all(DA, F) \
    { \
    if (*(DA)) \
        { \
            for (uint64_t i = 0; i < unsafe_dynarray_size(DA); i++) \
            { \
                F((*(DA))[i]); \
            } \
            memset(*(DA), 0, (uint64_t)unsafe_dynarray_size(DA) * (sizeof(**(DA)))); \
            free(unsafe_dynarray_get_header(DA)); \
            (*(DA)) = NULL; \
        } \
    }

#endif