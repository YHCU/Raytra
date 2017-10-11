//
//  ray.h
//  Raytra
//
//  Created by Yang He on 9/24/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef RAY_H
#define RAY_H

#include <stdio.h>
#include "basicmath.h"

class Ray {
    
private:
    
    mypoint o;
    myvector d;
    
    
public:
    
    Ray ();
    
    Ray (const mypoint &origin, const myvector &dir);
    
    void setOrigin(const mypoint new_origin);
    void setDirection(const myvector new_dir);
    mypoint getOrigin() const;
    myvector getDirection() const;
    
    mypoint pointOnRay(double t) const;
    
};



#endif /* ray_h */
