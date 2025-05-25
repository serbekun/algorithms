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

int GetArrayAvarage(int *array_collect_array_avarage,
    size_t size_array_collect_array_avarage) 
{

    // init value
    int sum_array_collect_array_avarage = 0;
    int avarage_array_collect_array_avarage;

    for (int i = 0;i < size_array_collect_array_avarage;i++) 
    {
        sum_array_collect_array_avarage += *(array_collect_array_avarage + i);
    }

    avarage_array_collect_array_avarage = sum_array_collect_array_avarage / size_array_collect_array_avarage;

    return avarage_array_collect_array_avarage;

}

void PrintIntArrayValue(int *array, size_t size_array, char *array_name) 
{

    for (int i = 0;i < size_array;i++)
        printf("%s|%d - %d \n", array_name, i, *(array + i));

}

int main()
{

    // init variables
    int size_array_with_random_num = 10;

    int a[size_array_with_random_num];
    int b[size_array_with_random_num];
    int c[size_array_with_random_num];
    int d[size_array_with_random_num];
    int e[size_array_with_random_num];

    int size_array_with_arrays_avarage = 5;
    char array_name[] = "f"; 
    int f[size_array_with_arrays_avarage];

    int array_f_avarage;

    // init randomizer
    srand(time(NULL));

    // set in array random value
    SetArrayRandomValue(a, size_array_with_random_num, 'a');
    SetArrayRandomValue(b, size_array_with_random_num, 'b');
    SetArrayRandomValue(c, size_array_with_random_num, 'c');
    SetArrayRandomValue(d, size_array_with_random_num, 'd');
    SetArrayRandomValue(e, size_array_with_random_num, 'e');

    // get array avarage
    f[0] = GetArrayAvarage(a, size_array_with_random_num);
    f[1] = GetArrayAvarage(b, size_array_with_random_num);
    f[2] = GetArrayAvarage(c, size_array_with_random_num);
    f[3] = GetArrayAvarage(d, size_array_with_random_num);
    f[4] = GetArrayAvarage(e, size_array_with_random_num);

    PrintIntArrayValue(f, size_array_with_arrays_avarage, array_name);

    array_f_avarage = GetArrayAvarage(f, size_array_with_arrays_avarage);
    printf("all avarage = %d", array_f_avarage);

    return 0;
}