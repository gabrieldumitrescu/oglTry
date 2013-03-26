/* math_3d implementation */

#include "math_3d.h"

void Matrix4f::InitIdentity(){
  mat[0][0]=1.0f; mat[0][1]=0.0f; mat[0][2]=0.0f; mat[0][3]=0.0f;
  mat[1][0]=0.0f; mat[1][1]=1.0f; mat[1][2]=0.0f; mat[1][3]=0.0f;
  mat[2][0]=0.0f; mat[2][1]=0.0f; mat[2][2]=1.0f; mat[2][3]=0.0f;
  mat[3][0]=0.0f; mat[3][1]=0.0f; mat[3][2]=0.0f; mat[3][3]=0.0f;
}
void Matrix4f::InitScaleMatrix(float scaleX,float scaleY, float scaleZ){
  InitIdentity();
  mat[0][0]=scaleX;
  mat[1][1]=scaleY;
  mat[2][2]=scaleZ;
}

void Matrix4f::InitRotationMatrix(float angleX, float angleY, float angleZ){
  Matrix4f rx,ry,rz;
  rx.InitIdentity();
  ry.InitIdentity();
  rz.InitIdentity();
  
  const float x=ToRadian(angleX);
  const float y=ToRadian(angleY);
  const float z=ToRadian(angleZ);

  
  rx.mat[1][1]=cosf(x); rx.mat[1][2]=-sinf(x);
  rx.mat[2][1]=sinf(x); rx.mat[2][2]=cosf(x);

  ry.mat[0][0]=cosf(y); ry.mat[0][2]=-sinf(y);
  ry.mat[2][0]=sinf(y); ry.mat[2][2]=cosf(y);

  rz.mat[0][0]=cosf(z); rz.mat[0][2]=-sinf(z);
  rz.mat[1][0]=sinf(z); rz.mat[1][2]=cosf(z);

  *this=rz*ry*rx;
  
}
 
void Matrix4f::InitTranslationMatrix(float transX,float transY,float transZ){
    InitIdentity();
    mat[0][3]=transX;
    mat[1][3]=transY;
    mat[2][3]=transZ;
}

Matrix4f Matrix4f::operator*(const Matrix4f &right) const{
  Matrix4f res;
  for(unsigned int i=0;i<4; ++i)
    for(unsigned int j=0;j<4; ++j)
      res.mat[i][j]= mat[i][0] * right.mat[0][j]+
	mat[i][1] * right.mat[1][j]+
	mat[i][2] * right.mat[2][j]+
	mat[i][3] * right.mat[3][j];
  return res;
}
