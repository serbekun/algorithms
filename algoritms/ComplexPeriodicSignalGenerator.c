#include <stdio.h>
#include <string.h>
#include <math.h>

#define IHUHA 10000
#define IHUHA_PLUS_1 (IHUHA + 1)  
#define FILE_NAME_SIZE 256
#define DEFAULT_FILE_NAME "ComplexPeriodicSignalGenerator.dat"

int WriteToFile(double *xx, double *fu, const char *filename) 
{

    FILE *fp = fopen(filename, "w");
    if (fp) {
        for (int i = 1; i <= IHUHA; i++) {
            fprintf(fp, "%.10f %.10f\n", xx[i], fu[i]);
        }
        fclose(fp);
    } else {
        perror("Error open file");
        return 1;
    }


}

/**
* Generates a periodic signal from the sum of sines.
*
* @param xx Array for storing x values ​​(time or argument).
* @param fu Array for storing function (signal) values.
* @param size Size of xx and fu arrays.
* @param st Sampling step.
* @param per1 Period of the first sinusoid.
* @param per2 Period of the second sinusoid.
* @param per3 Period of the third sinusoid.
* @param per4 Period of the fourth sinusoid.
* @param a2 Amplitude of the third sinusoid (with minus).
* @param a4 Amplitude of the fourth sinusoid.
*/
void ComplexPeriodicSignalGenerator(
    double *xx, 
    double *fu, 
    int size, 
    double st, 
    double per1, 
    double per2, 
    double per3, 
    double per4, 
    double a2, 
    double a4
) 
{
    for (int i = 0; i < size; i++) {
        double x = i * st;
        xx[i] = x;
        fu[i] = sin(per1 * x) 
               + sin(per2 * x) 
               - a2 * sin(per3 * x) 
               + a4 * sin(per4 * x);
    }
}

int main(int argc, char *argv[]) 
{

    char filename[FILE_NAME_SIZE];

    if (argc > 1) {
        strcpy(filename, argv[1]);
    } else {
        strcpy(filename, DEFAULT_FILE_NAME);
    }

    const double per1 = 60.4;
    const double per2 = 18.1;
    const double per3 = 32.05;
    const double per4 = 91.0;
    
    const double a2 = 3.0;
    const double a4 = 1.0;
    
    double xx[IHUHA+1];
    double fu[IHUHA+1];
    const double st = 1.0 / IHUHA;

    ComplexPeriodicSignalGenerator(xx, fu, IHUHA_PLUS_1, st, per1, per2, per3, per4, a2, a4);

    WriteToFile(xx, fu, filename);

    return 0;
}