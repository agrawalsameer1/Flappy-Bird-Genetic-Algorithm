#include "Matrix.h"

#pragma once

class Model {
    public:
        Matrix params;
        double fitness = 0;

        Model();
        Model(int xDimension);

        void setParams(Matrix params2);
        Matrix getParams();
        
        void setFitness(double newFitness);
        void calcFitness(Matrix* xVals, double* yVals, int dataLength);
        double getFitness();

        int getDims();
};