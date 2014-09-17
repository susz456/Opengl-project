#version 120

varying vec4 pixelColor;
varying vec4 interpolatedColor;
varying vec4 l;
varying vec4 n;
varying vec4 v;
varying vec2 iTexCoords;
varying vec4 ShadowCoord;

uniform sampler2D textureMap;
uniform sampler2D depthTexture;
uniform float tex_on;

void main(void){
  vec4 ml=normalize(l);
  vec4 mn=normalize(n);
  vec4 mv=normalize(v);

  float nl=max(dot(ml,mn),0);

  if (tex_on==0){
    gl_FragColor=interpolatedColor*vec4(nl,nl,nl,1);//vec4(1.0,0.0,1.0,1.0);//texture2D(textureMap0, iTexCoords);//
  }
  else{
    gl_FragColor=texture2D(textureMap, iTexCoords)*vec4(nl,nl,nl,1);
  }

}
/*
void main(){
  vec4 shadowCoordinate=ShadowCoord/ShadowCoord.w;
  shadowCoordinate.z += 0.0005;
  float distanceFromLight=texture2D(depthTexture, shadowCoordinate.st).z;

  float shadow =1.0;
  if (ShadowCoord.w>0.0)
    shadow=distanceFromLight<shadowCoordinate.z ? 0.5 : 1.0;
  //gl_FragColor=shadow*interpolatedColor;
  if (tex_on==0){
    gl_FragColor=shadow*interpolatedColor;//*vec4(nl,nl,nl,1);//vec4(1.0,0.0,1.0,1.0);//texture2D(textureMap0, iTexCoords);//
  }
  else{
    gl_FragColor=shadow*texture2D(textureMap, iTexCoords);//*vec4(nl,nl,nl,1);
  }

}
  */
