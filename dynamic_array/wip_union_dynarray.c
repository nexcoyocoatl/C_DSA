// Based on: aticleworld.com/implement-vector-in-c/

#include <stdlib.h>
#include <stdio.h>

#define DYNARRAY_INIT_SIZE 4

#define DYNARRAY_INIT(da, type) dynarray da;\
                          init(&da, type)

enum TYPE
{
    DYNARRAY_NULL = -1,
    DYNARRAY_INT = 0,
    DYNARRAY_STRING
};

typedef struct
{
    enum TYPE m_type;
    union {
        int *m_int;
        char **m_string;
    };
    size_t m_size;
    size_t m_capacity;
} s_dynarraylist;

typedef struct s_dynarray dynarray;
struct s_dynarray
{
    s_dynarraylist dynarray_list;
    size_t (*size) (dynarray *);
    void (*resize) (dynarray *, size_t);

    // (WIP) (Create a double struct for dynarrays? Macro?)
    void (*add) (dynarray *, void *);
    void (*set) (dynarray *, size_t, void *);
    void *(*get) (dynarray *, size_t);
    // (WIP)

    void (*del) (dynarray *, size_t);
    void (*free) (dynarray *);
};

size_t dynarray_size(dynarray *da)
{
    if (da)
    {
        return da->dynarray_list.m_size;
    }

    return 0;
}

void dynarray_resize_int(dynarray *da, size_t capacity)
{
    if (da)
    {
        int *items = realloc(da->dynarray_list.m_int, sizeof(int) * capacity);
        if (items)
        {
            da->dynarray_list.m_int = items;
            da->dynarray_list.m_capacity = capacity;
        }
    }
}

void dynarray_add_int(dynarray *da, int item)
{
    if (da)
    {
        if (da->dynarray_list.m_capacity == da->dynarray_list.m_size)
        {
            dynarray_resize_int( da, da->dynarray_list.m_capacity <<= 1 );
        }

        da->dynarray_list.m_int[da->dynarray_list.m_size++] = item;
    }
}

void dynarray_set_int(dynarray *da, size_t index, int item)
{
    if (da)
    {
        if ( (index >= 0) && (index < da->dynarray_list.m_size) )
        {
            da->dynarray_list.m_int[index] = item;
        }
    }
}

int dynarray_get_int(dynarray *da, size_t index)
{
    int data = 0;

    if (da)
    {
        if ( (index>=0) && (index < da->dynarray_list.m_size) )
        {
            data = da->dynarray_list.m_int[index];
        }
    }

    return data;
}

void dynarray_del_int(dynarray *da, size_t index)
{
    size_t i = 0;
    if(da)
    {
        if ( (index < 0) || (index >= da->dynarray_list.m_size) )
        {
            return;
        }

        da->dynarray_list.m_int[index] = 0;

        for (i = index; (i < da->dynarray_list.m_size - 1); i++)
        {
            da->dynarray_list.m_int[i] = da->dynarray_list.m_int[i+1];
        }
        da->dynarray_list.m_int[da->dynarray_list.m_size] = '\0';

        da->dynarray_list.m_size--;

        if ( (da->dynarray_list.m_size > 0) && ((da->dynarray_list.m_size) == ((da->dynarray_list.m_capacity) >>= 2 )) )
        {
            dynarray_resize_int(da, da->dynarray_list.m_capacity >> 1);
        }
    }
}

void dynarray_free_int(dynarray *da)
{
    if (da)
    {
        free(da->dynarray_list.m_int);
        da->dynarray_list.m_int = NULL;
    }
}

void dynarray_resize_string(dynarray *da, size_t capacity)
{
    if (da)
    {
        char **items = realloc(da->dynarray_list.m_string, sizeof(void *) * capacity);
        if (items)
        {
            da->dynarray_list.m_string = items;
            da->dynarray_list.m_capacity = capacity;
        }
    }
}

void dynarray_add_string(dynarray *da, char *item)
{
    if (da)
    {
        if (da->dynarray_list.m_capacity == da->dynarray_list.m_size)
        {
            dynarray_resize_string( da, da->dynarray_list.m_capacity <<= 1 );
        }

        da->dynarray_list.m_string[da->dynarray_list.m_size++] = item;
    }
}

void dynarray_set_string(dynarray *da, size_t index, char *item)
{
    if (da)
    {
        if ( (index >= 0) && (index < da->dynarray_list.m_size) )
        {
            da->dynarray_list.m_string[index] = item;
        }
    }
}

char *dynarray_get_string(dynarray *da, size_t index)
{
    void *data = NULL;

    if (da)
    {
        if ( (index>=0) && (index < da->dynarray_list.m_size) )
        {
            data = da->dynarray_list.m_string[index];
        }
    }

    return data;
}

void dynarray_del_string(dynarray *da, size_t index)
{
    size_t i = 0;
    if(da)
    {
        if ( (index < 0) || (index >= da->dynarray_list.m_size) )
        {
            return;
        }

        da->dynarray_list.m_string[index] = NULL;

        for (i = index; (i < da->dynarray_list.m_size - 1); i++)
        {
            da->dynarray_list.m_string[i] = da->dynarray_list.m_string[i+1];
        }
        da->dynarray_list.m_string[da->dynarray_list.m_size] = NULL;

        da->dynarray_list.m_size--;

        if ( (da->dynarray_list.m_size > 0) && ((da->dynarray_list.m_size) == ((da->dynarray_list.m_capacity) >>= 2 )) )
        {
            dynarray_resize_string(da, da->dynarray_list.m_capacity >> 1);
        }
    }
}

void dynarray_free_string(dynarray *da)
{
    if (da)
    {
        free(da->dynarray_list.m_string);
        da->dynarray_list.m_string = NULL;
    }
}

void init(dynarray *da, int type)
{
    da->size = dynarray_size;

    da->dynarray_list.m_type = type;
    da->dynarray_list.m_capacity = DYNARRAY_INIT_SIZE;
    da->dynarray_list.m_size = 0;

    switch (da->dynarray_list.m_type)
    {
        case DYNARRAY_INT:
        {
            da->resize = dynarray_resize_int;
            da->add = dynarray_add_int;
            da->set = dynarray_set_int;
            da->get = dynarray_get_int;
            da->del = dynarray_del_int;
            da->free = dynarray_free_int;

            da->dynarray_list.m_int = malloc( sizeof(int *) * da->dynarray_list.m_capacity );    
            break;
        }

        case DYNARRAY_STRING:
        {
            da->resize = dynarray_resize_string;
            da->add = dynarray_add_string;
            da->set = dynarray_set_string;
            da->get = dynarray_get_string;
            da->del = dynarray_del_string;
            da->free = dynarray_free_string;

            da->dynarray_list.m_string = malloc( sizeof(char *) * da->dynarray_list.m_capacity );
        }

        case DYNARRAY_NULL:
        {
        }
        default:
        {
            exit(EXIT_FAILURE);
        }
    }

    if (!da->dynarray_list.m_int || !da->dynarray_list.m_string)
    {
        exit(EXIT_FAILURE);
    }
}

void test()
{
    DYNARRAY_INIT(da, DYNARRAY_INT);

    da.add(&da,"test");
    int value = 1;
    da.add(&da, &value);
    da.add(&da, "a");
    da.add(&da, (void*) 3); // breaks

    // Print elements through casting
    for (size_t i = 0; i < da.size(&da); i++)
    {
        if (i == 1 || i == 3)
        {
            printf("%d\n", *((int*)da.get(&da, i)));

            continue;
        }
        printf("%s\n", (char*)da.get(&da, i));
    }
}

int main(int argc, char *argv[])
{
    test();

    return 0;
}