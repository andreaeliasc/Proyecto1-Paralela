#include <stdio.h>

class Modelo {
    public:
        double *matrix;
        int columns;
        int rows;

    double get(int i, int j){return matrix[columns*i + j];}
    void set(int i, int j, double element){matrix[columns*i + j] = element; }
};