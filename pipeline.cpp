/*
 * Pipeline class implementation 
 *
*/

#include "pipeline.h"

void Pipeline::setScaleTransform(float x, float y, float z){
  m_Scale.x=x;
  m_Scale.y=y;
  m_Scale.z=z;
}

void Pipeline::setTranslationTransform(float x, float y, float z){
 m_Translation.x=x;
 m_Translation.y=y;
 m_Translation.z=z;
}

void Pipeline::setRotationTransform(float x, float y, float z){
  m_Rotation.x=x;
  m_Rotation.y=y;
  m_Rotation.z=z;
}

void Pipeline::setPerspectiveTransform(float FOV, 
				       float Width, float Height, 
				       float zNear, float zFar){
  m_Perspective.FOV=FOV;
  m_Perspective.width=Width;
  m_Perspective.height=Height;
  m_Perspective.zNear=zNear;
  m_Perspective.zFar=zFar;
}

Matrix4f Pipeline::getTransform() const{
  Matrix4f res;
  Matrix4f scale,translation,rotation,perspective;
  scale.InitScaleMatrix(m_Scale.x,m_Scale.y,m_Scale.z);
  translation.InitTranslationMatrix(m_Translation.x,
				    m_Translation.y,
				    m_Translation.z);
  rotation.InitRotationMatrix(m_Rotation.x,
			      m_Rotation.y,
			      m_Rotation.z);
  perspective.InitPerspectiveMatrix(m_Perspective.FOV,
				    m_Perspective.width,m_Perspective.height,
				    m_Perspective.zNear,m_Perspective.zFar); 

  res = perspective * translation * rotation * scale;
  return res;
   
}
