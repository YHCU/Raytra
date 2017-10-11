//
//  camera.cc
//  Raytra
//
//  Created by Yang He on 9/23/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include <vector>
#include <cmath>
#include <limits>

#include "camera.h"


void Camera::init(mypoint pos,
                  myvector dir,
                  float d,
                  float iw, float ih,
                  int pw, int ph) {
    
    eye = pos;
    
    // check if dir is in the form(0, s, 0)
    if ((dir[0] == 0) && (dir[2] == 0)) {
        // manipulate the dir vector by a bit
        dir.set(dir[1]/1000, dir[1], dir[1]/1000);
    }
    u.crossProduct(dir, myvector(0,1,0));
    v.crossProduct(u, dir);
    w = dir.invert();
    
    // normalize u,v,w
    u.normalize();
    v.normalize();
    w.normalize();
    
    this->d = d;
    nx = pw;
    ny = ph;
    
    width = iw;
    height = ih;
    
    try{
        pixelBuffer.resizeErase(ny, nx);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}

Ray Camera::constructRay(int i, int j) {
    Ray ray;
    ray.setOrigin(eye);
    myvector dir(0, 0, 0);
    dir += w * (-d);
    dir += u * (- (width / 2) + width * (i + 0.5) / nx);
    dir += v * ((height / 2) - height * (j + 0.5) / ny);
    ray.setDirection(dir);
    return ray;
}

void Camera::renderScene(const std::vector<Surface*> &surfaceList,
                         const std::vector<Light*> &lightList,
                         const std::vector<Material*> &materialList) {
    

    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            Ray r = constructRay(x, y);
            
            // check for closest sphere and record it
            double t_min = std::numeric_limits<double>::infinity();
            mypoint intersection;
            myvector norm;
            int materialID = 0;
            bool intersects = false;
            
            for (std::vector<Surface*>::const_iterator itsurf = surfaceList.begin();
                itsurf != surfaceList.end();
                ++itsurf) {
                Surface *newSurface = *itsurf;
                double t = newSurface->intersect(r);
                if (t > 0 and t < t_min) {
                    intersects = true;
                    intersection = r.pointOnRay(t);
                    norm = newSurface->computeNorm(intersection);
                    t_min = t;
                    materialID = newSurface->getMaterialID();
                }
            }
            
            myvector rgb(0.,0.,0.);
            // compute pixel with closest surface
            if (intersects) {
                
                for (std::vector<Light*>::const_iterator itlight = lightList.begin();
                    itlight != lightList.end();
                    ++itlight) {
                    
                    bool shadowed = false;
                    Light *newlight = *itlight;
                    mypoint lightpos = newlight->getPosition();
                    myvector l = lightpos - intersection;
                    double lightDist = sqrt(l.dotProduct(l));
                    
                    Ray shadowRay = Ray(intersection, l);
                    
                    for (std::vector<Surface*>::const_iterator itsurf2 = surfaceList.begin();
                         itsurf2 != surfaceList.end();
                         ++itsurf2) {
                        Surface *newSurface2 = *itsurf2;
                        double t_shadow = newSurface2->intersect(shadowRay);
                        if (t_shadow > 0) {
                            double shadowRayLength = sqrt((shadowRay.getDirection()*t_shadow).dotProduct(shadowRay.getDirection()*t_shadow));
                            if (shadowRayLength > (lightDist/10000)) {
                                shadowed = true;
                                break;
                            }
                        }
                    }
                    
                    if (!shadowed) {
                        l.normalize();
                        
                        myvector v = r.getOrigin() - intersection;
                        v.normalize();
                        
                        rgb += materialList[materialID]->phongShading(norm, l, v, newlight->spd())*(1.0/(lightDist*lightDist));
                    }
                }
            setPixel(x, y, rgb[0], rgb[1], rgb[2], 1);
            }
            
           
            
        }
    }

}

void Camera::writeImage(const char *scenefile) {
    
    try {
        Imf::RgbaOutputFile file(scenefile, nx, ny, Imf::WRITE_RGBA);
        file.setFrameBuffer(&pixelBuffer[0][0], 1, nx);
        file.writePixels(ny);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}












