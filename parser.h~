#include <iostream>
#include <fstream>
#include <string>
#include "/glm/glm.hpp"
#include "/glm/gtc/matrix_transform.hpp"
#include "/glm/gtc/type_ptr.hpp"
#include <vector>
#include "tga.h"

using namespace std;
using namespace glm;

struct mesh_M{
  vector<vec4> w;
  vector<vec4> n;
  vector<vec2> tc;
  string material;
  bool tex;
  GLuint handle;
  float Ns;
  vec3 Ka;
  vec3 Kd;
  vec3 Ks;
  float Ni;
  int count;
  GLuint vertices;
  GLuint normals;
  GLuint texCoords;
};

struct mtl{
  string name="none";
  float Ns=1;
  vec3 Ka=vec3(1.0,1.0,1.0);
  vec3 Kd=vec3(1.0,1.0,1.0);
  vec3 Ks=vec3(1.0,1.0,1.0);
  float Ni=1;
  string map_Kd;
  bool tex=false;
  GLuint handle;
};

int find_mtl(string material, vector<mtl> mtl_vector){
  int result=-1;
  for(int i=0; i<mtl_vector.size();i++){
    if (mtl_vector[i].name==material){
      result=i;
      //cout<<i<<endl;
      break;
    }
  }
  //cout<<"result "<<result<<" "<<material<<endl;
  return result;
}

GLuint readTexture(char* filename) {
  GLuint tex;
  TGAImg img;
  glActiveTexture(GL_TEXTURE0);
  if (img.Load(filename)==IMG_OK) {
    glGenTextures(1,&tex); //Zainicjuj uchwyt tex
    glBindTexture(GL_TEXTURE_2D,tex); //Przetwarzaj uchwyt tex
    if (img.GetBPP()==24) //Obrazek 24bit
      glTexImage2D(GL_TEXTURE_2D,0,3,img.GetWidth(),img.GetHeight(),0,
          GL_RGB,GL_UNSIGNED_BYTE,img.GetImg());
    else if (img.GetBPP()==32) //Obrazek 32bit
      glTexImage2D(GL_TEXTURE_2D,0,4,img.GetWidth(),img.GetHeight(),0,
          GL_RGBA,GL_UNSIGNED_BYTE,img.GetImg());
    else {
      printf("Nieobs¿ugiwany format obrazka w pliku: %s \n",filename);
    }
  } else {
    printf("Blad przy wczytywaniu pliku: %s\n; %d",filename, img.Load(filename));
  }
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
  return tex;
}


vector<mtl> loadMtl(char* pliczek){
  vector<mtl> result;
  ifstream plik;
  bool first_mtl=true;
  mtl tmp, clear_tmp;
  plik.open(pliczek, ios::in);
  if (plik.good()==true){
    cout<<"Uzyskano dostep do pliku mtl"<<endl;
    while(plik.good()){
      string znak;
      plik >> znak;

      if(znak=="newmtl"){
        if(first_mtl) first_mtl=false;
        else{
          result.push_back(tmp);
          tmp=clear_tmp;
        }
        plik >> tmp.name;
      }
      else if(znak=="Ns"){ 
        plik >> tmp.Ns;
      }
      else if(znak=="Ka"){
        plik >> tmp.Ka.x >> tmp.Ka.y >> tmp.Ka.z;
      }
      else if(znak=="Kd"){
        plik >> tmp.Kd.x >> tmp.Kd.y >> tmp.Kd.z;
      }
      else if(znak=="Ks"){
        plik >> tmp.Ks.x >> tmp.Ks.y >> tmp.Ks.z;
      }
      else if(znak=="Ni"){
        plik >> tmp.Ni;
      }
      else if(znak=="map_Kd"){
        plik >> tmp.map_Kd;
      }

    }

    result.push_back(tmp);
  }
  return result;
}




void stringSplit(string &text, char separator, vector<string> &substrings){
  size_t sepPosition=text.find(separator);
  if (sepPosition==string::npos){
    cout << "Brak separatora" << endl;
    return;
  }
  string tmp=text;
  do{
    substrings.push_back(tmp.substr(0,sepPosition));
    tmp=tmp.substr(sepPosition+1);
    sepPosition=tmp.find(separator, 0);
  } while(sepPosition !=string::npos);
  substrings.push_back(tmp);
}


vector<mesh_M> loadObj(char* file_obj, char* file_mtl){//(char* pliczek, vector<mtl> mtl_vector){
  ifstream plik;
  bool face_flag = false;
  bool face_flag2 = false;
  //bool first_o = true;
  vector<mesh_M> result;
  plik.open(file_obj, ios::in);
  if (plik.good()==true){
    cout<<"Uzyskano dostep do pliku"<<endl;
    vector<vec3> tempVertices;
    vector<vec3> tempNormals;
    vector<vec2> tempTexCoords;
    vector<vec3> vertexIndieces;
    vector<vec3> normalsIndieces;
    vector<vec3> texCoordsIndieces;
    string material, material2;
    while(true){
      string znak;
      plik >> znak;
      face_flag=false;
      material2=material;
      if (znak == "v"){
        float a, b, c;
        plik >> a >> b >> c;
        vec3 tmp=vec3(a, b, c);
        tempVertices.push_back(tmp);
      }
      else if (znak == "vn"){
        float a, b, c;
        plik >> a >> b >> c;
        vec3 tmp=vec3(a, b, c);
        tempNormals.push_back(tmp);
      }
      else if (znak == "f"){
        float a, b, c;
        char separator='/';
        string sa, sb, sc;
        vector<string> substrings_a, substrings_b, substrings_c;
        face_flag=true;
        face_flag2=true;
        bool is_vt=false;
        plik >> sa >> sb >> sc;
        stringSplit(sa, separator, substrings_a);
        stringSplit(sb, separator, substrings_b);
        stringSplit(sc, separator, substrings_c);
        //vector<string>::iterator it;
        if (substrings_a[0].empty()) a=0;
        else a=(float)atof(substrings_a[0].c_str());
        if (substrings_b[0].empty()) b=0;
        else b=(float)atof(substrings_b[0].c_str());
        if (substrings_c[0].empty()) c=0;
        else c=(float)atof(substrings_c[0].c_str());
        vec3 tmpVec=vec3(a, b, c);
        vertexIndieces.push_back(tmpVec);
        //
        if (substrings_a[1].empty()) a=0;
        else{
          //cout<<"is_vt"<<endl;
          a=(float)atof(substrings_a[1].c_str());
          is_vt=true;
        }
        if (substrings_b[1].empty()) b=0;
        else b=(float)atof(substrings_b[1].c_str());
        if (substrings_c[1].empty()) c=0;
        else c=(float)atof(substrings_c[1].c_str());
        tmpVec=vec3(a, b, c);
        if (is_vt) texCoordsIndieces.push_back(tmpVec);
        //
        if (substrings_a[2].empty()) a=0;
        else a=(float)atof(substrings_a[2].c_str());
        if (substrings_b[2].empty()) b=0;
        else b=(float)atof(substrings_b[2].c_str());
        if (substrings_c[2].empty()) c=0;
        else c=(float)atof(substrings_c[2].c_str());
        tmpVec=vec3(a, b, c);
        normalsIndieces.push_back(tmpVec);
      }
      else if (znak == "vt"){
        float a, b;
        plik >> a >> b;
        vec2 tmp = vec2(a, -b);
        tempTexCoords.push_back(tmp);
      }
      else if (znak=="usemtl"){
        plik >> material;
        if (material2.empty()) material2=material;

      }
      if (((!face_flag)&&face_flag2)||!plik.good()){
        face_flag2=false;
        mesh_M part;
        vec4 tmpVec;
        vec4 tmpNor;
        vec2 tmpTex;
        vector<vec3>::iterator it;
        //cout<<"face"<<endl;
        for (it=vertexIndieces.begin(); it!=vertexIndieces.end(); ++it){
          tmpVec=vec4(tempVertices[(*it).x-1].x, tempVertices[(*it).x-1].y, tempVertices[(*it).x-1].z,1.0);
          part.w.push_back(tmpVec);

          tmpVec=vec4(tempVertices[(*it).y-1].x, tempVertices[(*it).y-1].y, tempVertices[(*it).y-1].z,1.0);
          part.w.push_back(tmpVec);

          tmpVec=vec4(tempVertices[(*it).z-1].x, tempVertices[(*it).z-1].y, tempVertices[(*it).z-1].z,1.0);
          part.w.push_back(tmpVec);
        }
        //cout<<"po vertexIndieces"<<endl;
        //
        //for(it=texCoordsIndieces.end(); it!=texCoordsIndieces.begin();it--){
        for(it=texCoordsIndieces.begin(); it!=texCoordsIndieces.end(); ++it){
          tmpTex=vec2(tempTexCoords[(*it).x-1].x, tempTexCoords[(*it).x-1].y);
          part.tc.push_back(tmpTex);

          tmpTex=vec2(tempTexCoords[(*it).y-1].x, tempTexCoords[(*it).y-1].y);
          part.tc.push_back(tmpTex);

          tmpTex=vec2(tempTexCoords[(*it).z-1].x, tempTexCoords[(*it).z-1].y);
          part.tc.push_back(tmpTex);
        }
        //cout<<"Po texcoordsindieces"<<endl;
        //
        for(it=normalsIndieces.begin(); it!=normalsIndieces.end(); ++it){
          tmpNor=vec4(tempNormals[(*it).x-1].x, tempNormals[(*it).x-1].y, tempNormals[(*it).x-1].z,0.0);
          part.n.push_back(tmpNor);

          tmpNor=vec4(tempNormals[(*it).y-1].x, tempNormals[(*it).y-1].y, tempNormals[(*it).y-1].z,0.0);
          part.n.push_back(tmpNor);

          tmpNor=vec4(tempNormals[(*it).z-1].x, tempNormals[(*it).z-1].y, tempNormals[(*it).z-1].z,0.0);
          part.n.push_back(tmpNor);
        }
        //cout<<"po normalsindieces"<<endl;
        //
        part.material=material2;
        part.count=vertexIndieces.size();
        result.push_back(part);
        vertexIndieces.clear();
        normalsIndieces.clear();
        texCoordsIndieces.clear();
      }


      if (!plik.good()) break;
      }
      plik.close();
    }
    else cout<<"Brak dostepu do pliku"<<endl;


    //
    vector<mtl> mtl_vector;
    mtl_vector=loadMtl(file_mtl);
    vector<mesh_M>::iterator it;
    //
    vector<mtl> tmpVecMtl;

    for(int i=0; i<mtl_vector.size(); i++){
      bool copy=false;
      for(int j=0; j<tmpVecMtl.size(); j++){
        if ((!(mtl_vector[i].map_Kd.empty()))&&(mtl_vector[i].map_Kd==tmpVecMtl[j].map_Kd)){
          //cout<<"kopiuje texture "<<mtl_vector[i].map_Kd<<endl;
          mtl_vector[i].handle=tmpVecMtl[j].handle;
          mtl_vector[i].tex=true;
          copy=true;
        } 
      } 
      if (!copy){
        if(!(mtl_vector[i].map_Kd.empty())){
          char *cstr = new char[mtl_vector[i].map_Kd.length()+1];
          strcpy(cstr, mtl_vector[i].map_Kd.c_str());
          mtl_vector[i].handle=readTexture(cstr);
          mtl_vector[i].tex=true;
          delete [] cstr;
        } 
        tmpVecMtl.push_back(mtl_vector[i]);
      }
    }
    //
    int index;
    for(it=result.begin(); it<result.end(); ++it){
      index=find_mtl((*it).material, mtl_vector);
      (*it).handle=mtl_vector[index].handle;
      (*it).tex=mtl_vector[index].tex;
      (*it).Ns=mtl_vector[index].Ns;
      (*it).Ka=mtl_vector[index].Ka;
      (*it).Kd=mtl_vector[index].Kd;
      (*it).Ks=mtl_vector[index].Ks;
      (*it).Ni=mtl_vector[index].Ni;
    }
    //
    return result;
  }
