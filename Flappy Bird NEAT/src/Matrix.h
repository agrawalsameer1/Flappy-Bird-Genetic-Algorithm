#include <iostream>
#include <random>

#pragma once

class Matrix {
    public:
        int xDim = 1;
        double* vals = nullptr;

        Matrix();
        Matrix(int xDimension);
        Matrix(const Matrix& other);

        ~Matrix();

        Matrix& operator=(const Matrix& other);


        double get(int index);
        void set(int index, double newVal);

        double multiply(Matrix b);

        void set(Matrix b);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& b);
};