#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* exit code. 0) sucsesful 1) error write to the file 2) error alocate memory\n" */

// studetn stuct
struct student {
    int id; // num on the class
    int sex; // 0 - boy, 1 - girl
};

/* funk for shufle places for more random   */
void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/* main algoritms to set new place */
void SetPLasec(int *places, const int PLACES_SIZE, int cols)
{

    int *students = malloc(PLACES_SIZE * sizeof(int));
    for (int i = 0; i < PLACES_SIZE; i++) {
        students[i] = i + 1;
    }

    int *rest = malloc((PLACES_SIZE - 2) * sizeof(int));
    int idx = 0;
    for (int i = 0; i < PLACES_SIZE; i++) {
        if (students[i] != 1 && students[i] != 2) {
            rest[idx++] = students[i];
        }
    }
    shuffle(rest, PLACES_SIZE - 2);

    for (int i = 0; i < PLACES_SIZE; i++) {
        places[i] = 0;
    }

    int row = rand() % (PLACES_SIZE / cols - 1);
    int col = rand() % (cols - 1);

    int pos1 = row * cols + col;
    int pos2;

    if (rand() % 2) {
        pos2 = pos1 + 1;
    } else {
        pos2 = pos1 + cols;
    }

    places[pos1] = 23; // i
    places[pos2] = 22; // she

    idx = 0;
    for (int i = 0; i < PLACES_SIZE; i++) {
        if (places[i] == 0) {
            places[i] = rest[idx++];
        }
    }

    free(students);
    free(rest);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc < 3) {
        printf("Usage: %s <number_of_places> <output_file>\n", argv[0]);
        return 1;
    }

    const int PLACES_SIZE = atoi(argv[1]);

    int *places = (int *)malloc(PLACES_SIZE * sizeof(int));
    if (!places) {
        perror("Error allocating memory for places");
        return 2;
    }

    SetPlaces(places, PLACES_SIZE, 6);

    FILE *file = fopen(argv[2], "w");
    if (!file) {
        perror("Error opening file");
        printf("Since the file couldn't be opened, outputting data to terminal:\n");

        for (int i = 0; i < PLACES_SIZE; i++) {
            printf("Table - %d, Student - %d\n", i + 1, places[i]);
        }

        free(places);
        return 1;
    }

    for (int i = 0; i < PLACES_SIZE; i++) {
        fprintf(file, "Table - %d, Student - %d\n", i + 1, places[i]);
    }

    printf("Successfully wrote data to file '%s'\n", argv[2]);

    fclose(file);
    free(places);

    printf("End\n");

    return 0;
}