#ifndef SCENE_H
#define SCENE_H

#include "api.h"
#include "objects.h"
#include "types.h"

using namespace std;

class Scene {    
 private:
   list<unique_ptr<ObjModel>> obj_list;
   vec3 eye_pos; // Initial eye position, also for resets
   vec3 up_pos; // Initial up position, also for resets
   vec3 center_pos; // Center look at point 
   
   mat4 updateProjectionMatrix(int width, int height, ShaderOpts *opts);
   mat4 updateModelViewMatrix(ShaderOpts *opts);

 public:
    int init();
    void draw(int width, int height, ShaderOpts *opts);

};

#endif