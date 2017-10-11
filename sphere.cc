//
//  sphere.cc
//  Raytra
//
//  Created by Yang He on 9/23/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include "sphere.h"


Sphere::Sphere(mypoint center, float radius) {
    c = center;
    r = radius;
}
    
double Sphere::intersect(const Ray &ray) const {
    
    myvector e_c = ray.getOrigin() - c;
    
    myvector d = ray.getDirection();
    double d_dot_d = d.dotProduct(d);
    
    // now compute the two terms under the square root sign:
    
    double discrim_term1 = d.dotProduct (e_c);
    discrim_term1 *= discrim_term1; // square it.
    
    double discrim_term2 = e_c.dotProduct (e_c);
    discrim_term2 -= (r * r);
    discrim_term2 *= d_dot_d;
    
    
    // this is what's under the square root sign:
    double discriminant = discrim_term1 - discrim_term2;
    
    // complex root - missed the sphere:
    if (discriminant < 0.0) {
        return 0;
    }
    
    // otherwise, we hit it (either once or twice) - and discriminant is >= 0
    
    discriminant = sqrt (discriminant);
    
    double quadratic_form = -1 * d.dotProduct (e_c);
    
    double t = (quadratic_form + discriminant) / d_dot_d;
    
    if (discriminant > 0.) {
        double temp_t = (quadratic_form - discriminant) / d_dot_d;
        if (temp_t > 0 and (t <=0 or temp_t < t)) {
            t = temp_t;
        }
    }
    
    if (t > 0) {
        return t;
    }
    
    return 0;
    
    // otherwise, t is the parameter of the closest intersection > 0.
    
    
}

myvector Sphere::computeNorm(const mypoint &intersection) const {
        myvector norm = intersection - c;
        norm.normalize();
        return norm;
}


    
