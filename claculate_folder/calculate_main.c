#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "calculator.h"
#include "initers.h"

int main() {

    // init value
    int array_with_result_note_size;
    int array_with_result_size;
    const size_t input_size = 40;
    char input[input_size];
    unsigned char input_num;

    printf("welcome to another math calcilation\n");

    while(1) 
    {

        printf("1. initers\n");
        printf("2. calculator\n");
        printf("type 'exit' for exit\n");

        fgets(input, input_size, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (!strcmp(input, "exit"))
            return 0;
        else {
            input_num = atoi(input);
            if (input_num == 1)
                calculator_main();
        }
    }
}