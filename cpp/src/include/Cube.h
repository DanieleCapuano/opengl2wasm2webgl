#ifndef CUBE_H
#define CUBE_H

#include "ObjModel.h"
#include "shaders-def.h"


/****************************************
    CUBE CLASS
*/
class Cube: public ObjModel {    
  private:
    list<string> attrsNames = {"a_position", "a_normal"};
    // list<string> attrsNames = {"a_position"};
    list<string> uniformsNames = {
      "u_modelview", 
      "u_projection", 
      "u_time", 
      "u_opacity",
      "u_ambient",
      "u_diffuse",
      "u_specular",
      "u_emission",
      "u_shininess",
      "u_lightposn",    // positions of lights 
      "u_lightcolor",   // colors of lights
      "u_nlights"       // number of lights used
    };

    const char* vertexShaderSource; 
    const char* fragmentShaderSource;
    float cubeSize = 2.5;
    GLfloat material_ambient[4] = { 0.2, 0.2, 0.2, 1. };
    GLfloat material_diffuse[4] = { 0.4, 0.2, 0.2, 1. };
    GLfloat material_specular[4] = { .5, .5, 1., 1. };
    GLfloat material_emission[4] = { 0., 0., 0., 0. };
    float material_shininess = 50.;

    const GLfloat cubeVerts[24][3] = {
      // Front face
      { -0.5f, -0.5f, 0.5f },{ -0.5f, 0.5f, 0.5f },{ 0.5f, 0.5f, 0.5f },{ 0.5f, -0.5f, 0.5f },
      // Back face
      { -0.5f, -0.5f, -0.5f },{ -0.5f, 0.5f, -0.5f },{ 0.5f, 0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f },
      // Left face
      { -0.5f, -0.5f, 0.5f },{ -0.5f, 0.5f, 0.5f },{ -0.5f, 0.5f, -0.5f },{ -0.5f, -0.5f, -0.5f },
      // Right face
      { 0.5f, -0.5f, 0.5f },{ 0.5f, 0.5f, 0.5f },{ 0.5f, 0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f },
      // Top face
      { 0.5f, 0.5f, 0.5f },{ -0.5f, 0.5f, 0.5f },{ -0.5f, 0.5f, -0.5f },{ 0.5f, 0.5f, -0.5f },
      // Bottom face
      { 0.5f, -0.5f, 0.5f },{ -0.5f, -0.5f, 0.5f },{ -0.5f, -0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f }
    };

    // Cube normals
    const GLfloat cubeNorms[24][3] = {
      // Front face
      { 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 0.0f, 1.0f },
      // Back face
      { 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f, -1.0f },
      // Left face
      { -1.0f, 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f },
      // Right face
      { 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f },
      // Top face
      { 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f, 0.0f },
      // Bottom face
      { 0.0f, -1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f }
    };

    // Cube indices
    const GLuint cubeIndices[36] = {
      0, 2, 1, 0, 3, 2, // Front face
      4, 5, 6, 4, 6, 7, // Back face
      8, 9, 10, 8, 10, 11, // Left face
      12, 14, 13, 12, 15, 14, // Right face
      16, 18, 17, 16, 19, 18, // Top face
      20, 21, 22, 20, 22, 23 // Bottom face
    };

    mat4 updateModelView(ShaderOpts *opts);

  public:
    Cube() {};
    virtual ~Cube() {}; //destructor

    void init();
    GLuint initVAO(GLuint program);
    void draw(ShaderOpts *opts);
};

#endif