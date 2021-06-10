#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Q1a.c"

double *linspace(double start, double end, int number) {
    double *list;
    int i = 0;
    double step = (double) (end - start) / number;
    list = (double *) calloc(number, sizeof(double));

    list[i] = start;
    for (i = 1; i < number; i++) {
        list[i] = list[i - 1] + step;
    }
    list[number] = end;
    return list;
}

int main() {
    int i;
    double a = -25, b = 25, y;
    double *x_array = linspace(a, b, 100);
    FILE *fp1 = fopen("diffPattern.csv", "w");
    fprintf(fp1, "x,y\n");
    for (i = 0; i < 101; i++) {
        if (x_array[i] == 0){
            y = 1;
        }
        else {
            y = (pow(2 * J(1, x_array[i]) / x_array[i], 2));
        }
        fprintf(fp1, "%f,%f\n", x_array[i], y);
    }
    fclose(fp1);
    return 0;
}



