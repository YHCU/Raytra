//
//  pointlight.h
//  Raytra
//
//  Created by Yang He on 10/4/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef light_h
#define light_h

#include "basicmath.h"

class Light {

public:
    
    Light() {pos.set(0.,0.,0.);}
    
    virtual ~Light() {}
    
    virtual myvector spd() = 0;
    
    mypoint getPosition () const {return pos;}

protected:
    
    mypoint pos;

};

class PointLight: public Light {

public:
    
    PointLight() {}
    PointLight (const myvector &I, const mypoint &position) {
        pos = position;
        rgb = I;
    }
    ~PointLight() {}
    
    virtual myvector spd() {return rgb;}
    
private:
    
    myvector rgb;

};


#endif /* light_h */
