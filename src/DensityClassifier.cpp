/* 
 * File:   DensityClassifier.cpp
 * Author: gurdil
 * 
 * Created on March 24, 2015, 11:19 PM
 */

#include "DensityClassifier.h"

DensityClassifier::DensityClassifier(int nbClass, int densitySize, int k) :
nbClass(nbClass),
densitySize(densitySize),
k(k)
{
}

DensityClassifier::~DensityClassifier() 
{
}

void DensityClassifier::learn(std::vector<MyImage> images)
{
	proba.clear();
    int elementPerClass = images.size()/nbClass;
    for (int i = 0; i < images.size(); ++i)
    {
    	proba.push_back(images[i].density(densitySize));
	}
}

double DensityClassifier::euclidianDistance(std::vector<double> a,std::vector<double> b)
{
	double diff = 0;
	for (int i = 0; i < a.size(); ++i)
	{
		diff += std::abs(a[i] - b[i]);
	}
	return diff/(double)a.size();
}

bool compare(std::tuple<int, double> i, std::tuple<int, double> j)
{
	return std::get<1>(i) < std::get<1>(j);
}

std::vector<double> DensityClassifier::test(MyImage image)
{
	std::vector<double> result(nbClass,0);

    auto densityTest = image.density(densitySize);
    int elementPerClass = proba.size()/nbClass;
    
    std::vector<std::tuple<int, double>> distance;

    for (int i = 0; i < nbClass; ++i)
    {
		for (int j = 0; j < elementPerClass; j++)
		{
			int element = i*elementPerClass+j;
			double eDistance = this->euclidianDistance(proba[element], densityTest);
			distance.push_back(std::make_tuple(i, eDistance));
		}
	}

    std::sort (distance.begin(), distance.end(), compare);

    for (int i = 0; i < k; ++i)
    {
    	result[std::get<0>(distance[i])]+=1;
	}

    return result;
}

int DensityClassifier::tests(std::vector<MyImage> images)
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
