#include "api.h"

using namespace std;

GLuint loadShader(GLenum type, const char *source) {
	//create a shader
	GLuint shader = glCreateShader(type);
	if (shader == 0) {
		checkGLErrors("Error creating shader");
		return 0;
	}

	//load the shader source to the shader object and compile it
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	//check if the shader compiled successfully
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char errorLog[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		checkGLErrors(errorLog);
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint buildProgram(GLuint vertexShader, GLuint fragmentShader, list<string> attrs) {
	//create a GL program and link it
	GLuint programObject = glCreateProgram();
	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	int i=0;
	for (string attr : attrs) {
		const char *aname = attr.c_str();
		// GLuint loc = glGetAttribLocation(programObject, aname);
		// printf("ATTRIB LOC for ATTR %s: %d\n", aname, loc);
		glBindAttribLocation(programObject, i, aname);
		i++;
	}
	glLinkProgram(programObject);

	//check if the program linked successfully
	GLint linked;
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked) {
		printf("QUI ERRORONE\n");
		checkGLErrors("After program link failed");
		glDeleteProgram(programObject);
		return 0;
	}
	return programObject;
}


char const* gl_error_string(GLenum const err) noexcept
{
  switch (err)
  {
    // opengl 2 errors (8)
    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";

    case GL_TABLE_TOO_LARGE:
      return "GL_TABLE_TOO_LARGE";

    // opengl 3 errors (1)
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    // gles 2, 3 and gl 4 error are handled by the switch above
    default:
      assert(!"unknown error");
      return nullptr;
  }
}

void checkGLErrors(const char *from) {
	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR) {
		printf("ERROR from %s\n", from);
		printf("%s\n", gl_error_string(err));
	}
}