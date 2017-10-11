//
//  triangle.cc
//  Raytra
//
//  Created by Yang He on 10/10/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include "triangle.h"
#include "basicmath.h"

Triangle::Triangle (mypoint p1, mypoint p2, mypoint p3) {
    point1 = p1;
    point2 = p2;
    point3 = p3;
    norm.crossProduct(point2 - point1, point3 - point1);
    norm.normalize();
}

double Triangle::intersect(const Ray &r) const {
    
    myvector rDir = r.getDirection();
    mypoint rOri = r.getOrigin();
    
    double a = point1[0] - point2[0];
    double b = point1[1] - point2[1];
    double c = point1[2] - point2[2];
    double d = point1[0] - point3[0];
    double e = point1[1] - point3[1];
    double f = point1[2] - point3[2];
    double g = rDir[0];
    double h = rDir[1];
    double i = rDir[2];
    double j = point1[0] - rOri[0];
    double k = point1[1] - rOri[1];
    double l = point1[2] - rOri[2];
    double M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
    
    double t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;
    if (t > 0) {
        double gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
        if (gamma > 0 and gamma < 1) {
            double beta = (j*(e*i - h*f) + k*(g*f - d*i) +l*(d*h - e*g))/M;
            if (beta > 0 and beta < (1 - gamma)) {
                return t;
            }
        }
    }
    
    
    return 0;
}

myvector Triangle::computeNorm(const mypoint &intersection) const {
    return norm;
}
