#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "calculator.h"

double* CreateArrayWithResult();

int InitesrMenu() 
{

    printf("1. init array for save there results");


}

char ** CreateArrayWithNoteForArrayWithResult()
{






}



double* CreateArrayWithResult(int *array_size) {
    int need_bytes_for_this;
    double *array_with_result = NULL;
    char yes_or_no;

    do {
        
        do {
        printf("type array with result size: ");
        scanf("%d", array_size);
        while (getchar() != '\n'); // clear buffer
        
        need_bytes_for_this = *array_size * sizeof(double);
        printf("need memory for create : %d bayts\n", need_bytes_for_this);
        printf("Are you satisfied with this amount of memory usage?\n");
        printf("if no type 'n' for exit and don't creaet array\n");
        printf("if no but you can change array size type 'c'\n");
        printf("if yes type 'y' and we create array with this amount of memory\n");
        printf("y/n/c :");
        yes_or_no = getchar();

        if (yes_or_no == 'n')
            return NULL;
        if (yes_or_no == 'c')
            continue;
        if (yes_or_no == 'y')
            break;
        } while (1);
        
        // allocate memory
        double *array_with_result = (double *)malloc(need_bytes_for_this);
        if (!array_with_result) {
            printf("error allocate memory try with more liitle size.\n");
        }
    } while (!array_with_result);

    return array_with_result;
}