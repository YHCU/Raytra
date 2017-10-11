
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "parser.h"

// assumes you have defined these h files - use other names
// if you have made other files that fit here!
#include "basicmath.h"
#include "sphere.h"
#include "triangle.h"   

using namespace std;


// In this code, you can see how Sphere and Camera are set up - you
// will need to do similar for the other classes.
//
// You will also need to keep track of the last material defined, so
// that you can connect it to any surfaces that are subsequently defined.
//
void Parser::parse(const char *file,
                   std::vector<Surface*> &surfaceList,
                   std::vector<Light*> &lightList,
                   std::vector<Material*> &materialList,
                   Camera &cam) {
    
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    int num_cams = 0; // keep track of how many cameras we read in
    
    int materialID = 0;
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        Surface *thissurface = 0;

        cmd="";
        
        istringstream iss(buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='/' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        } 
        else if (cmd=="s") {
            mypoint pos; 
            double r;
            iss >> pos >> r;
            thissurface = new Sphere(pos, r);
        } 
        else if (cmd=="t") {
            // Triangle
            mypoint p1, p2, p3;
            iss >> p1 >> p2 >> p3;
            thissurface = new Triangle(p1, p2, p3);
            
        }
        else if (cmd=="p") {
            // Plane
        }
        else if (cmd=="c") {
            // Camera:
            ++num_cams; // keep track of how many we read in
 
            
            // read in the parameters:
            mypoint pos; myvector dir; 
            double d,iw,ih; 
            int pw,ph;
            iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
            
            // construct it:
            cam.init (pos,dir,d,iw,ih,pw,ph);
        } 
        else if (cmd=="l") {
            
            string lighttype = "";
            iss >> lighttype;
            if (lighttype == "p") {
                mypoint pos;
                myvector I;
                iss >> pos >> I;
                Light *pointLight = new PointLight(I, pos);
                lightList.push_back(pointLight);
            }
            if (lighttype == "d") {
            }
            if (lighttype == "a") {
            }
        }
        else if (cmd=="m") {
            myvector diff,spec,refl;
            double phong;
            iss >> diff >> spec >> phong >> refl;
            
            Material *thismaterial = new Material(diff, spec, refl, phong);
            materialList.push_back(thismaterial);
            ++materialID;
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << endl;
        }
        
        if (thissurface) {
            surfaceList.push_back(thissurface);
            thissurface->setMaterialID(materialID);
        }

    }
    
    in.close();
    
    // make sure we read in 1 camera, no more no less 8).
    if (num_cams != 1) {
        std::cerr << "scene file error: exactly ONE camera must be defined." << endl;
    }
    
}
