#version 120

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lPos;
//uniform vec3 carLightPos;
//uniform vec3 carLightDir;
uniform vec3 color_vec;
uniform float mtl_on;

attribute vec4 vertex;
attribute vec4 normal;
attribute vec2 texCoords;

varying vec2 iTexCoords;
varying vec4 interpolatedColor;
varying vec4 l;
varying vec4 n;
varying vec4 v;

void main(void){
  l=normalize(V*(lPos-M*vertex));
  n=normalize(V*M*normal);
  v=normalize(vec4(0,0,0,1)-V*M*vertex);

  if (mtl_on==1){
    interpolatedColor=vec4(color_vec,1.0);
  }
  
  gl_Position=P*V*M*vertex;
  iTexCoords=texCoords;
}
