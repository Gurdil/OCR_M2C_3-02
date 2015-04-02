/* 
 * File:   DistanceClassifier.h
 * Author: gurdil
 *
 * Created on March 25, 2015, 12:41 AM
 */

#ifndef DISTANCECLASSIFIER_H
#define	DISTANCECLASSIFIER_H

#include "myImage.h"
#include <vector>
#include "classifier.h"
#include <cmath>

class DistanceClassifier : public Classifier
{
public:
    DistanceClassifier(int nbClass, int distanceSize = 5);
    void learn(std::vector<MyImage> images);
    std::vector<double> test(MyImage image);
    int tests(std::vector<MyImage> images);
    virtual ~DistanceClassifier();
private:
    int nbClass;
    int distanceSize;
    std::vector<std::vector<double>> proba;
};

#endif	/* DISTANCECLASSIFIER_H */

