//
//  material.h
//  Raytra
//
//  Created by Yang He on 10/4/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef material_h
#define material_h

#include "basicmath.h"

class Material {
    
public:
    
    Material () {
        k_diffuse.set(.2,.3,.8);
        k_specular.set(.9,.9,.9);
        k_reflective.set(0.,0.,0.);
        phong = 0.5;
    }
    
    Material (myvector &d, myvector &s, myvector &r, float p) {
        k_diffuse = d;
        k_specular = s;
        k_reflective = r;
        phong = p;
    }
    
    myvector phongShading(const myvector &n,
                          const myvector &l,
                          const myvector &v,
                          const myvector &I);

private:
    
    myvector k_diffuse;
    myvector k_specular;
    myvector k_reflective;
    float phong;
};

#endif /* material_h */
