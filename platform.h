#ifndef PLATFORM_H
#define PLATFORM_h

int platformVertexCount=6;

float platformVertices[]={
  -10.0f, -2.0f, -10.0f, 1.0f,
  -10.0f, -2.0f, 10.0f, 1.0f,
  10.0f, -2.0f, 10.0f, 1.0f,

  -10.0f, -2.0f, -10.0f, 1.0f,
  10.0f, -2.0f, -10.0f, 1.0f,
  10.0f, -2.0f, 10.0f, 1.0f
};

float platformColors[]={
  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,
  
  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f, 1.0f
};
#endif
