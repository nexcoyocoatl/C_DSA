#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int
#define bool _Bool

struct deque
{
    int *a;
    uint front;
    uint end;
    uint size;
    uint capacity;
};

void deque_init(struct deque *d, uint _capacity);
void deque_add_first(struct deque *d, int e);
int deque_remove_first(struct deque *d);
void deque_add_last(struct deque *d, int e);
int deque_remove_last(struct deque *d);
uint deque_length(struct deque *d);
uint deque_max_size(struct deque *d);
void deque_resize(struct deque *d, uint new_capacity);
bool deque_is_empty(struct deque *d);
bool deque_is_full(struct deque *d);
void deque_print_contents(struct deque *d);
void deque_print_array(struct deque *d);

// Initializes deque
void deque_init(struct deque *d, uint _capacity)
{
    if (_capacity < 1)
    {
        return;
    }

    d->a = malloc(sizeof(int) * _capacity);
    d->front = 0;
    d->size = 0;
    d->capacity = _capacity;
}

// Adds element to the front of the deque
// Front alwayss points to the last existing element added to the front of the deque
void deque_add_first(struct deque *d, int e)
{
    if (d->capacity == d->size)
    {
        return;
    }

    d->front = (d->front + d->capacity - 1) % d->capacity;

    d->a[d->front] = e;

    d->size++;
}

// Removes element from the front of the deque
int deque_remove_first(struct deque *d)
{
    if (d->size == 0)
    {
        return -1;
    }

    int e = d->a[d->front];

    d->front = (d->front + 1) % d->capacity;

    d->size--;

    return e;
}

// Adds element to the end of the queue
// End always ponts to the next free space after the last existing element added to the end of the deque
void deque_add_last(struct deque *d, int e)
{
    if (d->capacity == d->size)
    {
        return;
    }

    uint end = (d->front + d->size) % d->capacity;

    d->a[end] = e;

    d->size++;
}

// Removes element from the end of the deque
int deque_remove_last(struct deque *d)
{
    if (d->size == 0)
    {
        return -1;
    }

    uint end = (d->front + d->size - 1) % d->capacity;

    int e = d->a[end];

    d->size--;

    return e;
}

// Finds element in the deque
bool deque_find_elem(struct deque *d, int e)
{
    if (d->size == 0)
    {
        return false;
    }

    size_t i = d->front;

    for (uint i = 0; i < d->size; i++) {
        if (d->a[(d->front + i) % d->capacity] == e)
        {
            return true;
        }
    }

    return false;
}

// Returns deque size / length
uint deque_length(struct deque *d)
{
    return d->size;
}

// Returns deque capacity / max size
uint deque_max_size(struct deque *d)
{
    return d->capacity;
}

// Resizes the deque (only increases, for now)
void deque_resize(struct deque *d, uint new_capacity)
{
    int *a2 = malloc(sizeof(int) * new_capacity);

    for (uint i = 0; i < d->size; i++) {
        a2[i] = d->a[(d->front + i) % d->capacity];
    }

    free(d->a);
    d->a = a2;

    d->front = 0;
    d->capacity = new_capacity;
}

// Returns true if deque is empty
bool deque_is_empty(struct deque *d)
{
    return (d->size == 0);
}

// Returns true if deque is full
bool deque_is_full(struct deque *d)
{
    return (d->size == d->capacity);
}

// Prints the contents of the deque in the right order
void deque_print_contents(struct deque *d)
{
    if (d->size == 0)
    {
        printf("Deque contents = []\n");
        return;
    }

    size_t i = d->front;

    uint end = (d->front + d->size) % d->capacity;

    printf("Deque contents = [ ");
    do
    {
        printf("%d ", d->a[i]);
        i = ++i % d->capacity;
    }
    while (i != end);

    printf("]\n");
}

// Prints the contents of the array in the array's order
void deque_print_array(struct deque *d)
{
    printf("Array contents = [ ");
    for (size_t i = 0; i < d->capacity; i++)
    {
        printf("%d ", d->a[i]);
    }
    printf("]\n");
}