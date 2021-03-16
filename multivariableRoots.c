#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct vector {
    double x;
    double y;
} vector; /* Equivalent of 2 element that holds x and y values */

vector vectorSubtract(vector a, vector b){
    vector output;
    output.x = a.x-b.x;
    output.y = a.y-b.y;
    return output;
}; /* defines subtraction between 2 vectors */

double vectorMagnitude(vector a){
    return pow((pow(a.x,2)+pow(a.y,2)),0.5);
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

double f1(double x, double y, const vector roots[], int rootsFound) {
    double original = (pow((x + 1), 2) + pow((y + 1), 2) - 25);
    int i;
    for (i = 0; i < rootsFound; i++) {
        original /= (x - roots[i].x);
        original /= (y - roots[i].y);
    }
    return original;
}; /* First function given to solve simultaneously */

double f2(double x, double y, const vector roots[], int rootsFound) {
    double original = (x*y + y*y - 5);
    int i;
    for (i = 0; i < rootsFound; i++) {
        original /= (x - roots[i].x);
        original /= (y - roots[i].y);
    }
    return original;
}; /* Second function given to solve simultaneously */

vector F(vector v, const vector roots[], int rootsFound) {
    vector w;
    w.x = f1(v.x, v.y, roots, rootsFound);
    w.y = f2(v.x, v.y, roots, rootsFound);
    return w;
}; /* returns vector (f1(x,y), f2(x,y)) */

matrix partials(vector current, vector previous, const vector roots[], int rootsFound) {
    matrix output;
    output.m[0][0] = (f1(current.x, current.y, roots, rootsFound) - f1(previous.x, current.y, roots, rootsFound)) /
                     (current.x - previous.x); /* df1/dx */
    output.m[0][1] = (f1(current.x, current.y, roots, rootsFound) - f1(current.x, previous.y, roots, rootsFound)) /
                     (current.y - previous.y); /* df1/dy */
    output.m[1][0] = (f2(current.x, current.y, roots, rootsFound) - f2(previous.x, current.y, roots, rootsFound)) /
                     (current.x - previous.x); /* df2/dx */
    output.m[1][1] = (f2(current.x, current.y, roots, rootsFound) - f2(current.x, previous.y, roots, rootsFound)) /
                     (current.y - previous.y); /* df2/dy */
    return output;
}; /* returns a first order approximation of the jacobian*/

vector secant(vector current, vector previous, const vector roots[], int rootsFound) {
    vector delta = MV_multiplication(inverse(partials(current, previous, roots, rootsFound)), F(current, roots, rootsFound));
    return vectorSubtract(current, delta);
}; /* returns the output of 1 iteration of the 2-variable secant method*/

vector findRoot(vector a, vector b, const vector roots[], int rootsFound){
    double epsilon = pow(10, -15);
    vector temp;
    double diff = vectorMagnitude(vectorSubtract(a,b));
    while (diff > epsilon){
        temp = secant(a,b,roots,rootsFound);
        b = a;
        a = temp;
        diff = vectorMagnitude(vectorSubtract(a,b));
    }
    return a;
}; /* Calls secant method narrowing points until iteration is smaller than set epsilon */

int main() {
    int rootsFound;
    vector roots[4];
    vector a, b;
    a.x = -5;
    a.y = 0;
    b.x = 5;
    b.y = 0;
    printf("a is (%lf,%lf)\n",a.x,a.y);
    printf("b is (%lf,%lf)\n",b.x,b.y);

    for (rootsFound = 0; rootsFound < 4; rootsFound++){
        a.x = a.y = 10;
        b.x = b.y = -7;
        roots[rootsFound] = findRoot(a,b,roots, rootsFound);
        printf("Root %d is at (%lf,%lf)\n",rootsFound + 1,roots[rootsFound].x,roots[rootsFound].y);
    };
}; /* calls findRoot 4 times for and outputs results */