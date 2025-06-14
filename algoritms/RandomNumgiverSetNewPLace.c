#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* exit code. 0) sucsesful 1) error write to the file 2) error alocate memory\n" */

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  // random index
        int temp = array[i];  
        array[i] = array[j];
        array[j] = temp;
    }
}

void SetPLasec(int *places, const int PLACES_SIZE)
{

    for (int i = 0; i < PLACES_SIZE; i++) {
        places[i] = i + 1;
    }

    // shuffel array
    shuffle(places, PLACES_SIZE);
}

int main(int argc, char *argv[]) {

    srand(time(NULL));    
    
    if (argc < 2) {
        printf("type number.\n");
        return 1;
    }

    const int PLACES_SIZE = atoi(argv[1]);

    int *places = (int *)malloc(PLACES_SIZE * sizeof(int));
    if (!places) {
        perror ("error alocate memory exiting\n");
        return 2;
    }

    SetPLasec(places, PLACES_SIZE);

    FILE *file = fopen(argv[2], "w");
    if (!file) {
        perror("error open file from argv[2]\n");
        printf("because error open file put date to terminal\n");
        for (int i = 0; i < PLACES_SIZE; i++)
        {
            printf("table - %d, student - %d\n", i + 1, places[i]);
        }
        free(places);
        return 1;
    } 

    for (int i = 0; i < PLACES_SIZE; i++)
    {
        fprintf(file, "table - %d, student - %d\n", i + 1, places[i]);
    }
    printf("succsesfull write date to file '%s'\n", argv[2]);

    fclose(file);
    free(places);

    printf("end");

    return 0;
}