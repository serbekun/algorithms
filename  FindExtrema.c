#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double x;
    double y;
} Point;

Point* ReadFile(const char *filename, size_t *outSize) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("error open file");
        return NULL;
    }

    size_t capacity = 10;
    size_t size = 0;
    Point *points = malloc(capacity * sizeof(Point));
    if (!points) {
        perror("error allocate memory");
        fclose(file);
        return NULL;
    }

    while (!feof(file)) {
        if (size >= capacity) {
            capacity *= 2;
            Point *tmp = realloc(points, capacity * sizeof(Point));
            if (!tmp) {
                perror("error allocate memory");
                free(points);
                fclose(file);
                return NULL;
            }
            points = tmp;
        }

        if (fscanf(file, "%lf %lf", &points[size].x, &points[size].y) == 2) {
            size++;
        } else {
            break;
        }
    }

    fclose(file);
    *outSize = size;
    return points;
}

void SavePoints(const char *filename, Point *points, size_t size) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("error write to file");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        fprintf(f, "%e %e\n", points[i].x, points[i].y);
    }

    fclose(f);
}

void FindAndSaveExtrema(Point *points, size_t size) {
    Point *mins = malloc(size * sizeof(Point));
    Point *maxs = malloc(size * sizeof(Point));
    size_t min_count = 0, max_count = 0;

    for (size_t i = 1; i < size - 1; i++) {
        if (points[i - 1].y > points[i].y && points[i + 1].y > points[i].y) {
            mins[min_count++] = points[i];
        } else if (points[i - 1].y < points[i].y && points[i + 1].y < points[i].y) {
            maxs[max_count++] = points[i];
        }
    }

    SavePoints("data_min.dat", mins, min_count);
    SavePoints("data_max.dat", maxs, max_count);

    free(mins);
    free(maxs);
}

int main() {
    char filename[256];
    printf("enter file name: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    size_t size = 0;
    Point *points = ReadFile(filename, &size);
    if (!points) return 1;

    SavePoints("data_all.dat", points, size);
    FindAndSaveExtrema(points, size);

    printf("date save: data_all.dat, data_min.dat, data_max.dat\n");

    free(points);
    return 0;
}
