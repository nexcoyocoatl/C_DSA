#ifndef _MACRO_dynlist_H_
#define _MACRO_dynlist_H_

// based on https://crocidb.com/post/simple-vector-implementation-in-c/
//    and https://www.youtube.com/watch?v=HvG03MY2H04

#include <stdlib.h>
#include <string.h>

#define uint64 unsigned long long

#define dynlist(T) struct dynlist \
{ \
    uint64 capacity; \
    uint64 size; \
    T* array; \
}; \
struct dynlist

// Initializes dynamic array, allocating 8 spaces from the start
#define dynlist_init(DL) \
    { \
        uint64 initial_capacity = 8; \
        DL->array = malloc(initial_capacity * sizeof (DL.array)); \
        header.m_capacity = initial_capacity; \
        header.m_size = 0; \
    }

// Initializes dynamic array, allocating n spaces from the start
#define dynlist_init_n(DL, n) \
    { \
        uint64 initial_capacity = 8; \
        DL->array = malloc(initial_capacity * sizeof (DL.array)); \
        header.m_capacity = initial_capacity; \
        header.m_size = 0; \
    }
    
// To get to the header, casts array to header type and subtracts 1
#define dynlist_get_header(DL) \
    (((struct dynlist_header*)DL) - 1)

// Returns size by accessing the header
#define dynlist_size(DL) \
    (DL? dynlist_get_header(DL)->m_size : 0)

// Returns capacity from the header
#define dynlist_capacity(DL) \
    (DL? dynlist_get_header(DL)->m_capacity : 0)

// Resizes with realloc to the required size
#define dynlist_resize(DL, required_size) \
    { \
        struct dynlist_header *header = dynlist_get_header(DL); \
        header->m_capacity = required_size; \
        header = (struct dynlist_header*)realloc(header, (sizeof *header) + (uint64)(required_size * sizeof(*DL))); \
        DL = (void*)(header + 1); \
    }

// Multiplies capacity by 2 if needed
#define dynlist_check_enlarge(DL) \
{ \
    if ( (dynlist_get_header(DL)->m_size * 2) > dynlist_get_header(DL)->m_capacity ) \
    { \
        uint64 new_capacity = dynlist_get_header(DL)->m_capacity * 2; \
        dynlist_resize(DL, new_capacity); \
    } \
}

// Divides capacity by 2 if needed
#define dynlist_check_reduce(DL) \
{ \
    if ( dynlist_get_header(DL)->m_size < (dynlist_get_header(DL)->m_capacity / 2) ) \
    { \
        uint64 new_capacity = dynlist_get_header(DL)->m_capacity / 2; \
        dynlist_resize(DL, new_capacity); \
    } \
}

// Shifts left from end to index
#define dynlist_shift_left_to(DL, index) \
    { \
        for (uint64 i = index; i < dynlist_size(DL) - 1; i++) \
        { \
            DL[i] = DL[i+1]; \
        } \
    } \

// Shifts right from index
#define dynlist_shift_right_from(DL, index) \
    { \
        for (uint64 i = dynlist_size(DL); i > index; i--) \
        { \
            DL[i] = DL[i-1]; \
        } \
    } \

// Shifts all elements to the left by one
#define dynlist_shift_left(DL) \
    { \
        dynlist_shift_left_to(DL, 0); \
    }

// Shifts all elements to the right by one
#define dynlist_shift_right(DL) \
    { \
        dynlist_shift_right_from(DL, 0); \
    }

// TODO: Inserts element at index
#define dynlist_push(DL, E, index) \
    { \
        dynlist_check_enlarge(DL); \
        dynlist_shift_right_from(DL, index); \
        DL[index] = E; \
        dynlist_get_header(DL)->m_size++; \
    } \

// TODO: Removes element at index
#define dynlist_remove(DL, index) \
    { \
        dynlist_shift_left_to(DL, index) \
        dynlist_check_reduce(DL); \
        dynlist_get_header(DL)->m_size--; \
    } \

// out is assigned the i element of the list
#define dynlist_get(DL, i, out) \
    out = DL[i]

// out is assigned the first element of the list
#define dynlist_get_first(DL, out) \
    out = DL[0]

// out is assigned the last element of the list
#define dynlist_get_last(DL, out) \
    out = DL[dynlist_size(DL)-1]

// Adds to the start of the list
#define dynlist_push_first(DL, E) \
    { \
        dynlist_push(DL, E, 0); \
    }

// Inserts an element to the end of the list,
#define dynlist_push_last(DL, E) \
    { \
        dynlist_check_enlarge(DL); \
        DL[dynlist_size(DL)] = E; \
        dynlist_get_header(DL)->m_size++; \
    }

// Removes element from the start of the list,
#define dynlist_remove_first(DL) \
    { \
        if (dynlist_get_header(DL)->m_size) \
        { \
            dynlist_shift_left(DL); \
            dynlist_check_reduce(DL); \
            dynlist_get_header(DL)->m_size--; \
        } \
    }

// Removes element from the end of the list,
#define dynlist_remove_last(DL) \
    { \
        if (dynlist_get_header(DL)->m_size) \
        { \
            dynlist_get_header(DL)->m_size--; \
            dynlist_check_reduce(DL); \
        } \
    }

// Takes out element from the end of the list
#define dynlist_pop_last(DL, out) \
    { out = DL[dynlist_size(DL)-1]; dynlist_remove_last(DL); }

// Takes out element from the start of the list
#define dynlist_pop_first(DL, out) \
    { out = DL[0]; dynlist_remove_first(DL); }

// Clears list memory
#define dynlist_free(DL) \
    if (DL) \
    {\
        memset(DL, 0, (uint64)dynlist_size(DL) * (sizeof(*DL))); \
        free(dynlist_get_header(DL));\
        DL = NULL;\
    } \

// Clears list memory and its objects (for a list of objects in the heap)
#define dynlist_free_all(DL, F) \
    { \
    if (DL) \
        { \
            for (uint64 i = 0; i < dynlist_size(DL); i++) \
            { \
                F(DL[i]); \
            } \
            memset(DL, 0, (uint64)dynlist_size(DL) * (sizeof(*DL))); \
            free(dynlist_get_header(DL)); \
            DL = NULL; \
        } \
    }

#endif
