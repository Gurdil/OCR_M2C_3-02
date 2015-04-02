/* 
 * File:   DistanceClassifier.cpp
 * Author: gurdil
 * 
 * Created on March 25, 2015, 12:41 AM
 */

#include "DistanceClassifier.h"

DistanceClassifier::DistanceClassifier(int nbClass, int distanceSize) : nbClass(nbClass), distanceSize(distanceSize)
{
}

DistanceClassifier::~DistanceClassifier() {
}

void DistanceClassifier::learn(std::vector<MyImage> images)
{
	proba.clear();
    int elementPerClass = images.size()/nbClass;
    
    for (int i = 0; i < nbClass; i++) 
    {
        std::vector<double> probaClass(distanceSize*2,0);
        for (int j = 0; j < elementPerClass; j++) 
        {
            int element = i*elementPerClass+j;
            auto distance = images[element].distance(distanceSize);
            for (int k = 0; k < distance.size(); k++) 
            {
                probaClass[k] = probaClass[k] + distance[k];
            }
        }
        
        for (int k = 0; k < probaClass.size(); k++) 
        {
            probaClass[k] = probaClass[k] / elementPerClass;
        }
        
        proba.push_back(probaClass);
    }
}

std::vector<double> DistanceClassifier::test(MyImage image)
{
    auto distanceTest = image.distance(distanceSize);
    
    std::vector<double> result(nbClass,0);
    
    for (int i = 0; i < nbClass; i++) 
    {
        double diff = 0;
        for (int j = 0; j < 2*distanceSize; j++) 
        {
            diff += std::abs(proba[i][j] -  distanceTest[j]);
        }
        result[i] = diff / (double)(2*distanceSize);
    }
    
    for (int i = 0; i < result.size(); i++) 
    {
        result[i] = std::exp(-1*result[i]);
    }

    double sum = 0;
    for (int i = 0; i < result.size(); i++) 
    {
        sum += result[i];
    }
    
    for (int i = 0; i < result.size(); i++) 
    {
        result[i] = result[i]/sum;
    }
    
    
    return result;
}

int DistanceClassifier::tests(std::vector<MyImage> images)
{
     int elementPerClass = images.size()/nbClass;
    
    int nbError = 0;
    
    for (int i = 0; i < images.size(); i++) 
    {
        auto result = this->test(images[i]);
        
        double maximum = 0;
        int rang = 0;
        
        for (int j = 0; j < result.size(); j++) 
        {
            if(result[j] >maximum)
            {
                maximum = result[j];
                rang = j;
            }
        }
        int classe = i / elementPerClass;
        
        if(rang != classe)
        {
            nbError++;
        }
        
    }
    return nbError;
}
