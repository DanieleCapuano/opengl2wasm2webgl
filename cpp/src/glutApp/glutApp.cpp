
#include "api.h"
#include <time.h>

using namespace std;

int width = 675; 
int height = 675;
float currtime = 0.0;
clock_t t;

float t_x = 0., t_y = 0.;   //translate x and y
float r_x = 0., r_y = 0.;   //rotate (the camera) x and y

bool is_rotate = false;

void reshape(int w, int h) {
    width = w;
    height = h;
}

void display() {
    currtime = clock() - t;
    currtime = ((float)currtime)/CLOCKS_PER_SEC;    //in seconds
    drawAPI(width, height, currtime, 1.0, t_x, t_y, r_x, r_y);
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case 'r': // rotate the eye. 
      std::cout << "Operation is set to (eye) Rotate\n" ; 
      is_rotate = true;
      break ;
    case 't':
      is_rotate = false;
      std::cout << "Operation is set to (world) Translate\n" ; 
      break ;
  }
  glutPostRedisplay();
}

void specialKey(int key, int x, int y) {
  switch(key) {
    case 100: //left
        if (is_rotate) {
            r_x += 1.;
        }
        else {
            t_x -= .1;
        }
        break;
    case 101: //up
        if (is_rotate) {
            r_y -= 1.;
        }
        else {
            t_y += .1;
        }
        break;
    case 102: //right
        if (is_rotate) {
            r_x -= 1.;
        }
        else {
            t_x += .1;
        }
        break;
    case 103: //down
        if (is_rotate) {
            r_y += 1.;
        }
        else {
            t_y -= .1;
        }
        break;
  }
}

// main function
// sets up window to which we'll draw
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    if(!initGLAPI(width, height)) {
        printf("BAAAD!\n");
        return 0;
    }

    std::cout << "Press 'r' for (eye) Rotation, 't' for (world) Translation\n" ; 

    t = clock();
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutMainLoop();
    return 0;
}