#include <stdio.h>
#include "GL/glew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtc/type_ptr.hpp"
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
float CAMERA_ANGLE = 40.0f;

float ANGLE = 0;

char * AUTO_MODEL_DIR = "models/auto.obj";
char * AUTO_MATERIAL_DIR = "models/auto.mtl";
char * TRACK_MODEL_DIR = "models/trasa.obj";
char * TRACK_MATERIAL_DIR = "models/trasa.mtl";

ShaderProgram *shaderProgram;

GLuint vao;
GLuint bufVertices;
GLuint bufColors;
GLuint bufNormals;

//GLuint pVertices;
//GLuint pColors;

mat4 matP; //rzutowania
mat4 matV; //widoku
mat4 matM; //modelu
vec3 vecZ; //wektor przesuniecia przy wduszeniu strzalek

vec4 lightPosition = vec4(0.1, 3.0, -3.0, 1.0); //pozycja zrodla swiatla
vec3 carLightPosition = vec3(0.0, 2.0, 0.0);
vec3 carLightDirection = vec3(0.0, 0.05, 1.0);

Camera * globalCamera;
Engine * globalEngine;

GLuint *model_vertices;
GLuint *model_texCoords;
vector<mesh_M> loaded, model;
GLuint bufV;
float *vert;
float *coords;
GLuint tex0;
GLuint bufTexCoords;
GLfloat mtl_on;
GLfloat tex_on;
