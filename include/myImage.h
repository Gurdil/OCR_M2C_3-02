/* 
 * File:   myImage.h
 * Author: gurdil
 *
 * Created on March 24, 2015, 1:40 AM
 */

#ifndef MYIMAGE_H
#define	MYIMAGE_H

#define cimg_use_tiff
#include <CImg.h>
#include <vector>
#include <math.h>
#include <iostream>

class MyImage : public cimg_library::CImg<unsigned char>
{
    public:
    MyImage(const char *const 	filename) : cimg_library::CImg<unsigned char>(filename)
    {
        for (unsigned int i = 0; i < this->size(); i++) 
        {
            this->_at(i) = 255 - this->_at(i);
        }
    }
    
    MyImage(const CImg< unsigned char > & img) : cimg_library::CImg<unsigned char>(img)
    {
        
    }
    
    std::vector<MyImage> cut()
    {
        bool detectLine = false;
        int firstLine = 0;
        int lastLine = 0;
        std::vector<MyImage> myvector;
        
        
        
        for (int i = 0; i < this->height(); i++) 
        {
        CImg<unsigned char> row = this->get_shared_row(i);
        double sum = row.sum();
        if(detectLine)
        {
            if (sum == 0)
            {
                lastLine = i;
                CImg<unsigned char> rows = this->get_shared_rows(firstLine, lastLine);


                bool detectCol = false;
                int firstCol = 0;
                int lastCol = 0;
                for (int j = 0; j < rows.width(); j++) 
                {
                    CImg<unsigned char> col = rows.get_column(j);
                    double sumCol = col.sum();
                    if(detectCol)
                    {
                        if (sumCol == 0)
                        {
                            lastCol = j;
                            CImg<unsigned char> image = rows.get_columns(firstCol, lastCol).autocrop();
                            image = image.get_resize(image.width()+2,image.height()+2,-100,-100,0,0,0.5,0.5);
                            myvector.push_back (MyImage(image));
                            detectCol = false;
                        }
                    }
                    else
                    {
                        if (sumCol>0)
                        {
                            firstCol = j;
                            detectCol = true;
                        }
                    }
                }




                detectLine = false;
            }
        }
        else
        {
            if (sum>0)
            {
                firstLine = i;
                detectLine = true;
            }
        }
    }
        return myvector;
    }

    std::vector<double> distance(int N)
    {
        std::vector<double> result;
        int pas = this->height()/(N+1);
        
        for (int i = 1; i <= N; i++) 
        {
            auto row = this->get_row(pas*i);
            
            for (unsigned int j = 0; j < row.size(); j++) 
            {
                if(row._at(j) > 0)
                {
                    result.push_back((double)j/(double)this->width());
                    break;
                }
            }

            for (unsigned int j = row.size(); j > 0; j--) 
            {
                if(row._at(j) > 0)
                {
                    result.push_back((double)(this->width()-j)/(double)this->width());
                    break;
                }
            }
        }

        
        return result;
    }

    std::vector<double> density(int N)
    {
        std::vector<double> result;
        int pasCol = (double)this->width()/(double)N ;
        int pasLi  = (double)this->height()/(double)N;
        
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < N; j++) 
            {
                int startLin = i*pasLi;
                int startCol = j*pasCol;
                auto part = this->get_crop(startCol, startLin, startCol + pasCol, startLin + pasLi);
               result.push_back(part.sum()/(255.0*part.width()*part.height()));
            }
        }

        return result;
    }
};

#endif	/* MYIMAGE_H */

