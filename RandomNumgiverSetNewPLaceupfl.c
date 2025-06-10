#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS 5
#define PLACES_SIZE 26

struct student {
    int id;
    int sex; // 0 - boy, 1 - girl
};

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int get_required_sex(int row, int col) {
    if (row % 2 == 0) {
        return (col % 2 == 0) ? 1 : 0;
    } else {
        return (col % 2 == 0) ? 0 : 1; 
    }
}


void SetPlaces(struct student **students, int *places, int size, int cols) {
    int rows = (size + cols - 1) / cols;
    int total_pairs = 0;
    int max_pairs = 100;
    int(*pairs)[2] = malloc(max_pairs * sizeof(int[2]));

    for (int row = 0; row < rows; row++) {
        int row_cols = (row < rows - 1) ? cols : size - (rows - 1) * cols;
        for (int col = 0; col < row_cols; col++) {
            int idx1 = row * cols + col;
            if (col < row_cols - 1) {
                int idx2 = row * cols + col + 1;
                pairs[total_pairs][0] = idx1;
                pairs[total_pairs][1] = idx2;
                total_pairs++;
            }
            if (row < rows - 1) {
                int next_row_cols = (row + 1 == rows - 1) ? size - (rows - 1) * cols : cols;
                if (col < next_row_cols) {
                    int idx2 = (row + 1) * cols + col;
                    pairs[total_pairs][0] = idx1;
                    pairs[total_pairs][1] = idx2;
                    total_pairs++;
                }
            }
        }
    }

    struct student *special_boy = NULL;
    struct student *special_girl = NULL;
    int *boys = malloc(size * sizeof(int));
    int *girls = malloc(size * sizeof(int));
    int boy_count = 0, girl_count = 0;

    for (int i = 0; i < size; i++) {
        if (students[i]->id == 22) {
            special_girl = students[i];
        } else if (students[i]->id == 23) {
            special_boy = students[i];
        } else {
            if (students[i]->sex == 0) {
                boys[boy_count++] = students[i]->id;
            } else {
                girls[girl_count++] = students[i]->id;
            }
        }
    }

    shuffle(boys, boy_count);
    shuffle(girls, girl_count);

    for (int i = 0; i < size; i++) {
        places[i] = 0;
    }

    if (total_pairs > 0) {
        int pair_index = rand() % total_pairs;
        int pos1 = pairs[pair_index][0];
        int pos2 = pairs[pair_index][1];
        int row1 = pos1 / cols;
        int col1 = pos1 % cols;
        int row2 = pos2 / cols;
        int col2 = pos2 % cols;
        int sex1 = get_required_sex(row1, col1);
        int sex2 = get_required_sex(row2, col2);

        if (sex1 == 0 && sex2 == 1) {
            places[pos1] = special_boy->id;
            places[pos2] = special_girl->id;
        } else if (sex1 == 1 && sex2 == 0) {
            places[pos1] = special_girl->id;
            places[pos2] = special_boy->id;
        } else {
            places[pos1] = special_boy->id;
            places[pos2] = special_girl->id;
        }
    }

    int boy_idx = 0, girl_idx = 0;
    for (int row = 0; row < rows; row++) {
        int row_cols = (row < rows - 1) ? cols : size - (rows - 1) * cols;
        for (int col = 0; col < row_cols; col++) {
            int idx = row * cols + col;
            if (places[idx] != 0) continue;
            
            int required_sex = get_required_sex(row, col);
            if (required_sex == 0) {
                if (boy_idx < boy_count) {
                    places[idx] = boys[boy_idx++];
                } else if (girl_idx < girl_count) {
                    places[idx] = girls[girl_idx++];
                }
            } else {
                if (girl_idx < girl_count) {
                    places[idx] = girls[girl_idx++];
                } else if (boy_idx < boy_count) {
                    places[idx] = boys[boy_idx++];
                }
            }
        }
    }

    free(pairs);
    free(boys);
    free(girls);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int *places = malloc(PLACES_SIZE * sizeof(int));
    if (!places) {
        perror("Error allocating memory for places");
        return 2;
    }

    // init student
    struct student s1 = {1, 0};
    struct student s2 = {2, 1};
    struct student s3 = {3, 1};
    struct student s4 = {4, 1};
    struct student s5 = {5, 1};
    struct student s6 = {6, 1};
    struct student s7 = {7, 1};
    struct student s8 = {8, 1};
    struct student s9 = {9, 1};
    struct student s10 = {10, 1};
    struct student s11 = {11, 1};
    struct student s12 = {12, 1};
    struct student s13 = {13, 0};
    struct student s14 = {14, 0};
    struct student s15 = {15, 0};
    struct student s16 = {16, 0};
    struct student s17 = {17, 0};
    struct student s18 = {18, 0};
    struct student s19 = {19, 0};
    struct student s20 = {20, 0};
    struct student s21 = {21, 0};
    struct student s22 = {22, 1};
    struct student s23 = {23, 0};
    struct student s24 = {24, 0};
    struct student s25 = {25, 0};
    struct student s26 = {26, 0};

    struct student *persons_array[PLACES_SIZE] = {
        &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10,
        &s11, &s12, &s13, &s14, &s15, &s16, &s17, &s18, &s19, &s20,
        &s21, &s22, &s23, &s24, &s25, &s26
    };

    SetPlaces(persons_array, places, PLACES_SIZE, COLS);

    FILE *file = fopen(argv[1], "w");
    if (!file) {
        perror("Error opening file");
        printf("Outputting to terminal:\n");
        for (int i = 0; i < PLACES_SIZE; i++) {
            int row = i / COLS;
            int col = i % COLS;
            printf("Row %d, Col %d: Student %d (%s)\n", 
                   row + 1, col + 1, places[i],
                   (persons_array[places[i]-1]->sex == 0) ? "M" : "F");
        }
        free(places);
        return 1;
    }

    for (int i = 0; i < PLACES_SIZE; i++) {
        int row = i / COLS;
        int col = i % COLS;
        fprintf(file, "Row %d, Col %d: Student %d (%s)\n", 
                row + 1, col + 1, places[i],
                (persons_array[places[i]-1]->sex == 0) ? "M" : "F");
    }

    printf("Successfully wrote data to file '%s'\n", argv[1]);
    fclose(file);
    free(places);
    return 0;
}