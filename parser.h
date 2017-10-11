#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>


#include "surface.h"
#include "camera.h"
#include "material.h"
#include "light.h"

//
// Basic parser for the scene files:
//

class Parser {

public:
    virtual void parse(const char *file,
                       std::vector<Surface*> &surfaceList,
                       std::vector<Light*> &lightList,
                       std::vector<Material*> &materialList,
                       Camera &cam);
    
};



#endif 
