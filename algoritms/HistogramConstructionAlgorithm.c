#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void DecomposerValue(float *array, int *table
    , size_t array_size, size_t size_table) 
{

    int numbox;

for (int i = 0; i < array_size; i++)
{
    numbox = *(array + i) / 0.01;
    numbox--;
    
    if (numbox < 0)
        numbox = 0;

    if (numbox >= (int)size_table)
        numbox = (int)size_table - 1;

    (*(table + numbox))++;
}

}

void RandomNumZeroOne(float *array, size_t array_size) 
{

    for (int i = 0; i < array_size; i++) 
    {
        *(array + i) = (float)rand() / (float)RAND_MAX;
    }

}

void PrintIntArrayValue(int *array, size_t size_array, char *array_name) 
{

    for (int i = 0;i < size_array;i++)
        printf("%s|%d - %d \n", array_name, i, *(array + i));

}

int main() {

    // init variables
    size_t array_size = 100000;
    size_t size_table = 100;
    float array[array_size];
    int table[size_table];
    char name[] = "table";

    for (size_t i = 0; i < size_table; i++) 
        table[i] = 0;

    // init randomizer
    srand(time(NULL));
    
    RandomNumZeroOne(array, array_size);

    DecomposerValue(array, table, array_size, size_table);

    PrintIntArrayValue(table, size_table, name);

    return 0;
}