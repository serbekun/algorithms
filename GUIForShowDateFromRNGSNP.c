#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("use file %s\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("erro open file");
        return 1;
    }

    int table, student;
    int count = 0;

    while (fscanf(file, "table - %d, student - %d\n", &table, &student) == 2) {
        printf("[%d] ", student);
        count++;

        if (count % 6 == 0) {
            printf("\n");
        }
    }

    if (count % 6 != 0) {
        printf("\n");
    }

    fclose(file);
    return 0;
}