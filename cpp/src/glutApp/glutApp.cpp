
#include "api.h"
#include <time.h>

using namespace std;

int width = 675; 
int height = 675;
float currtime = 0.0;
clock_t t;

float t_x = 0., t_y = 0.;   //translate x and y

void reshape(int w, int h) {
    width = w;
    height = h;
}

void display() {
    currtime = clock() - t;
    currtime = ((float)currtime)/CLOCKS_PER_SEC;    //in seconds
    drawAPI(width, height, currtime, 1.0, t_x, t_y);
}

void specialKey(int key, int x, int y) {
  switch(key) {
    case 100: //left
        t_x -= .1;
        break;
    case 101: //up
        t_y += .1;
        break;
    case 102: //right
        t_x += .1;
        break;
    case 103: //down
        t_y -= .1;
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

    t = clock();
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKey);
    glutMainLoop();
    return 0;
}