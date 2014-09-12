#version 120

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 Z;
uniform vec3 lPos;
uniform vec3 color_vec;
uniform float mtl_on;

attribute vec4 vertex;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texCoords;

varying vec2 iTexCoords;
varying vec4 interpolatedColor;

void main(void){
  if (mtl_on==1){
    interpolatedColor=vec4(color_vec,1.0);
  }
  else{
    interpolatedColor=color;
  }
  gl_Position=P*V*M*vertex;
  iTexCoords=texCoords;
}
