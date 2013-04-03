/* Utility classes for openGL operations */

#ifndef MATH_3D_H
#define MATH_3D_H

#include <math.h>


#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f/ M_PI)


struct Vector3f{
  float x,y,z;
  Vector3f(){};
  Vector3f(float xx,float yy, float zz): x(xx),y(yy),z(zz){};
};


/* Class Matrix4f stores a 4x4 square matrix containing
 * transformation values.
 * Can be initialized to be an identity matrix (no change happens when
 * multiplying with a vector) a rotation matrix( rotates by the specified angles
 * in degrees on the 3 axis) a scaling matrix(also in the 3 directions) or a 
 * perspective projection matrix.
 */
class Matrix4f{
 public:
  float mat[4][4];
  void InitIdentity();
  void InitScaleMatrix(float scaleX,float scaleY, float scaleZ);
  void InitRotationMatrix(float angleX, float angleY, float angleZ);
  void InitTranslationMatrix(float transX,float transY,float transZ);
  void InitPerspectiveMatrix(float FOV, float width, float height,
			    float zNear, float zFar);
  Matrix4f operator*(const Matrix4f &right) const;
};

#endif /* MATH_3D_H */
