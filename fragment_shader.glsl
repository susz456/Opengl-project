#version 120

varying vec4 pixelColor;
varying vec4 interpolatedColor;

varying vec2 iTexCoords;

uniform sampler2D textureMap;
uniform float tex_on;

void main(void){
  if (tex_on==0){
    gl_FragColor=interpolatedColor;//vec4(1.0,0.0,1.0,1.0);//texture2D(textureMap0, iTexCoords);//
  }
  else{
    gl_FragColor=texture2D(textureMap, iTexCoords);
  }

}
