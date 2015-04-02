/* 
 * File:   FusionClassifier.h
 * Author: gurdil
 *
 * Created on March 25, 2015, 1:39 AM
 */

#ifndef FUSIONCLASSIFIER_H
#define	FUSIONCLASSIFIER_H

#include "myImage.h"
#include <vector>
#include "classifier.h"
#include "DensityClassifier.h"
#include "DistanceClassifier.h"
#include <cmath>

class FusionClassifier : public Classifier
{
public:
    FusionClassifier(int nbClass, DistanceClassifier distanceClassifier, DensityClassifier densityClassifier);
    void learn(std::vector<MyImage> images);
    std::vector<double> test(MyImage image);
    int tests(std::vector<MyImage> images);
    virtual ~FusionClassifier();
private:
    int nbClass;
    DistanceClassifier distanceClassifier;
    DensityClassifier densityClassifier;
};

#endif	/* FUSIONCLASSIFIER_H */

