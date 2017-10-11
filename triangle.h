//
//  triangle.h
//  Raytra
//
//  Created by Yang He on 10/10/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef triangle_h
#define triangle_h

#include "basicmath.h"
#include "ray.h"
#include "surface.h"

class Triangle: public Surface {
    
    mypoint point1, point2, point3;
    myvector norm;
    
public:
    
    Triangle() {};
    Triangle(mypoint p1, mypoint p2, mypoint p3);
    ~Triangle(){};
    
    double intersect (const Ray &r) const;
    
    myvector computeNorm (const mypoint &intersection) const;
    
};


#endif /* triangle_h */
