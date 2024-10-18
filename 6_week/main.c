#include "dynarray.h"


int main()
{
    Dynarray a;
    init(&a, 0);
    for (size_t i = 0; i < 100; ++i)
    {
        push_back(&a, i);
    }
    pop_back(&a);
    resize(&a, 200);
    shrink_to_fit(&a);
    print_dynarray_info(&a);
    shallow_copy(&a);
    deep_copy(&a);
    print(&a);
    destroy(&a);
}