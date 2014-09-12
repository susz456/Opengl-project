#include <stdio.h>
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include "cube.h"
#include "platform.h"
#include "shaderprogram.h"
#include "parser.h"
#include "tga.h"
#include <vector>


using namespace glm;
using namespace std;

int windowWidth=600;
int windowHeight=600;
int windowX=100;
int windowY=100;
float cameraAngle=60.0f;


float angle=0;

ShaderProgram *shaderProgram;

GLuint vao;
GLuint bufVertices;
GLuint bufColors;
GLuint bufNormals;

GLuint pVertices;
GLuint pColors;

mat4 matP;//rzutowania
mat4 matV;//widoku
mat4 matM;//modelu
vec3 vecZ;//wektor przesuniecia przy wduszeniu strzalek

vec3 lightPosition=vec3(0.0, 20.0, -5.0);//pozycja zrodla swiatla
//float *vertices=verticesAvent;
//float *vertices=cubeVertices;
//float *colors=cubeColors;
//float *normals=cubeNormals;
//int vertexCount=10;//98237 cubeVertexCount;

float *pvertices=platformVertices;
float *pcolors=platformColors;

float move_x=0;
float move_y=0;

float camera_x=0;
float camera_y=0;

GLuint *model_vertices;
GLuint *model_texCoords;
vector<mesh_M> loaded;
mesh_M moj;
GLuint bufV;
float *vert;
float *coords;
GLuint tex0;
GLuint bufTexCoords;
GLfloat mtl_on;
GLfloat tex_on;


void keyDown(unsigned char c, int x, int y){
  switch(c){
    case 'a':
      camera_x++;
      break;
    case 'd':
      camera_x--;
      break;
    case 'w':
      camera_y++;
      break;
    case 's':
      camera_y--;
      break;
  }
}

void specialKeyDown(int c, int x, int y){
  switch(c){
    case GLUT_KEY_LEFT:
      move_x-=0.1;
      break;
    case GLUT_KEY_RIGHT:
      move_x+=0.1;
      break;
    case GLUT_KEY_UP:
      move_y+=0.1;
      break;
    case GLUT_KEY_DOWN:
      move_y-=0.1;
      break;
  }
}

void changeSize(int w, int h){
  glViewport(0, 0, w, h);
  windowWidth=w;
  windowHeight=h;
}

void assignVBOtoAttribute(char* attributeName, GLuint bufVBO, int variableSize){
  GLuint location=shaderProgram->getAttribLocation(attributeName);
  glBindBuffer(GL_ARRAY_BUFFER, bufVBO);
  glEnableVertexAttribArray(location);
  glVertexAttribPointer(location, variableSize, GL_FLOAT, GL_FALSE, 0, NULL);
}


void drawObject(){
  shaderProgram->use();
  glBindVertexArray(vao);

  //platforma
  assignVBOtoAttribute("vertex", pVertices, 4);
  assignVBOtoAttribute("color", pColors, 4);
  //
  glUniform4fv(shaderProgram->getUniformLocation("lPos"), 1, value_ptr(lightPosition));//pozycja zrodla swiatla

  glUniformMatrix4fv(shaderProgram->getUniformLocation("P"), 1, false, value_ptr(matP));
  glUniformMatrix4fv(shaderProgram->getUniformLocation("V"), 1, false, value_ptr(matV));
  glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));
  
  mtl_on=0;
  tex_on=0;
  glUniform1f(shaderProgram->getUniformLocation("mtl_on"),  mtl_on);//zmienna dla shadera, sprawdza skad brac kolor
  glUniform1f(shaderProgram->getUniformLocation("tex_on"),  tex_on);//czy textury wlaczone
  

  glDrawArrays(GL_TRIANGLES, 0, platformVertexCount);
  //
  vecZ=vec3(move_x,move_y,0.0f);
  matM=translate(matM, vecZ);

  glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));

  mtl_on=1;
  glUniform1f(shaderProgram->getUniformLocation("mtl_on"),  mtl_on);

  for(int i=0; i<loaded.size(); i++){
    assignVBOtoAttribute("vertex", model_vertices[i], 3);
    //color
    vec3 color_mtl=loaded[i].Kd+loaded[i].Ka+loaded[i].Ks;
    glUniform3fv(shaderProgram->getUniformLocation("color_vec"), 1, value_ptr(color_mtl));

    //texture
    assignVBOtoAttribute("texCoords", model_texCoords[i], 2);
    tex_on=0;
    if(loaded[i].tex){
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,loaded[i].handle);
      glUniform1i(shaderProgram->getUniformLocation("textureMap"),0);
      tex_on=1;
    }
    glUniform1f(shaderProgram->getUniformLocation("tex_on"),  tex_on);
    glDrawArrays(GL_TRIANGLES, 0, loaded[i].count*3);
  }

  glBindVertexArray(0);
}

void displayFrame(){
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matP=perspective(cameraAngle, (float)windowWidth/(float)windowHeight, 1.0f, 100.0f);//kat, stosunek szer/dl, granica dolna odkad widac obraz, granica gorna (odleglosc od kamery)

  matV=lookAt(vec3(camera_x, camera_y, 7.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

  matM=rotate(mat4(1.0f), angle, vec3(0, 1, 0));
  //matV=matV+mat4(0.0,0.0,0.0,move_x,0.0,0.0,0.0,move_y,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  drawObject();

  glutSwapBuffers();
}

void nextFrame(void){
  if(move_x>20) move_x=20;
  glutPostRedisplay();
}

GLuint makeBuffer(void* data, int vertexCount, int vertexSize){
  GLuint handle;
  glGenBuffers(1, &handle);
  glBindBuffer(GL_ARRAY_BUFFER, handle);
  glBufferData(GL_ARRAY_BUFFER, vertexCount*vertexSize, data, GL_STATIC_DRAW);

  return handle;
}

void setupVBO(){
  pVertices=makeBuffer(pvertices, platformVertexCount, sizeof(float)*4);
  pColors=makeBuffer(pcolors, platformVertexCount, sizeof(float)*4);

  for(int i=0; i<loaded.size(); i++){
    model_vertices[i]=makeBuffer(&(loaded[i]).w[0], loaded[i].count*3, sizeof(float)*3);
    model_texCoords[i]=makeBuffer(&(loaded[i]).tc[0], loaded[i].count*3, sizeof(float)*2);
  }
  //cout<<"Size of loaded: "<<loaded.size()<<endl;
}


void setupVAO(){
  glGenVertexArrays(1,&vao);
  glBindVertexArray(vao);

  //assignVBOtoAttribute("vertex", bufVertices, 4);
  //assignVBOtoAttribute("color", bufColors, 4);
  //assignVBOtoAttribute("normal", bufNormals, 4);

  //assignVBOtoAttribute("texCoords", bufTexCoords, 2);

  glBindVertexArray(0);
}

void setupShaders(){
  shaderProgram=new ShaderProgram("vertex_shader.glsl", NULL, "fragment_shader.glsl");
}

void initOpenGL(){
  setupShaders();
  setupVBO();
  setupVAO();
  glEnable(GL_DEPTH_TEST);
}

void initGLEW(){
  GLenum err=glewInit();
  if (GLEW_OK!=err){
    fprintf(stderr, "%s\n", glewGetErrorString(err));
    exit(1);
  }
}

void initGLUT(int* argc, char** argv){
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(windowX, windowY);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("Test");

  glutDisplayFunc(displayFrame);
  glutIdleFunc(nextFrame);
  glutReshapeFunc(changeSize);

  glutSpecialFunc(specialKeyDown);
  glutKeyboardFunc(keyDown);
}


int main(int argc, char** argv){
  bool a;
  initGLUT(&argc, argv);
  initGLEW();
  loaded=loadObj(argv[1], argv[2]);
  model_vertices= new GLuint[loaded.size()];
  model_texCoords= new GLuint[loaded.size()];


  initOpenGL();

  glutMainLoop();

  return 0;
}
