#ifdef EMSCRIPTEN
#include <emscripten.h>
#else 
#include <windows.h>  // For MS Windows
#endif

#include "api.h"
#include "Scene.h"

using namespace std;

int screen_width, screen_height;
vec3 eye_pos(0.0, 0.0, 5.0);
vec3 up_pos(0.0, 1.0, 0.0);
vec3 center_pos(0.0, 0.0, 0.0);

Scene SCENE;
ShaderOpts opts;

void videoInit(int width, int height) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL2Wasm2WebGL");
    glewInit();
}

void updateOptions(ShaderOpts *options, float time, float opacity, float t_x, float t_y, float r_x, float r_y) {
	options->curr_time = time;
	options->opacity = opacity;

	options->eye = eye_pos;
	options->center = center_pos;
	options->up = Transform::upvector(up_pos, vec3(eye_pos - center_pos));

	Transform::left(r_x, options->eye, options->up);
	Transform::up(r_y, options->eye, options->up);

	options->nlights = 2;
	//light 1
	options->lightposn[0] = 0.;
	options->lightposn[1] = 4.;
	options->lightposn[2] = 10.;
	options-> lightposn[3] = 0.;
	//light 2
	options->lightposn[4] = -3.;
	options->lightposn[5] = -5.;
	options->lightposn[6] = 6.;
	options-> lightposn[7] = 0.;

	//light col 1
	options->lightcolors[0] = 0.2;
	options->lightcolors[1] = 0.5;
	options->lightcolors[2] = 0.0;
	options->lightcolors[3] = 1.;

	//light col 2
	options->lightcolors[4] = 0.0;
	options->lightcolors[5] = 0.2;
	options->lightcolors[6] = 0.6;
	options->lightcolors[7] = 1.;

	options->curr_time = time;
	options->opacity = opacity;

	options->t_x = t_x;
	options->t_y = t_y;
}

extern "C" int initGLAPI(int width, int height) {
	videoInit(width, height);

	SCENE.init();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, width, height);
	return 1;
}

extern "C" void drawAPI(
	float width, float height, 
	float time, float opacity,
	float translate_x, float translate_y,
	float rotate_x, float rotate_y
) {
	//to manage window resize
	glutInitWindowSize(width, height);

	//fill the screen with the clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	updateOptions(&opts, time, opacity, translate_x, translate_y, rotate_x, rotate_y);
	SCENE.draw(width, height, &opts);

	//swap buffer to make whatever we've drawn to backbuffer appear on the screen
	glutSwapBuffers();
}