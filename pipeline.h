/* 
 * Class Pipeline used to initialize
 * the transformations required for an openGL application 
 */

#include "math_3d.h"

#ifndef PIPELINE_H
#define PIPELINE_H

class Pipeline{
 public:
 Pipeline() : 
    m_Scale(1.0f, 1.0f, 1.0f),
    m_Translation(0.0f,0.0f,0.0f),
    m_Rotation(0.0f,0.0f,0.0f){};
  void setScaleTransform(float x, float y, float z);
  void setTranslationTransform(float x, float y, float z);
  void setRotationTransform(float x, float y, float z);
  void setPerspectiveTransform(float FOV, 
			       float Width, float Height, 
			       float zNear, float zFar);
  Matrix4f getTransform() const;
 private:
  Vector3f m_Scale,m_Translation,m_Rotation;
  struct Persp_Data{
    float FOV,width,height,zNear,zFar;
  } m_Perspective;
  
  

};

#endif /* PIPELINE_H */
