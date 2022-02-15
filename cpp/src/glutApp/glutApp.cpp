
#include "api.h"
#include <time.h>

using namespace std;

int width = 675; 
int height = 675;
float currtime = 0.0;
clock_t t;

void reshape(int w, int h) {
    width = w;
    height = h;
}

void display() {
    currtime = clock() - t;
    currtime = ((float)currtime)/CLOCKS_PER_SEC;    //in seconds
    drawAPI(width, height, currtime, 1.0);
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
    glutMainLoop();
    return 0;
}