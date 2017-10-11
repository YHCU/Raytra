//
//  camera.h
//  Raytra
//
//  Created by Yang He on 9/23/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include "basicmath.h"
#include "ray.h"
#include "surface.h"
#include "material.h"
#include "light.h"


#include <ImfStandardAttributes.h>
#include <ImfRgba.h>
#include <ImfRgbaFile.h>
#include <ImfArray.h>


class Camera {

public:
    
    Camera() {};
    
    void init(mypoint pos,
              myvector dir,
              float d,
              float iw,
              float ih,
              int pw,
              int ph);
    
    Ray constructRay(int i, int j);
    
    void renderScene(const std::vector<Surface*> &surfaceList,
                     const std::vector<Light*> &lightList,
                     const std::vector<Material*> &materialList);
    
    void writeImage(const char *scenefile);
    
    void setPixel(int px, int py, float r, float g, float b, float a) {
        Imf::Rgba& pixel = pixelBuffer[py][px];
        pixel.r = r;
        pixel.g = g;
        pixel.b = b;
        pixel.a = a;
    }
    
    void fillBackground(float r, float g, float b) {
        for (int yy = 0; yy < ny; ++yy) {
            for (int xx = 0; xx < nx; ++xx) {
                setPixel(xx, yy, 0, 0, 0, 1);
            }
        }
    }
    
    mypoint getPosition() const {
        return eye;
    }
    
private:
    mypoint eye;
    
    float d;
    
    myvector u;
    myvector v;
    myvector w;
    
    int nx;
    int ny;
    
    float width, height;
    
    Imf::Array2D<Imf::Rgba> pixelBuffer;
    
};


#endif /* camera_hpp */
