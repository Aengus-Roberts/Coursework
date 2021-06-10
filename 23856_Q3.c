#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector {
    double x;
    double y;
} vector; /* Equivalent of 2 element that holds x and y values */

vector vectorSubtract(vector a, vector b) {
    vector output;
    output.x = a.x - b.x;
    output.y = a.y - b.y;
    return output;
}; /* defines subtraction between 2 vectors */

int doubleEquals(double a, double b) {
    double epsilon = pow(10, -10);
    if (((b - epsilon) < a) && (a < (b + epsilon))) {
        return 0;
    } else {
        return 1;
    }
};

int vectorEquals(vector a, vector b) {
    if ((doubleEquals(a.x, b.x) == 0) && (doubleEquals(a.y, b.y) == 0)) {
        return 0;
    } else {
        return 1;
    }
};

double vectorMagnitude(vector a) {
    return pow((pow(a.x, 2) + pow(a.y, 2)), 0.5);
}; /* returns magnitude of vector */

typedef struct matrix {
    double m[2][2];
} matrix; /* defines a 2x2 matrix using 2d arrays */

matrix inverse(matrix m) {
    double det = ((m.m[0][0] * m.m[1][1]) - (m.m[0][1] * m.m[1][0]));
    /* printf("det is %lf\n", det); */
    matrix result;
    result.m[0][0] = m.m[1][1] / det;
    result.m[0][1] = -m.m[0][1] / det;
    result.m[1][0] = -m.m[1][0] / det;
    result.m[1][1] = m.m[0][0] / det;
    return result;
}; /* returns inverse of 2x2 matrix input */

vector MV_multiplication(matrix m, vector v) {
    vector R;
    R.x = (m.m[0][0] * v.x) + (m.m[0][1] * v.y);
    R.y = (m.m[1][0] * v.x) + (m.m[1][1] * v.y);
    return R;
}; /* multiplies 2x2 matrix by 2x1 vector */

double f1(double x, double y) {
    double original = (pow((x + 1), 2) + pow((y + 1), 2) - 25);
    return original;
}; /* First function given to solve simultaneously */

double f2(double x, double y) {
    double original = (x * y + y * y - 5);
    return original;
}; /* Second function given to solve simultaneously */

vector F(vector v) {
    vector w;
    w.x = f1(v.x, v.y);
    w.y = f2(v.x, v.y);
    return w;
}; /* returns vector (f1(x,y), f2(x,y)) */

matrix partials(vector current, vector previous) {
    matrix output;
    output.m[0][0] = (f1(current.x, current.y) - f1(previous.x, current.y)) /
                     (current.x - previous.x); /* df1/dx */
    output.m[0][1] = (f1(current.x, current.y) - f1(current.x, previous.y)) /
                     (current.y - previous.y); /* df1/dy */
    output.m[1][0] = (f2(current.x, current.y) - f2(previous.x, current.y)) /
                     (current.x - previous.x); /* df2/dx */
    output.m[1][1] = (f2(current.x, current.y) - f2(current.x, previous.y)) /
                     (current.y - previous.y); /* df2/dy */
    return output;
}; /* returns a first order approximation of the jacobian*/

vector secant(vector current, vector previous) {
    vector delta = MV_multiplication(inverse(partials(current, previous)),
                                     F(current));
    return vectorSubtract(current, delta);
}; /* returns the output of 1 iteration of the 2-variable secant method*/

vector findRoot(vector a, vector b, int epsilonSF) {
    double epsilon = pow(10, -epsilonSF);
    vector temp;
    double diff = vectorMagnitude(vectorSubtract(a, b));
    while (diff > epsilon) {
        temp = secant(a, b);
        b = a;
        a = temp;
        diff = vectorMagnitude(vectorSubtract(a, b));
    }
    return a;
}; /* Calls secant method narrowing points until iteration is smaller than set epsilon */

int main() {
    srand(time(NULL));
    int rootsFound = 0;
    vector roots[4];
    vector a, b;
    int epsilonSF;
    printf("Please enter a resolution for epsilon as a negated power of 10: ");
    scanf("%d", &epsilonSF);
    while (rootsFound < 4) { /* Tries to find roots until all 4 are found */
        a.x = rand();
        a.y = rand();
        b.x = rand();
        b.y = rand();
        int i = 0;
        int check = 0;
        vector root = findRoot(a, b, epsilonSF);
        if (root.x != NAN && root.x != INFINITY) {
            for (i = 0; i < rootsFound; i++) {
                if (vectorEquals(root, roots[i]) == 0) {
                    check++;
                }
            }
            if (check == 0) {
                roots[rootsFound] = root;
                printf("Root %d is at (%lf,%lf)\n", rootsFound + 1, roots[rootsFound].x, roots[rootsFound].y);
                rootsFound += 1;
            }

        }
    }
}; /* calls findRoot 4 times for and outputs results */

