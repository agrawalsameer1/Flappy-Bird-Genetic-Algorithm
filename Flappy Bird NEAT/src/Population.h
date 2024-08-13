#include "Model.h"
#include <vector>
#include <algorithm> 

#pragma once

class Population {
    public:
        int popSize;
        std::vector<Model> population;

        Population();
        Population(int xDim, int n);

        void clearPopulation();

        void setPopulation(Population newPop);
        
        void fitnessFunction(Matrix* xVals, double* yVals, int dataLength);

        Population getFittest(int n);

        Population crossOver(int newSize, int nKeepSame, double scale);
};