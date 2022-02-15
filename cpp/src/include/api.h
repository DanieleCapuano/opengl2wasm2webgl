#ifndef API_H
#define API_H

// #define DEBUG_RUN

#include <algorithm>
#include <iostream>
#include <memory>
#include <list>
#include <map>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <vector>

#include "Transform.h"
#include "gl-utils.h"

using namespace std;

extern "C" int initGLAPI(int width, int height);
extern "C" void drawAPI(float width, float height, float time, float opacity, float translate_x, float translate_y);

#endif