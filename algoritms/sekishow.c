#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 6
#define PLACES_SIZE 25
#define FILENAME "new_sit_place.txt"

/* funk for show result */
int ShowResult() {

    // open file
    FILE *file = fopen(FILENAME, "r");
    if (!file) { // if error open file return
        perror("error open file from argv[1]");
        return 1;
    }

    // init value
    int row, col, student;
    char gender;
    int count = 0;

    // read file and print
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

    // clease file return 0
    fclose(file);
    return 0;
}

struct student {
    int id;
    int sex; // 0 - boy, 1 - girl
};

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

int get_required_sex(int row, int col) {
    if (row % 2 == 0)
        return (col % 2 == 0) ? 0 : 1;
    else
        return (col % 2 == 0) ? 1 : 0;
}

void SetPlaces(struct student **students, int *places, int size, int cols) {
    int rows = (size + cols - 1) / cols;
    int *boys = malloc(size * sizeof(int));
    int *girls = malloc(size * sizeof(int));
    int boy_count = 0, girl_count = 0;

    for (int i = 0; i < size; i++) {
        if (students[i]->sex == 0)
            boys[boy_count++] = students[i]->id;
        else
            girls[girl_count++] = students[i]->id;
    }

    shuffle(boys, boy_count);
    shuffle(girls, girl_count);

    int boy_idx = 0, girl_idx = 0;
    for (int i = 0; i < size; i++) places[i] = 0;

    for (int row = 0; row < rows; row++) {
        int row_cols = (row < rows - 1) ? cols : size - (rows - 1) * cols;
        for (int col = 0; col < row_cols; col++) {
            int idx = row * cols + col;
            int sex = get_required_sex(row, col);
            if (sex == 0 && boy_idx < boy_count) {
                places[idx] = boys[boy_idx++];
            } else if (sex == 1 && girl_idx < girl_count) {
                places[idx] = girls[girl_idx++];
            } else if (boy_idx < boy_count) {
                places[idx] = boys[boy_idx++];
            } else if (girl_idx < girl_count) {
                places[idx] = girls[girl_idx++];
            }
        }
    }

    free(boys);
    free(girls);
}

int main() {
    srand(time(NULL));
    int *places = malloc(PLACES_SIZE * sizeof(int));

    struct student s[PLACES_SIZE] = {
        {1,1}, {2,1}, {3,1}, {4,1}, {5,0}, {6,0}, {7,1}, {8,0}, {9,0}, {10,0},
        {11,0}, {12,0}, {13,1}, {14,1}, {15,1}, {16,0}, {17,0}, {18,0}, {19,0}, {20,0},
        {21,1}, {22,1}, {23,0}, {24,1}, {25,1}
    };

    struct student *ptrs[PLACES_SIZE];
    for (int i = 0; i < PLACES_SIZE; i++) {
        ptrs[i] = &s[i];
    }

    SetPlaces(ptrs, places, PLACES_SIZE, COLS);

    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Can't open file");
        return 1;
    }

    for (int i = 0; i < PLACES_SIZE; i++) {
        int row = i / COLS;
        int col = i % COLS;
        fprintf(file, "Row %d, Col %d: Student %d (%s)\n",
            row + 1, col + 1, places[i],
            (ptrs[places[i] - 1]->sex == 0) ? "M" : "F");
    }
    fclose(file);
    
    printf("Done. See '%s'\n", FILENAME);
    free(places);
    ShowResult();
    return 0;
}
