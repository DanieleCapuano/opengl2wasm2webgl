#include "ObjModel.h"

int ObjModel::init(
	const char *vertexShaderSource, 
	const char *fragmentShaderSource, 
	list<string> attrs, 
	list<string>uniforms
) {
    //load vertex and fragment shaders
	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
	if (!vertexShader) {
		checkGLErrors("Vertex shader");
		return 0;
	}
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	if (!fragmentShader) {
		checkGLErrors("Fragment shader");
		return 0;
	}

	program = buildProgram(vertexShader, fragmentShader, attrs);
	if (!program) {
		checkGLErrors("Build program");
		return program;
	}

	//save location of attributes variables to be used in derived classes
	for (string attr_name : attrs) {
		const char *aname = attr_name.c_str();
		attrsLoc[aname] = glGetAttribLocation(program, aname);
#ifdef DEBUG_RUN
		printf("ATTR %s at LOC %d\n", aname, attrsLoc[aname]);
#endif
	}

	//save location of uniform variables to be used in derived classes
	for (string unif_name : uniforms) {
		const char* uname = unif_name.c_str();
		uniformsLoc[unif_name.c_str()] = glGetUniformLocation(program, uname);
#ifdef DEBUG_RUN
		printf("UNIFORM %s at LOC %d\n", uname, attrsLoc[uname]);
#endif
	}

	return 1;
}

void ObjModel::printMatrixDebug(mat4 m, const char *desc) {
	printf("******Matrix %s\n", desc);
	printf("%.2f %.2f %.2f %.2f\n", m[0][0], m[0][1], m[0][2], m[0][3]);
	printf("%.2f %.2f %.2f %.2f\n", m[1][0], m[1][1], m[1][2], m[1][3]);
	printf("%.2f %.2f %.2f %.2f\n", m[2][0], m[2][1], m[2][2], m[2][3]);
	printf("%.2f %.2f %.2f %.2f\n", m[3][0], m[3][1], m[3][2], m[3][3]);
}

void ObjModel::transformvec(mat4 modelview, const GLfloat input[4], GLfloat output[4])  {
	vec4 inputvec(input[0], input[1], input[2], input[3]);

	vec4 outputvec = modelview * inputvec;
	output[0] = outputvec[0];
	output[1] = outputvec[1];
	output[2] = outputvec[2];
	output[3] = outputvec[3];
}