#version 120

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat4 Z;
uniform vec4 lPos;
uniform vec3 color_vec;
uniform float mtl_on;
uniform mat4 depthMVP;

attribute vec4 vertex;
attribute vec4 color;
attribute vec4 normal;
attribute vec2 texCoords;

varying vec2 iTexCoords;
varying vec4 interpolatedColor;
varying vec4 l;
varying vec4 n;
varying vec4 v;
varying vec4 ShadowCoord;


void main(void){
  l=normalize(V*(lPos-M*vertex));
  n=normalize(V*M*normal);
  v=normalize(vec4(0,0,0,1)-V*M*vertex);
  if (mtl_on==1){
    interpolatedColor=vec4(color_vec,1.0);
  }
  else{
    interpolatedColor=color;
  }
  gl_Position=P*V*M*vertex;
  iTexCoords=texCoords;
}
/*
void main(void){
  //interpolatedColor=vec4(0.8,0.3,0.7,1.0);//color;
  ShadowCoord=depthMVP*vertex;
  gl_Position=depthMVP*vertex;
  //gl_Position=P*V*M*vertex;
  iTexCoords=texCoords;
}*/
