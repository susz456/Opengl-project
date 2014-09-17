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

vec4 lightPosition=vec4(0.0, 50.0, 0.01, 1.0);//pozycja zrodla swiatla
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
float camera_z=0;

GLuint *model_vertices;
GLuint *model_texCoords;
vector<mesh_M> loaded, model;
mesh_M moj;
GLuint bufV;
float *vert;
float *coords;
GLuint tex0;
GLuint bufTexCoords;
GLfloat mtl_on;
GLfloat tex_on;

GLuint depthTexture;
GLuint Framebuffer=0;


void generateShadowFBO(){
  glGenTextures(1, &depthTexture);
  glBindTexture(GL_TEXTURE_2D, depthTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenFramebuffersEXT(1, &Framebuffer);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, Framebuffer);

  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTexture, 0);


  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cout<<"Blad FBO"<<endl;
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);


  vec3 lightInvDir = vec3(0.5f, 2, 2);

  mat4 depthP=ortho<float>(-10,10,-10,10,-10,20);
  mat4 depthM=lookAt(lightInvDir,vec3(0,0,0),vec3(0,1,0));
  mat4 depthV=mat4(1.0);
  mat4 depthMVP=depthP*depthV*depthM;

  glUniformMatrix4fv(shaderProgram->getUniformLocation("depthMVP"), 1, GL_FALSE, &depthMVP[0][0]);

  glUniform1i(shaderProgram->getUniformLocation("depthMap"),0);
}



void shadowMapping(){
  //GLuint Framebuffer=0;
  glGenFramebuffers(1, &Framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);

  //GLuint depthTexture;
  glGenTextures(1, &depthTexture);
  glBindTexture(GL_TEXTURE_2D, depthTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowX, windowY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

cout<<"sru"<<endl;
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture,0);
  cout<<"sru 2"<<endl;
  glDrawBuffer(GL_NONE);

 // if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
   // return false;
   

  vec3 lightInvDir = vec3(0.5f, 2, 2);

  mat4 depthP=matP;//ortho<float>(-10,10,-10,10,-10,20);
  mat4 depthM=lookAt(lightInvDir,vec3(0,0,0),vec3(0,1,0));
  mat4 depthV=mat4(1.0);
  mat4 depthMVP=depthP*depthV*depthM;

  glUniformMatrix4fv(shaderProgram->getUniformLocation("depthMVP"), 1, GL_FALSE, value_ptr(depthMVP));


}


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
    case 'q':
      camera_z++;
      break;
    case 'e':
      camera_z--;
      break;
  }
}

void specialKeyDown(int c, int x, int y){
  switch(c){
    case GLUT_KEY_LEFT:
      move_x+=0.1;
      break;
    case GLUT_KEY_RIGHT:
      move_x-=0.1;
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
  //assignVBOtoAttribute("color", pColors, 4);
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
  vecZ=vec3(move_x-10,14.0f,move_y);
  matM=translate(matM, vecZ);
  //matM=scale(matM, vec3(0.02,0.02,0.02));

  glUniformMatrix4fv(shaderProgram->getUniformLocation("M"), 1, false, value_ptr(matM));

  drawMesh(model);

  glBindVertexArray(0);
}

void displayFrame(){
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matP=perspective(cameraAngle, (float)windowWidth/(float)windowHeight, 1.0f, 100.0f);//kat, stosunek szer/dl, granica dolna odkad widac obraz, granica gorna (odleglosc od kamery)

  matV=lookAt(vec3(camera_x, camera_y, camera_z), vec3(0.0f, 0.0f, 60.0f), vec3(0.0f, 1.0f, 0.0f));

  matM=rotate(mat4(1.0f), angle, vec3(0, 1, 0));
  //matV=matV+mat4(0.0,0.0,0.0,move_x,0.0,0.0,0.0,move_y,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
  drawObject();

  glutSwapBuffers();
}

void nextFrame(void){
  //if(move_x>20) move_x=20;
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
  //pVertices=makeBuffer(pvertices, platformVertexCount, sizeof(float)*4);
  //pColors=makeBuffer(pcolors, platformVertexCount, sizeof(float)*4);

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
