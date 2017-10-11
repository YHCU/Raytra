//
//  material.cc
//  Raytra
//
//  Created by Yang He on 10/9/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include <stdio.h>
#include "material.h"

myvector Material::phongShading(const myvector &n,
                                const myvector &l,
                                const myvector &v,
                                const myvector &I){
    
    myvector rgb(0. ,0. ,0. );
    
    double n_dot_l = n.dotProduct(l);
    if (n_dot_l < 0) {
        n_dot_l = 0;
    }
    myvector diffuse(I[0]*n_dot_l*k_diffuse[0],
                     I[1]*n_dot_l*k_diffuse[1],
                     I[2]*n_dot_l*k_diffuse[2]);
    rgb += diffuse;
    
    
    myvector h(l[0] + v[0], l[1] + v[1], l[2] + v[2]);
    if (h.dotProduct(h) > 0) {
        h.normalize();
    }
    double n_dot_h = n.dotProduct(h);
    if (n_dot_h < 0) {
        n_dot_h = 0;
    }
    double n_dot_h_pow = pow(n_dot_h, phong);
    myvector specular(I[0]*n_dot_h_pow*k_specular[0],
                      I[1]*n_dot_h_pow*k_specular[1],
                      I[2]*n_dot_h_pow*k_specular[2]);
    rgb += specular;
    
    return rgb;
}
