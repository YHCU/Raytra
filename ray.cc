//
//  ray.cc
//  Raytra
//
//  Created by Yang He on 9/24/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include "ray.h"

Ray::Ray() {
    
}

Ray::Ray(const mypoint &origin, const myvector & dir) {
    o = origin;
    d = dir;
    d.normalize();
}

void Ray::setOrigin(const mypoint new_origin) {
    o = new_origin;
}

void Ray::setDirection(const myvector new_dir){
    d = new_dir;
    d.normalize();
}

mypoint Ray::getOrigin() const {
    return o;
}

myvector Ray::getDirection() const {
    return d;
}

mypoint Ray::pointOnRay(double t) const {
    return mypoint(o[0] + t * d[0],
                   o[1] + t * d[1],
                   o[2] + t * d[2]);
}
