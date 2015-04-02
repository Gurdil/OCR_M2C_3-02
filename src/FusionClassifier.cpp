/* 
 * File:   FusionClassifier.cpp
 * Author: gurdil
 * 
 * Created on March 25, 2015, 1:39 AM
 */

#include "FusionClassifier.h"

FusionClassifier::FusionClassifier(int nbClass, DistanceClassifier distanceClassifier, DensityClassifier densityClassifier) : 
nbClass(nbClass),
distanceClassifier(distanceClassifier), 
densityClassifier(densityClassifier)
{
}

FusionClassifier::~FusionClassifier() 
{
}

void FusionClassifier::learn(std::vector<MyImage> images)
{
    this->distanceClassifier.learn(images);
    this->densityClassifier.learn(images);
}

std::vector<double> FusionClassifier::test(MyImage image)
{
    auto distance = this->distanceClassifier.test(image);
    auto density = this->densityClassifier.test(image);
    
    std::vector<double> result(distance.size(), 0);
    double sum = 0;
    for (int i = 0; i < result.size(); i++) 
    {
        result[i] = distance[i] * density[i];
        sum += result[i];
    }

    for (int i = 0; i < result.size(); i++) 
    {
        result[i] = result[i] / sum;
    }
    
    return result;
}

int FusionClassifier::tests(std::vector<MyImage> images)
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
