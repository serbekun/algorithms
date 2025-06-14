#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void RandomNumZeroOne(float array[][100], size_t array_address_num ,size_t array_size) 
{

    for (int i = 0; i < array_size; i++) 
    {
        array[array_address_num][i] = (float)rand() / (float)RAND_MAX;
    }

}

void ClearArrayValue(float array[][100], size_t array_address_num, size_t array_size) 
{

    for (int i = 0; i < array_size; i++) 
    {
        array[array_address_num][i] = 0;
    }

}

float GetArrayAvarage(float array_collect_array_avarage[][100],
    size_t size_array_collect_array_avarage, size_t array_address_num) 
{

    float sum_array_collect_array_avarage = 0;
    float avarage;

    for (int i = 0; i < size_array_collect_array_avarage; i++)
    {
        sum_array_collect_array_avarage += array_collect_array_avarage[array_address_num][i];
    }

    avarage = sum_array_collect_array_avarage / 100;

    return avarage;

}

void PrintFloatArrayValue(float array[][100], size_t size_array, char *array_name) 
{
    for (int i = 0; i < size_array; i++)
        printf("%s|%d - %f \n", array_name, i, array[1][i]);
}

int main() 
{

    size_t size_first_array = 2;
    size_t size_second_array = 100;
    float array[size_first_array][size_second_array];
    char name_avarage[] = "avarage";
    float all_avarage;

    for (int i = 0;i < 100; i++) 
    {
        ClearArrayValue(array, 0, size_second_array);
        RandomNumZeroOne(array, 0, size_second_array);

        array[1][i] = GetArrayAvarage(array, size_second_array, 0);

    }

    all_avarage = GetArrayAvarage(array, size_second_array, 1);

    PrintFloatArrayValue(array, size_second_array, name_avarage);

    printf("all avarage = %f\n", all_avarage);
}