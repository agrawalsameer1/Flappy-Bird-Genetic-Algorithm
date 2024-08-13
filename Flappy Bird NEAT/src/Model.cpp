#include "Model.h"

Model::Model() {
    params = Matrix();
    fitness = 0;
}

Model::Model(int xDimension) {
    params = Matrix(xDimension);
    fitness = 0;
}

void Model::setParams(Matrix params2) {
    params.set(params2);
}

Matrix Model::getParams() {
    return params;
}

void Model::setFitness(double newFitness) {
    //std::cout << "newFitness: " << newFitness << "\n";
    fitness = newFitness;
}

void Model::calcFitness(Matrix* xVals, double* yVals, int dataLength) {
    double newFitness = 0;

    for (int i = 0; i < dataLength; i++) {
        newFitness += ((abs(yVals[i] - params.multiply(xVals[i])))/dataLength);
    }

    setFitness(newFitness);
}

double Model::getFitness() {
    return fitness;
}

int Model::getDims() {
    return params.xDim;
}