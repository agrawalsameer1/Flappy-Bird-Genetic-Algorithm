#include "Matrix.h"

double genRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a distribution between min and max
    std::uniform_real_distribution<> dis(min, max);
    
    // Generate and return the random number
    return dis(gen);
}

Matrix::Matrix() {
    xDim = 1;
    vals = new double[xDim];
    vals[0] = genRandomNumber(-1, 1);
}

Matrix::Matrix(int xDimension) {
    xDim = xDimension;
    vals = new double[xDim];

    for (int i = 0; i < xDim; i++) {
        vals[i] = genRandomNumber(-1, 1);
    }
}

Matrix::Matrix(const Matrix& other) {
    xDim = other.xDim;
    if (vals != nullptr) {
        delete[] vals;
    }

    vals = new double[xDim];

    for (int i = 0; i < xDim; i++) {
        vals[i] = other.vals[i];
    }
}

Matrix::~Matrix() {
    delete[] vals;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        xDim = other.xDim;
        if (vals != nullptr) {
            delete[] vals;
        }

        vals = new double[xDim];

        for (int i = 0; i < xDim; i++) {
            vals[i] = other.vals[i];
        }
    }
    
    return *this;
}

double Matrix::get(int index) {
    return vals[index];
}

void Matrix::set(int index, double newVal) {
    vals[index] = newVal;
}

double Matrix::multiply(Matrix b) {
    double result = 0;

    for (int i = 0; i < xDim; i++) {
        result += (vals[i] * b.vals[i]);
    }

    return result;
}

void Matrix::set(Matrix b) {
    xDim = b.xDim;

    for (int i = 0; i < xDim; i++) {
        vals[i] = b.vals[i];
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& dt) {
    for (int i = 0; i < dt.xDim; i++) {
        os << dt.vals[i] << " ";
    }
    return os;
}