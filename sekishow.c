#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLS        6
#define PLACES_SIZE 25
#define FILENAME    "new_sit_place.txt"

typedef struct {
    int id;
    int sex;  // 0=boy, 1=girl
    int eyes; // 0=good, 1=bad
} student;

int ShowResult() {
    FILE *f = fopen(FILENAME, "r");
    if (!f) { perror("Error opening file"); return 1; }

    int row, col, student;
    char gender;
    int count = 0;
    while (fscanf(f, "Row %d, Col %d: Student %d (%c)\n",
                  &row, &col, &student, &gender) == 4) {
        printf("[%d (%c)] ", student, gender);
        if (++count % COLS == 0) printf("\n");
    }
    if (count % COLS) printf("\n");
    fclose(f);
    return 0;
}

void shuffle(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

int get_required_sex(int row, int col) {
    return (row % 2 == 0) ? (col % 2 == 0 ? 0 : 1) : (col % 2 == 0 ? 1 : 0);
}

void SetPlaces(student **students, int *places, int size, int cols) {
    int rows = (size + cols - 1) / cols;

    int bad_boys[size], bad_girls[size], good_boys[size], good_girls[size];
    int bb=0, bg=0, gb=0, gg=0;

    for (int i = 0; i < size; i++) {
        student *s = students[i];
        if (s->eyes == 1) {
            (s->sex == 0) ? (bad_boys[bb++] = s->id) : (bad_girls[bg++] = s->id);
        } else {
            (s->sex == 0) ? (good_boys[gb++] = s->id) : (good_girls[gg++] = s->id);
        }
    }

    shuffle(bad_boys, bb);
    shuffle(bad_girls, bg);
    shuffle(good_boys, gb);
    shuffle(good_girls, gg);

    for (int i = 0; i < size; i++) places[i] = 0;

    int ibb=0, ibg=0, igb=0, igg=0;

    for (int r = 0; r < rows; r++) {
        int row_cols = (r < rows - 1) ? cols : size - (rows - 1) * cols;
        for (int c = 0; c < row_cols; c++) {
            int idx = r * cols + c;
            if (places[idx] != 0) continue;

            int need = get_required_sex(r, c);
            if (need == 0) {
                places[idx] = (ibb < bb) ? bad_boys[ibb++] :
                              (igb < gb) ? good_boys[igb++] :
                              (ibg < bg) ? bad_girls[ibg++] :
                                           good_girls[igg++];
            } else {
                places[idx] = (ibg < bg) ? bad_girls[ibg++] :
                              (igg < gg) ? good_girls[igg++] :
                              (ibb < bb) ? bad_boys[ibb++] :
                                           good_boys[igb++];
            }
        }
    }
}

int main() {
    srand((unsigned)time(NULL));

    student s1 = {1, 1, 1};
    student s2 = {2, 1, 1};
    student s3 = {3, 1, 1};
    student s4 = {4, 0, 1};
    student s5 = {5, 0, 1};
    student s6 = {6, 0, 0};
    student s7 = {7, 1, 0};
    student s8 = {8, 0, 0};
    student s9 = {9, 0, 0};
    student s10 = {10, 0, 0};
    student s11 = {11, 0, 0};
    student s12 = {12, 0, 0};
    student s13 = {13, 1, 0};
    student s14 = {14, 1, 0};
    student s15 = {15, 1, 0};
    student s16 = {16, 0, 0};
    student s17 = {17, 0, 0};
    student s18 = {18, 0, 0};
    student s19 = {19, 0, 0};
    student s20 = {20, 0, 0};
    student s21 = {21, 1, 0};
    student s22 = {22, 1, 0};
    student s23 = {23, 0, 0};
    student s24 = {24, 1, 0};
    student s25 = {25, 1, 0};

    student *persons[PLACES_SIZE] = {
        &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8, &s9, &s10,
        &s11, &s12, &s13, &s14, &s15, &s16, &s17, &s18, &s19, &s20,
        &s21, &s22, &s23, &s24, &s25
    };

    int *places = malloc(PLACES_SIZE * sizeof(int));
    if (!places) { perror("malloc"); return 1; }

    SetPlaces(persons, places, PLACES_SIZE, COLS);

    FILE *f = fopen(FILENAME, "w");
    if (!f) { perror("fopen"); free(places); return 1; }

    for (int i = 0; i < PLACES_SIZE; i++) {
        int r = i / COLS, c = i % COLS;
        int id = places[i];
        char *g = (persons[id-1]->sex == 0) ? "M" : "F";
        fprintf(f, "Row %d, Col %d: Student %d (%s)\n", r+1, c+1, id, g);
    }
    fclose(f);

    ShowResult();
    free(places);
    return 0;
}
