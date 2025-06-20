#pragma once 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void plus_oper();

int calculator_main() {

    const size_t input_size = 40;
    char input[input_size];
    unsigned char input_num;

    while(1) 
    {
        
        printf("1. plus operation");
        printf("type 'exit' for exit\n");

        fgets(input, input_size, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (!strcmp(input, "exit"))
            return;
        else {
            input_num = atoi(input);
            if (input_num == 1)
            plus_oper();
        }
    }
}

void plus_oper()
{

    // inti values
    int num1;
    int num2;
    int res;
    
    // get input
    printf("type first number for plus : ");
    scanf(%d, &num1);
    while (getchar() != '\n') // clear buffer
    printf("type second number for plus : ");
    scanf(%d, &num2);
    while (getchar() != '\n') // clear buffer

    // calculate res
    res = num1 + num2;
    
    // print res
    printf("result = %d", res);

    // TODO 
    /*
    create here code fro save result in array_with_result      
    */
    
}
