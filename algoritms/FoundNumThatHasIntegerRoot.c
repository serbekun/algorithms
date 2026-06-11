#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A structure containing an array of square integers.
 */
typedef struct {
    size_t count;
    size_t capacity;
    int *squares;
} NumsThatHasIntegerRoot;

/**
 * @brief Returns the first how_many_num_found squares of natural numbers.
 * 
 * @param how_many_num_found How many numbers need to be found?
 * @return A pointer to the structure, or NULL on error.
 * 
 * @note The caller is required to free the memory:
 *       1. free(result->squares);
 *       2. free(result);
 */
NumsThatHasIntegerRoot* FoundNumThatHasIntegerRoot(size_t how_many_num_found)
{
    if (how_many_num_found == 0)
        return NULL;

    NumsThatHasIntegerRoot *result = malloc(sizeof(NumsThatHasIntegerRoot));
    if (!result) {
        perror("Failed to allocate NumsThatHasIntegerRoot");
        return NULL;
    }

    result->count = 0;
    result->capacity = (how_many_num_found > 64) ? how_many_num_found : 64;
    result->squares = malloc(sizeof(int) * result->capacity);
    if (!result->squares) {
        perror("Failed to allocate squares array");
        free(result);
        return NULL;
    }

    for (size_t i = 1; i <= how_many_num_found; ++i) {
        if (i > __INT_MAX__ / i) {
            break;
        }

        int square = (int)(i * i);
        result->squares[result->count++] = square;

        if (result->count >= result->capacity) {
            size_t new_capacity = result->capacity * 2;
            int *tmp = realloc(result->squares, sizeof(int) * new_capacity);
            if (!tmp) {
                perror("Failed to realloc squares array");
                free(result->squares);
                free(result);
                return NULL;
            }
            result->squares = tmp;
            result->capacity = new_capacity;
        }
    }

    return result;
}
        
int main() {

    NumsThatHasIntegerRoot *result = FoundNumThatHasIntegerRoot(128);

    for (size_t i = 0; i < result->count; i++) {
        printf("%ld: %d\n", i, result->squares[i]);
    }

    free(result->squares);
    free(result);

    return 0;
}