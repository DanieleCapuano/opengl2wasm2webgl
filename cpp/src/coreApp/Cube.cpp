#include "Cube.h"

void Cube::init() {
	vertexShaderSource = CUBE_VERT;
	fragmentShaderSource = CUBE_FRAG;

	BufferData verts_data;
	BufferData indices_data;
	BufferData norms_data;

	verts_data.data_size = sizeof(cubeVerts);
	verts_data.data = (void *)cubeVerts;
	bufferData["a_position"] = verts_data;


	norms_data.data_size = sizeof(cubeNorms);
	norms_data.data = (void *)cubeNorms;
	bufferData["a_normal"] = norms_data;

	indices_data.data_size = sizeof(cubeIndices);
	indices_data.data = (void *)cubeIndices;
	bufferData["indices"] = indices_data;

	ObjModel::init(vertexShaderSource, fragmentShaderSource, attrsNames, uniformsNames);
	vao = initVAO(program);
}

GLuint Cube::initVAO(GLuint program) {
	GLuint pos_buffer, norm_buffer, ind_buffer;
	GLuint vao;
	BufferData buf_data;

	glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //bind buffers and write coordinates into them
	glGenBuffers(1, &pos_buffer);
	glGenBuffers(1, &norm_buffer);
	glGenBuffers(1, &ind_buffer);
	checkGLErrors("After GEN BUFFERS");
    
    ////////////////////////
    //positions
	buf_data = bufferData["a_position"];
	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
    glBufferData(GL_ARRAY_BUFFER, buf_data.data_size, buf_data.data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attrsLoc["a_position"]);
    glVertexAttribPointer(attrsLoc["a_position"], 3, GL_FLOAT, GL_FALSE, 0, 0);
	checkGLErrors("After POS SETTING");


	////////////////////////
    //normals
	buf_data = bufferData["a_normal"];
	glBindBuffer(GL_ARRAY_BUFFER, norm_buffer);
	glBufferData(GL_ARRAY_BUFFER, buf_data.data_size, buf_data.data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(attrsLoc["a_normal"]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	////////////////////////
    //indices
	// The indices array tells OpenGL what order to iterate through the buffers in when the shaders execute
	buf_data = bufferData["indices"];
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, buf_data.data_size, buf_data.data, GL_STATIC_DRAW);

	//clear the bindings
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

//here we update the modelview for the current object due to interactive transforms
mat4 Cube::updateModelView(ShaderOpts *opts) {
	mat4 modelview = opts->modelview_matrix;
	mat4 translate = Transform::translate(opts->t_x, opts->t_y, 0.);

	modelview = modelview * translate;
	modelview = modelview * Transform::scale(cubeSize, cubeSize, cubeSize);	//transform specific for Cube
	
	return modelview;
}

void Cube::draw(ShaderOpts *opts) {
    //enable our shader program
	glUseProgram(program);
	glBindVertexArray(vao);

	glm::mat4 modelview = updateModelView(opts);

	glUniformMatrix4fv(uniformsLoc["u_modelview"], 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(uniformsLoc["u_projection"], 1, GL_FALSE, &opts->projection_matrix[0][0]);
	glUniform1f(uniformsLoc["u_time"], opts->curr_time);
	glUniform1f(uniformsLoc["u_opacity"], opts->opacity);

	GLfloat lightposn_transformed[4*opts->nlights];
	for (int i=0; i < opts->nlights; i++) {
		 transformvec(opts->modelview_matrix, &opts->lightposn[i * 4], &lightposn_transformed[i * 4]);
	}

	glUniform1i(uniformsLoc["u_nlights"], opts->nlights);
	glUniform4fv(uniformsLoc["u_lightposn"], opts->nlights, (GLfloat *)lightposn_transformed);
	glUniform4fv(uniformsLoc["u_lightcolor"], opts->nlights, (GLfloat *)opts->lightcolors);
	glUniform4fv(uniformsLoc["u_ambient"], 1, (GLfloat *)material_ambient);
	glUniform4fv(uniformsLoc["u_diffuse"], 1, (GLfloat *)material_diffuse);
	glUniform4fv(uniformsLoc["u_specular"], 1, (GLfloat *)material_specular);
	glUniform4fv(uniformsLoc["u_emission"], 1, (GLfloat *)material_emission);
	glUniform1f(uniformsLoc["u_shininess"], material_shininess);

	//draw the triangle
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 vertices to form 12 triangles for 1 cube
	
#ifndef EMSCRIPTEN
	checkGLErrors("After draw");
#endif
	
	glBindVertexArray(0);
}