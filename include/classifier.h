/* 
 * File:   classifier.h
 * Author: gurdil
 *
 * Created on March 24, 2015, 8:55 PM
 */

#ifndef CLASSIFIER_H
#define	CLASSIFIER_H

#include "myImage.h"
#include <vector>

class Classifier {
public:
    virtual void learn(std::vector<MyImage> images)=0;
    virtual std::vector<double> test(MyImage images)=0;
private:

};

#endif	/* CLASSIFIER_H */

