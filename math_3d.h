/* Utility classes for openGL operations */

#ifndef MATH_3D_H
#define MATH_3D_H

#include <math.h>


#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f/ M_PI)


class Matrix4f{
 public:
  float mat[4][4];
  void InitIdentity();
  void InitScaleMatrix(float scaleX,float scaleY, float scaleZ);
  void InitRotationMatrix(float angleX, float angleY, float angleZ);
  void InitTranslationMatrix(float transX,float transY,float transZ);
  Matrix4f operator*(const Matrix4f &right) const;
};

#endif /* MATH_3D_H */
