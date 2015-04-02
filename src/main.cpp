//#define cimg_use_tiff
//#include <CImg.h>
#include <iostream>
#include <vector>
#include <cmath>
//using namespace cimg_library;

#include "myImage.h"
#include <CImg.h>
#include "DensityClassifier.h"
#include "DistanceClassifier.h"
#include "FusionClassifier.h"

using namespace cimg_library;

int main() 
{
    int const NB_CLASS = 10;
   
   
   MyImage learnImage("./res/app.tif");
    std::vector<MyImage> vectorLearn = learnImage.cut();
   
   MyImage testImage("./res/test.tif");
    std::vector<MyImage> vectorTest = testImage.cut();
   
    std::vector<double> distance = vectorLearn[61].distance(5);

    DistanceClassifier classifier1(NB_CLASS);
    classifier1.learn(vectorLearn);
    std::cout << "Distance classifier :" << classifier1.tests(vectorTest) << std::endl;
    
    DensityClassifier classifier(NB_CLASS);
    classifier.learn(vectorLearn);
    std::cout << "Density classifier :" << classifier.tests(vectorTest) << std::endl;
     
   FusionClassifier classifier2(NB_CLASS, classifier1, classifier);
    classifier2.learn(vectorLearn);
    std::cout << "Fusion classifier :" << classifier2.tests(vectorTest) << std::endl;
     
   cimg_library::CImgDisplay main_disp(vectorTest[14],"Click a point");
   while (!main_disp.is_closed()) {}
  return 0;
}
