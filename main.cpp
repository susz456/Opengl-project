#include "GlobalVariables.h"

void keypressWrapper(unsigned char c, int x, int y) {
	globalCamera->action(c, x, y);
}

void keypressWrapper(int c, int x, int y) {
	globalEngine->action(c, x, y);
}

void changeSize(int w, int h) {
	glViewport(0, 0, w, h);
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;
}

void assignVBOtoAttribute(char* attributeName, GLuint bufVBO,
		int variableSize) {
	GLuint location = shaderProgram->getAttribLocation(attributeName);
	glBindBuffer(GL_ARRAY_BUFFER, bufVBO);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL);
}

void drawMesh(vector<mesh_M> &mesh){
  
  mtl_on=1;
  glUniform1f(shaderProgram->getUniformLocation("mtl_on"),  mtl_on);

  for(int i=0; i<mesh.size(); i++){
    assignVBOtoAttribute("vertex", mesh[i].vertices, 4);
    assignVBOtoAttribute("normal", mesh[i].normals, 4);
    //color
    vec3 color_mtl=mesh[i].Kd;//+mesh[i].Ka+mesh[i].Ks;
    //cout<<"kd "<<loaded[i].Kd.x<<endl;
    glUniform3fv(shaderProgram->getUniformLocation("color_vec"), 1, value_ptr(color_mtl));

    //texture
    assignVBOtoAttribute("texCoords", mesh[i].texCoords, 2);
    tex_on=0;
    if(mesh[i].tex){
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,mesh[i].handle);
      glUniform1i(shaderProgram->getUniformLocation("textureMap"),0);
      tex_on=1;
    }
    glUniform1f(shaderProgram->getUniformLocation("tex_on"),  tex_on);
    glDrawArrays(GL_TRIANGLES, 0, mesh[i].count*3);
  }
}


void drawObject(){
  shaderProgram->use();
  glBindVertexArray(vao);
//cout<<"camera "<<camera_x<<" "<<camera_y<<" "<<camera_z<<endl;
  //platforma
  //assignVBOtoAttribute("vertex", pVertices, 4);
  assignVBOtoAttribute("color", pColors, 4);
  //
  glUniform4fv(shaderProgram->getUniformLocation("lPos"), 1, value_ptr(lightPosition));//pozycja zrodla swiatla


  matM=scale(matM, vec3(10.0,10.0,10.0));

  glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(matP));
  glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(matV));
  glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));
  
  //mtl_on=0;
  //tex_on=0;
  //glUniform1f(shaderProgram->getUniformLocation("mtl_on"),  mtl_on);//zmienna dla shadera, sprawdza skad brac kolor
  //glUniform1f(shaderProgram->getUniformLocation("tex_on"),  tex_on);//czy textury wlaczone
  drawMesh(loaded);

  //glDrawArrays(GL_TRIANGLES, 0, platformVertexCount);
  matM=scale(matM, vec3(0.04,0.04,0.04));
  vecZ=vec3(globalEngine->X-10,globalEngine->Y+14,globalEngine->Z);
  matM=translate(matM, vecZ);
  //matM=scale(matM, vec3(0.02,0.02,0.02));

  glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));

  drawMesh(model);

  glBindVertexArray(0);
}

void displayFrame() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	matP = perspective(CAMERA_ANGLE,
			(float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 1.0f, 100.0f); //kat, stosunek szer/dl, granica dolna odkad widac obraz, granica gorna (odleglosc od kamery)

	matV = lookAt(vec3(globalCamera->X-4, globalCamera->Y+7, -5.0f),
			vec3(0.0f, 0.0f, 60.0f), vec3(0.0f, 1.0f, 0.0f));

	matM = rotate(mat4(1.0f), ANGLE, vec3(0, 1, 0));
	//matV=matV+mat4(0.0,0.0,0.0,move_x,0.0,0.0,0.0,move_y,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	drawObject();

	glutSwapBuffers();

}

void nextFrame(void) {
	glutPostRedisplay();
}

GLuint makeBuffer(void* data, int vertexCount, int vertexSize) {
	GLuint handle;
	glGenBuffers(1, &handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * vertexSize, data,
	GL_STATIC_DRAW);

	return handle;
}

float color [] = {1.0f, 0.0f, 0.0f, 1.0f};
void setupVBO(){
  //pVertices=makeBuffer(pvertices, platformVertexCount, sizeof(float)*4);

  pColors=makeBuffer(color, 1, sizeof(float));

  for(int i=0; i<loaded.size(); i++){
    loaded[i].vertices=makeBuffer(&(loaded[i]).w[0], loaded[i].count*3, sizeof(float)*4);
    loaded[i].normals=makeBuffer(&(loaded[i]).n[0], loaded[i].count*3, sizeof(float)*4);
    loaded[i].texCoords=makeBuffer(&(loaded[i]).tc[0], loaded[i].count*3, sizeof(float)*2);
  }

  for(int i=0; i<model.size(); i++){
    model[i].vertices=makeBuffer(&(model[i]).w[0], model[i].count*3, sizeof(float)*4);
    model[i].normals=makeBuffer(&(model[i]).n[0], model[i].count*3, sizeof(float)*4);
    model[i].texCoords=makeBuffer(&(model[i]).tc[0], model[i].count*3, sizeof(float)*2);
  }
  //cout<<"Size of loaded: "<<loaded.size()<<endl;
}

void setupVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//assignVBOtoAttribute("vertex", bufVertices, 4);
	//assignVBOtoAttribute("color", bufColors, 4);
	//assignVBOtoAttribute("normal", bufNormals, 4);

	//assignVBOtoAttribute("texCoords", bufTexCoords, 2);

	glBindVertexArray(0);
}

void setupShaders() {
	shaderProgram = new ShaderProgram("vertex_shader.glsl", NULL,
			"fragment_shader.glsl");
}

void initOpenGL() {
	setupShaders();
	setupVBO();
	setupVAO();
	glEnable(GL_DEPTH_TEST);
}

void initGLEW() {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "%s\n", glewGetErrorString(err));
		exit(1);
	}
}

void initGLUT(int* argc, char** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Test");

	glutDisplayFunc(displayFrame);
	glutIdleFunc(nextFrame);
	glutReshapeFunc(changeSize);

	glutSpecialFunc(keypressWrapper);
	glutKeyboardFunc(keypressWrapper);
}


int main(int argc, char** argv){
	globalEngine = new Engine();
	globalCamera = new Camera();
  initGLUT(&argc, argv);
  initGLEW();
  model=loadObj("auto.obj", "auto.mtl");
  loaded=loadObj("trasa.obj", "trasa.mtl");
  //loaded.vertices= new GLuint[loaded.size()];
  //loaded.texCoords= new GLuint[loaded.size()];


  initOpenGL();
  //generateShadowFBO();
  //shadowMapping();

	glutMainLoop();

	return 0;
}
