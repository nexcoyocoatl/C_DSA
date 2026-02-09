#include "macro_dynlist.h"

// Passes array by reference to avoid malloc on a local scope
// void test_int_inside_function(int **dynarray)
// {
//     for (int i = 14; i > 0; i--)
//     {
//         // Will need to malloc here
//         dynarray_push_first(dynarray, i);
//     }
// }

int main()
{
    dynlist(int) a;
    dynlist_init(a);
    
    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // for (size_t i = 0; i <= 15; i++)
    // {
    //     dynarray_push_last(&a, i+15);
    //     printf("%d ", a[i]);
    // }
    // printf("\n");

    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // test_int_inside_function(&a);

    // for (size_t i = 0; i < dynarray_size(&a); i++)
    // {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");

    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // for (size_t i = 0; i < 15; i++)
    // {
    //     dynarray_remove_first(&a);
    // }

    // for (size_t i = 0; i < dynarray_size(&a); i++)
    // {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");

    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // for (size_t i = 0; i < 10; i++)
    // {
    //     dynarray_remove_last(&a);
    // }

    // for (size_t i = 0; i < dynarray_size(&a); i++)
    // {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");

    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // dynarray_remove_last(&a);

    // printf("size: %llu\n", dynarray_size(&a));
    // printf("capacity: %llu\n", dynarray_capacity(&a));

    // dynarray(char*) b;
    // dynarray_init(&b);

    // printf("b size: %llu\n", dynarray_size(&b));
    // printf("b capacity: %llu\n", dynarray_capacity(&b));

    // char* s = "a";
    // dynarray_push_last(&b, s);
    // s = "b";
    // dynarray_push_last(&b, s);

    // for (size_t i = 0; i < 2; i++)
    // {
        
    //     printf("%s, ", b[i]);
    // }
    // printf("\n");

    // struct test1{
    //     int num;
    // };

    // dynarray(struct test1*) c;
    // dynarray_init(&c);
    // dynarray_push_last(&c, malloc(sizeof (*c) * 1));
    // c[0]->num = 1;
    // printf("%d\n", c[0]->num);

    // struct test2{
    //     char string[30];
    // };

    // dynarray(struct test2*) d;
    // dynarray_init(&d);
    // dynarray_push_last(&d, malloc(sizeof(char) * 13));
    // strcpy(d[0]->string, "Hello, World");
    // printf("%s\n", d[0]->string);

    // dynarray_free(&a);
    // dynarray_free(&b);
    // dynarray_free_all(&c, free);
    // dynarray_free_all(&d, free);

    return 0;
}