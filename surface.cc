//
//  surface.cpp
//  Raytra
//
//  Created by Yang He on 10/9/17.
//  Copyright © 2017 Yang He. All rights reserved.
//


#include "surface.h"

double Surface::intersect(const Ray &) const {
    
    std::cout << "don't call Surface::intersect" << std::endl;
    
    return -1;
    
}

myvector Surface::computeNorm(const mypoint &intersection) const {
    
    std::cout << "don't call Surface::computeNorm" << std::endl;
    
    return myvector(0.,0.,0.);
}
