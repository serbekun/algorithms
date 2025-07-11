#include <stdio.h>
#include <stdlib.h>

float divide(float x, float y) {
    return x / y;
}

float multiply(float x, float y) {
    return x * y;
}

float calculate_power(float voltage, float current) {
    return multiply(voltage, current);
}

float calculate_energy(float power, float time) {
    return multiply(power, time);
}

float calculate_current(float power, float voltage) {
    return divide(power, voltage);
}

float calculate_voltage(float power, float current) {
    return divide(power, current);
}

void print_menu() {
    printf("Electricity Calculator\n");
    printf("1. Power calculation (P = U*I)\n");
    printf("2. Energy calculation (E = P*t)\n");
    printf("3. Current calculation (I = P/U)\n");
    printf("4. Voltage calculation (U = P/I)\n");
    printf("5. Show menu\n");
    printf("0. Exit\n");
}

int main() {
    print_menu();
    
    while (1) {
        printf("\nSelect operation (0-4): ");
        char input[10];
        fgets(input, sizeof(input), stdin);
        int choice = atoi(input);
        
        if (choice == 0) {
            printf("Exiting the program\n");
            break;
        }
        else if (choice == 1) {
            printf("Enter voltage (V): ");
            fgets(input, sizeof(input), stdin);
            float u = atof(input);
            
            printf("Enter current (A): ");
            fgets(input, sizeof(input), stdin);
            float i = atof(input);
            
            float p = calculate_power(u, i);
            printf("Power: %.2f W\n", p);
        }
        else if (choice == 2) {
            printf("Enter power (W): ");
            fgets(input, sizeof(input), stdin);
            float p = atof(input);
            
            printf("Enter time (h): ");
            fgets(input, sizeof(input), stdin);
            float t = atof(input);
            
            float e = calculate_energy(p, t);
            printf("Energy: %.2f Wh\n", e);
        }
        else if (choice == 3) {
            printf("Enter power (W): ");
            fgets(input, sizeof(input), stdin);
            float p = atof(input);
            
            printf("Enter voltage (V): ");
            fgets(input, sizeof(input), stdin);
            float u = atof(input);
            
            float i = calculate_current(p, u);
            printf("Current: %.2f A\n", i);
        }
        else if (choice == 4) {
            printf("Enter power (W): ");
            fgets(input, sizeof(input), stdin);
            float p = atof(input);
            
            printf("Enter current (A): ");
            fgets(input, sizeof(input), stdin);
            float i = atof(input);
            
            float u = calculate_voltage(p, i);
            printf("Voltage: %.2f V\n", u);
        }
        else if (choice == 5) {
            print_menu();
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}