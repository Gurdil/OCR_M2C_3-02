/* 
 * File:   DensityClassifier.h
 * Author: gurdil
 *
 * Created on March 24, 2015, 11:19 PM
 */

#ifndef DENSITYCLASSIFIER_H
#define	DENSITYCLASSIFIER_H

#include "myImage.h"
#include <vector>
#include "classifier.h"
#include <cmath>
#include <tuple>
#include <algorithm>
#include <iostream>

class DensityClassifier : public Classifier
{
public:
    DensityClassifier(int nbClass, int densitySize = 5, int k = 10);
    void learn(std::vector<MyImage> images);
    std::vector<double> test(MyImage image);
    int tests(std::vector<MyImage> images);
    virtual ~DensityClassifier();
private:
    int nbClass;
    int densitySize;
    int k;
    std::vector<std::vector<double>> proba;

    double euclidianDistance(std::vector<double> a,std::vector<double> b);
    //bool compare(std::tuple<int, double> i, std::tuple<int, double> j);
};

#endif	/* DENSITYCLASSIFIER_H */

