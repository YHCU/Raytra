//
//  main.cc
//  Raytra
//
//  Created by Yang He on 9/23/17.
//  Copyright © 2017 Yang He. All rights reserved.
//

#include <iostream>

#include "parser.h"
#include "surface.h"
#include "light.h"
#include "material.h"
#include "camera.h"

using namespace std;

#include <ImfStandardAttributes.h>
#include <ImfRgba.h>
#include <ImfRgbaFile.h>
#include <ImfArray.h>




int main(int argc, const char * argv[]) {
    
    
    try
    {
        std::vector<Surface*> surfaceList;
        std::vector<Light*> lightList;
        std::vector<Material*> materialList;
        Camera thecamera;
        Parser parser1;
        Material *default_mat = new Material;
        materialList.push_back(default_mat);
        
        parser1.parse(argv[1], surfaceList, lightList, materialList, thecamera);
        
        assert(surfaceList.size() != 0);
        
        if (lightList.size() == 0) {
            myvector defaultlightcolor(1,1,1);
            PointLight *defaultLight = new PointLight(defaultlightcolor, thecamera.getPosition());
            lightList.push_back(defaultLight);
        }
        thecamera.fillBackground(0, 0, 0);
        thecamera.renderScene(surfaceList, lightList, materialList);

        thecamera.writeImage(argv[2]);
        
        for (Surface *s: surfaceList) {
            delete s;
        }
        
        for (Light *l: lightList) {
            delete l;
        }
        
        for (Material *m: materialList) {
            delete m;
        }
        
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    
    
    
    return 0;
}
