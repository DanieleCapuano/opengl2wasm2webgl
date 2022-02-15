#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "api.h"
#include "types.h"

class ObjModel {    
  public:
    map<string, GLuint> attrsLoc;
    map<string, GLuint> uniformsLoc;
    map<string, BufferData> bufferData;
    GLuint program;
    GLuint vao;

    //destructor
    virtual ~ObjModel() {};

    //to be implemented in derived classes
    virtual GLuint initVAO(GLuint program) = 0;
    virtual void draw(ShaderOpts *opts) = 0;

    void printMatrixDebug(mat4 m, const char *desc);
    void transformvec (mat4 modelview, const GLfloat input[4], GLfloat output[4]);
    int init(const char *vertexShaderSource, const char *fragmentShaderSource, list<string> attrs, list<string>uniforms);
};

#endif