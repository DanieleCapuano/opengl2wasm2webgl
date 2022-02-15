#ifndef GLUTILS_H
#define GLUTILS_H

#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

GLuint loadShader(GLenum type, const char *source);
GLuint buildProgram(GLuint vertexShader, GLuint fragmentShader, list<string> attrs);
void checkGLErrors(const char *from);

#endif