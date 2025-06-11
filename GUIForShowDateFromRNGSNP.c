#include <stdio.h>
#include <stdlib.h>

#define COLS 6

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("use: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("error open file from argv[1]");
        return 1;
    }

    int row, col, student;
    char gender;
    int count = 0;

    while (fscanf(file, "Row %d, Col %d: Student %d (%c)\n", &row, &col, &student, &gender) == 4) {
        printf("[%d (%c)] ", student, gender);
        count++;

        if (count % COLS == 0) {
            printf("\n");
        }
    }

    if (count % COLS != 0) {
        printf("\n");
    }

    fclose(file);
    return 0;
}
