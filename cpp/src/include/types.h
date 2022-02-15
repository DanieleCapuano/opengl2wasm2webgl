#ifndef TYPES_H
#define TYPES_H

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <math.h>
// #include <vector>
#include "api.h"

// glm provides vector, matrix classes like glsl
// Typedefs to make code more readable 

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;

const int MAX_LIGHTS_N = 10;
struct ShaderOpts {
    mat4 projection_matrix;
    mat4 modelview_matrix;
    vec3 eye;
    vec3 up;
    vec3 center;
    GLfloat lightposn[4*MAX_LIGHTS_N];     // positions of lights
    GLfloat lightcolors[4*MAX_LIGHTS_N];   // colors of lights
    int nlights;                           // number of lights used

    float curr_time;
    float opacity;
} ;

struct BufferData {
  int data_size;
  void *data;
};

#endif