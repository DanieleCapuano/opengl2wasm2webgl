#include "Scene.h"

int Scene::init() {
    Cube *C = new Cube();
    C->init();
    obj_list.emplace_back(C);

    return 1;
}

//here we update the projection for the scene due to interactive transforms and window reshaping
mat4 Scene::updateProjectionMatrix(int width, int height, ShaderOpts *opts) {
	mat4 proj;
    float
        fovy = 90.0, // For field of view
        aspect = (float) width / (float) height, 
        zNear = 0.1, 
        zFar = 99.0;

    proj = Transform::perspective(fovy, aspect, zNear, zFar);
	return proj;
}

mat4 Scene::updateModelViewMatrix(ShaderOpts *opts) {
    eye_pos = opts->eye;
    center_pos = opts->center;
    up_pos = opts->up;

    return Transform::lookAt(opts->eye, opts->center, opts->up);
}


void Scene::draw(int width, int height, ShaderOpts *opts) {
    opts->projection_matrix = updateProjectionMatrix(width, height, opts);
    opts->modelview_matrix = updateModelViewMatrix(opts);

    for (list<unique_ptr<ObjModel>>::iterator itr=obj_list.begin(); itr!=obj_list.end(); ++itr) {
        (*itr)->draw(opts);
    }
}