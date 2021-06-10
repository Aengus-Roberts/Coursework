#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double function(double x) {
    return (pow(x + 1, -2) + pow(x - 1, -2) - 10);
};

double *linspace(double start, double end, int number) {
    double *list;
    list = (double *) calloc(number, sizeof(double));
    int i = 0;
    double step = (double) (end - start) / number;
    list[i] = start;
    for (i = 1; i < number; i++) {
        list[i] = list[i - 1] + step;
    }
    list[number] = end;
    return list;
};
/* Returns a list of number equally spaced values between start and finish */

int rootNumber() {
    double start = -10, end = 10;
    double *xList = linspace(start, end, 300);
    int previous;
    if (function(xList[0]) < 0) {
        previous = 0;
    } else {
        previous = 1;
    }

    int i;
    int current;
    int numberOfRoots = 0;
    for (i = 1; i < 300; i++) {
        if (function(xList[i]) < 0) {
            current = 0;
        } else {
            current = 1;
        }
        if (current != previous) {
            numberOfRoots += 1;
        }
        previous = current;
    }
    return numberOfRoots;
};
/* Uses the bisection method to approximate the number of roots */

double *approxRoots(int N) {
    double *approxRootsList;
    approxRootsList = (double *) calloc(N, sizeof(double));
    double start = -10, end = 10;
    double *xList = linspace(start, end, 600);
    int rootsFound = 0;
    int previous;
    if (function(xList[0]) < 0) {
        previous = 0;
    } else {
        previous = 1;
    }

    int i;
    int current;
    for (i = 1; i < 600; i++) {
        if (function(xList[i]) < 0) {
            current = 0;
        } else {
            current = 1;
        }
        if (current != previous) {
            approxRootsList[rootsFound] = xList[i - 1];
            rootsFound += 1;
        }
        previous = current;
    }
    return approxRootsList;
}
/* Returns a value of x close to the root */

double secant(double x1, double x2) {
    double delta = ((function(x2) * (x2 - x1)) /
                    (function(x2) - function(x1)));
    return (x2 - delta);
};
/* Returns x_(n+2) given x_(n+1) and x_n */

double getdiff(double x1, double x2) {
    if (x2 > x1) {
        return (x2 - x1);
    } else {
        return (x1 - x2);
    }
}
/* Returns the magnitude of the difference between x1 and x2 */

double findRoot(double start, double epsilonSF) {
    double x1 = start, x2 = (start + ((double) 1 / 30));
    double epsilon = pow(10, -epsilonSF);
    double temp;
    double diff = getdiff(x1, x2);
    while (diff > epsilon) {
        temp = secant(x1, x2);
        x1 = x2;
        x2 = temp;
        diff = getdiff(x1, x2);
    }
    return x2;
}
/* Iteratively uses the secant method to approximate a root
 * until a sufficient level of accuracy has been reached */

int main() {
    int epsilonSF;
    printf("Please enter a resolution for epsilon as a negated power of 10: ");
    scanf("%d", &epsilonSF);
    int check = 0;
    int N = rootNumber();
    double *approxList = approxRoots(N);
    double *roots;
    roots = (double *) calloc(N, sizeof(double));
    for (check = 0; check < N; check++) {
        roots[check] = findRoot(approxList[check], epsilonSF);
        printf("Root %d is %lf\n", check, roots[check]);
    }

};


