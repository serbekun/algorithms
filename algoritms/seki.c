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

/* student struct */
struct student {
    int id; // num in class
    int sex; // 0 - boy, 1 - girl
    int eyes; // 0 - good, 1 - bad; 
};

/* funk for shuffle and get more random */
void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/* funk for get what place for what sex */
int get_required_sex(int row, int col) {
    if (row % 2 == 0) {
        return (col % 2 == 0) ? 0 : 1;
    } else {
        return (col % 2 == 0) ? 1 : 0; 
    }
}

/* funk for set new sit place */
void SetPlaces(struct student **students, int *places, int size, int cols) {
    
    // inti values
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

    // inti values
    struct student *special_boy = NULL;
    struct student *special_girl = NULL;
    int *boys = malloc(size * sizeof(int));
    int *girls = malloc(size * sizeof(int));
    int boy_count = 0, girl_count = 0;

    // init special id
    int special_id1 = 23;
    int special_id2 = 22;

    for (int i = 0; i < size; i++) {
        if (students[i]->id == special_id2) {
            special_girl = students[i];
        } else if (students[i]->id == special_id1) {
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

/* main */
int main(int argc, char *argv[]) {

    srand(time(NULL));

    int *places = malloc(PLACES_SIZE * sizeof(int));
    if (!places) {
        perror("Error allocating memory for places");
        return 2;
    }

    // init student
    struct student s1 = {1, 1};
    struct student s2 = {2, 1};
    struct student s3 = {3, 1};
    struct student s4 = {4, 1};
    struct student s5 = {5, 0};
    struct student s6 = {6, 0};
    struct student s7 = {7, 1};
    struct student s8 = {8, 0};
    struct student s9 = {9, 0};
    struct student s10 = {10, 0};
    struct student s11 = {11, 0};
    struct student s12 = {12, 0};
    struct student s13 = {13, 1};
    struct student s14 = {14, 1};
    struct student s15 = {15, 1};
    struct student s16 = {16, 0};
    struct student s17 = {17, 0};
    struct student s18 = {18, 0};
    struct student s19 = {19, 0};
    struct student s20 = {20, 0};
    struct student s21 = {21, 1};
    struct student s22 = {22, 1};
    struct student s23 = {23, 0};
    struct student s24 = {24, 1};
    struct student s25 = {25, 1};

    struct student *persons_array[PLACES_SIZE] = {
        &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10,
        &s11, &s12, &s13, &s14, &s15, &s16, &s17, &s18, &s19, &s20,
        &s21, &s22, &s23, &s24, &s25
    };

    SetPlaces(persons_array, places, PLACES_SIZE, COLS);

    FILE *file = fopen(FILENAME, "w");
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

    fclose(file);
    printf("Successfully wrote data to file '%s'\n", FILENAME);
    ShowResult();
    free(places);
    return 0;
}