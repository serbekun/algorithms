#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SetArrayRandomValue(int *array, size_t array_size, char ArrayName) 
{

    for (int i = 0;i < array_size;i++) 
    {
        *(array + i) = rand() % (100 -0 + 1) + 0;
    }

    for (int i = 0;i < array_size;i++) 
    {
        printf("%c|%d - %d \n", ArrayName, i, *(array + i));
    }

}

void ElementwiseAbsDifference(int *a, int *b, int *c, size_t arrays_sizes) 
{

    for (int i = 0;i < arrays_sizes;i++) 
    {
        if (*(a + i) > *(b + i))
        {
            *(c + i) = *(a + i) - *(b + i);
        }
        else 
        {
            *(c + i) = *(b + i) - *(a + i);
        }
    }

    for (int i = 0;i < arrays_sizes;i++) 
    {
        printf("c|%d - %d \n", i, *(c + i));
    }

}

int main() 
{ 

    //init values
    size_t a_size = 100;
    size_t b_size = 100;
    size_t c_size = 100;
    int a[100];
    int b[100];
    int c[100];
    int *ptr_a = a;
    int *ptr_b = b;
    int *ptr_c = c;

    srand(time(NULL)); //init randomizer

    SetArrayRandomValue(ptr_a, a_size, 'a');
    SetArrayRandomValue(ptr_b, b_size, 'b');

    ElementwiseAbsDifference(ptr_a, ptr_b, ptr_c, 100);

    return 0;
}
