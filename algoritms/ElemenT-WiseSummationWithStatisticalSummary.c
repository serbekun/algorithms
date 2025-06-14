#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GetSumOfArray(float *a, float *b, float *c, float *d, float *e, float *array_with_sum, size_t size_arrays) 
{
    for (int i = 0; i < size_arrays; i++) 
    {
        *(array_with_sum + i) = *(a + i) + *(b + i) + *(c + i) + *(d + i) + *(e + i); 
    }
}

void SetArrayRandomValue(float *array, size_t array_size, char ArrayName) 
{
    for (int i = 0; i < array_size; i++) 
    {
        *(array + i) = (float)rand() / RAND_MAX * 100.0f;
    }
}

void PrintFloatArrayValue(float *array, size_t size_array, char *array_name) 
{
    for (int i = 0; i < size_array; i++)
        printf("%s|%d - %f \n", array_name, i, *(array + i));
}

float GetArrayAvarage(float *array_collect_array_avarage, size_t size_array_collect_array_avarage) 
{
    // init value
    float sum_array_collect_array_avarage = 0.0f;
    float avarage_array_collect_array_avarage;

    for (int i = 0; i < size_array_collect_array_avarage; i++) 
    {
        sum_array_collect_array_avarage += *(array_collect_array_avarage + i);
    }

    avarage_array_collect_array_avarage = sum_array_collect_array_avarage / size_array_collect_array_avarage;

    return avarage_array_collect_array_avarage;

}

int main() 
{
    // init variables
    int size_arrays = 100000;

    float a[size_arrays];
    float b[size_arrays];
    float c[size_arrays];
    float d[size_arrays];
    float e[size_arrays];

    float f[size_arrays];

    char array_name[] = "avarage"; 
    int size_array_with_avarage = 6;
    float array_with_avarage[size_array_with_avarage];

    // init randomizers
    srand(time(NULL));

    // set in array random value
    SetArrayRandomValue(a, size_arrays, 'a');
    SetArrayRandomValue(b, size_arrays, 'b');
    SetArrayRandomValue(c, size_arrays, 'c');
    SetArrayRandomValue(d, size_arrays, 'd');
    SetArrayRandomValue(e, size_arrays, 'e');

    GetSumOfArray(a, b, c, d, e, f, size_arrays);

    array_with_avarage[0] = GetArrayAvarage(a, size_arrays);
    array_with_avarage[1] = GetArrayAvarage(b, size_arrays);
    array_with_avarage[2] = GetArrayAvarage(c, size_arrays);
    array_with_avarage[3] = GetArrayAvarage(d, size_arrays);
    array_with_avarage[4] = GetArrayAvarage(e, size_arrays);
    array_with_avarage[5] = GetArrayAvarage(f, size_arrays);

    PrintFloatArrayValue(array_with_avarage, size_array_with_avarage, array_name);

    return 0;
}
