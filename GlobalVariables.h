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
#include "core/Camera.h"
#include "core/Engine.h"

using namespace glm;
using namespace std;

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;
int WINDOW_X = 100;
int WINDOW_Y = 100;
float CAMERA_ANGLE = 60.0f;

float ANGLE = 0;

ShaderProgram *shaderProgram;

GLuint vao;
GLuint bufVertices;
GLuint bufColors;
GLuint bufNormals;

GLuint pVertices;
GLuint pColors;

mat4 matP; //rzutowania
mat4 matV; //widoku
mat4 matM; //modelu
vec3 vecZ; //wektor przesuniecia przy wduszeniu strzalek

vec3 lightPosition = vec3(0.0, 20.0, -5.0); //pozycja zrodla swiatla
//float *vertices=verticesAvent;
//float *vertices=cubeVertices;
//float *colors=cubeColors;
//float *normals=cubeNormals;
//int vertexCount=10;//98237 cubeVertexCount;

float *pvertices = platformVertices;
float *pcolors = platformColors;

Camera * globalCamera;
Engine * globalEngine;

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
