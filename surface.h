//
//  surface.h
//  Raytra
//
//  Created by Yang He on 10/4/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef surface_h
#define surface_h

#include "ray.h"
#include "basicmath.h"

class Surface {
public:
    Surface() {};
    
    virtual ~Surface() {};
    
    virtual double intersect(const Ray &) const;
    
    virtual myvector computeNorm(const mypoint &) const;
    
    void setMaterialID(int ID) {materialID = ID;}
    
    int getMaterialID() {return materialID;}
    
protected:
    
    int materialID;

};

#endif /* surface_h */
