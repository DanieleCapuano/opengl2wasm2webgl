#version 300 es
precision mediump float;

/*
    WARNING - DON'T USE INLINE COMMENTS NEAR YOUR CODE
    e.g.
    uniform float myuniform;    //THIS WON'T WORK
*/

// Inputs to the vertex shader
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

// Uniform variables
uniform mat4 u_modelview;
uniform mat4 u_projection; 

// Additional outputs for the vertex shader in addition to gl_Position
out vec3 mynormal;
out vec4 myvertex;

void main() {
    gl_Position = u_projection * u_modelview * vec4(a_position, 1.0); 

	mynormal = mat3(transpose(inverse(u_modelview))) * a_normal; 
    myvertex = u_modelview * vec4(a_position, 1.0) ; 
}

