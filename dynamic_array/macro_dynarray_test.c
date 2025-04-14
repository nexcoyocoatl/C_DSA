#include <stdio.h>
#include <stdlib.h>
#include "macro_dynarray.c"

int main()
{
    dynarray(int) a;
    dynarray_init(a);
    
    printf("size: %lu\n", dynarray_size(a));
    printf("capacity: %lu\n", dynarray_capacity(a));

    for (size_t i = 0; i < 30; i++)
    {
        dynarray_push(a, i);
        printf("%d, ", a[i]);
    }
    printf("\n");

    printf("size: %lu\n", dynarray_size(a));
    printf("capacity: %lu\n", dynarray_capacity(a));

    for (size_t i = 0; i <= 30; i++)
    {
        printf("%d, ", a[i]);
    }
    printf("\n");

    printf("size: %lu\n", dynarray_size(a));
    printf("capacity: %lu\n", dynarray_capacity(a));

    for (size_t i = 0; i < 15; i++)
    {
        dynarray_pop(a);
    }

    printf("size: %lu\n", dynarray_size(a));
    printf("capacity: %lu\n", dynarray_capacity(a));

    dynarray_pop(a);

    printf("size: %lu\n", dynarray_size(a));
    printf("capacity: %lu\n", dynarray_capacity(a));

    dynarray(char*) b;
    dynarray_init(b);

    printf("b size: %lu\n", dynarray_size(b));
    printf("b capacity: %lu\n", dynarray_capacity(b));

    char* s = "a";
    dynarray_push(b, s);
    s = "b";
    dynarray_push(b, s);

    for (size_t i = 0; i < 2; i++)
    {
        
        printf("%s, ", b[i]);
    }
    printf("\n");

    struct test1{
        int num;
    };

    dynarray(struct test1*) c;
    dynarray_init(c);
    dynarray_push(c, malloc(sizeof *c * 1));
    c[0]->num = 1;
    printf("%d\n", c[0]->num);

    struct test2{
        char string[30];
    };

    dynarray(struct test2*) d;
    dynarray_init(d);
    dynarray_push(d, malloc(sizeof *d * 1));
    strcpy(d[0]->string, "Hello, World");
    printf("%s\n", d[0]->string);

    dynarray_free(a);
    dynarray_free(b);
    dynarray_free_all(c, free);
    dynarray_free_all(d, free);

    return 0;
}