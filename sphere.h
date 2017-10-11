//
//  sphere.h
//  Raytra
//
//  Created by Yang He on 9/23/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef SPHERE_H
#define SPHERE_H

#include <stdio.h>
#include "basicmath.h"
#include "ray.h"
#include "surface.h"

class Sphere : public Surface {
    
    mypoint c;
    float r;
    
public:
    
    Sphere(){};
    Sphere(mypoint center, float radius);
    ~Sphere(){};
    
    // return > 0 if intersects, else 0
    double intersect (const Ray &r) const;
    
    myvector computeNorm(const mypoint &intersection) const;
    
};


#endif /* sphere_hpp */
