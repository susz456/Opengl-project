#version 120

varying vec4 pixelColor;
varying vec4 interpolatedColor;
varying vec4 l;
varying vec4 n;
varying vec4 v;
varying vec2 iTexCoords;

uniform sampler2D textureMap;
uniform float tex_on;

void main(void){
  vec4 ml=normalize(l);
  vec4 mn=normalize(n);
  vec4 mv=normalize(v);
  vec4 mr=reflect(-ml,mn);
  vec4 Ms=vec4(1,1,1,1);

  float shininess=40;

  float nl=max(dot(ml,mn),0);
  float rv=pow(max(dot(mr,mv),0),shininess);

  if (tex_on==0){
    gl_FragColor=interpolatedColor*vec4(nl,nl,nl,1)+Ms*vec4(rv,rv,rv,0);
  }
  else{
    gl_FragColor=texture2D(textureMap, iTexCoords)*vec4(nl,nl,nl,1)+Ms*vec4(rv,rv,rv,0);
  }

}
