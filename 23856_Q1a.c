#include <stdio.h>
#include <math.h>


double function(int m, double x, double theta) {
    return cos(m * theta - (x * sin(theta)));
}

double J(int m, double x) {
    int N = 10000;
    float h = (float) 1 / (float) (N - 1);
    float a = 0;
    double b = M_PI;
    double total = 0.5 * (function(m, x, a) + function(m, x, b));
    float xi = h;
    while (xi < b) {
        total += function(m, x, xi);
        xi += h;
    }
    return (total * h) / M_PI;

}

int main() {
    int i;
    FILE *fp = fopen("bessel.csv", "w");
    fprintf(fp, "J0,J1,J2\n");
    for (i = 0; i < 21; i++) {
        fprintf(fp, "%f,%f,%f,\n", J(0, i), J(1, i), J(2, i));

    }
    fclose(fp);
}
