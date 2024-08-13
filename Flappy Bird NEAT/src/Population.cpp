#include "Population.h"

bool moreFit(const Model& m1, const Model& m2) 
{ 
    return m1.fitness > m2.fitness; 
} 

double generateRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a distribution between min and max
    std::uniform_real_distribution<> dis(min, max);
    
    // Generate and return the random number
    return dis(gen);
}

Population::Population() {
    ;
}

Population::Population(int xDim, int n) {
    popSize = n;

    population.reserve(popSize);

    for (int i = 0; i < popSize; i++) {
        population.push_back(Model(xDim));
    }
}

void Population::clearPopulation() {
    for (int i = 0; i < popSize; i++) {
        delete[] population[i].params.vals;
    }

    population.clear();
}

void Population::setPopulation(Population newPop) {
    for (int i = 0; i < popSize; i++) {
        population[i].setParams(newPop.population[i].getParams());
    }
}

void Population::fitnessFunction(Matrix* xVals, double* yVals, int dataLength) {
    for (int i = 0; i < popSize; i++) {
        population[i].calcFitness(xVals, yVals, dataLength);
    }
}

Population Population::getFittest(int n) {
    std::sort(population.begin(), population.end(), moreFit);

    Population newPopulation = Population(population[0].getDims(), n);

    for (int i = 0; i < n; i++) {
        newPopulation.population[i].setParams(population[i].getParams());
        newPopulation.population[i].setFitness(population[i].getFitness());
    }

    return newPopulation;
}

Population Population::crossOver(int newSize, int nKeepSame, double scale) {
    Population newPopulation = Population(population[0].getDims(), newSize);

    for (int i = 0; i < nKeepSame; i++) {
        newPopulation.population[i].setParams(population[i].getParams());
    }

    double totalFitness = 0;

    for (int i = 0; i < popSize; i++) {
        totalFitness += population[i].getFitness();
    }

    for (int i = nKeepSame; i < newSize; i++) {
        Matrix params2 = Matrix(population[0].getDims());

        for (int j = 0; j < population[0].getDims(); j++) {
            double curParam = 0;

            for (int k = 0; k < popSize; k++) {
                curParam += (population[k].getParams().get(j)) * (population[k].getFitness()/totalFitness);
            }

            curParam += generateRandomNumber((500./population[0].getFitness()) * -1 * scale, (500./population[0].getFitness()) * scale);

            params2.set(j, curParam);
        }

        newPopulation.population[i].setParams(params2);
    }

    return newPopulation;
}