/////////////////////////////////////////////////////////////
// File  : Matrix.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Matrix Math                                     //
/////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

namespace Framework
{
  struct Mtx44
  {
    float m[4][4];
  };

  Mtx44 Mtx44Rotate(Vec3 &n, float angle);

  Vec3 Mtx44MultPoint(Vec3 pt, Mtx44 Mtx);

  Vec4 Mtx44MultPoint(Vec4 pt, Mtx44 Mtx);

  void Mtx44RotRadX(Mtx44 *pResult, float angle);

  void Mtx44RotRadY(Mtx44 *pResult, float angle);

  void Mtx44RotRadZ(Mtx44 *pResult, float angle);

  void Mtx44Trans(Mtx44 *pResult, float x, float y, float z);

  void Mtx44Scale(Mtx44 *pResult, float x, float y, float z);

  void Mtx44Identity(Mtx44 *pResult);

  void Mtx44Concat(Mtx44 *pResult, Mtx44 *pMtx0, Mtx44 *pMtx1);

  void Mtx44Perspective(Mtx44 *pResult, float focal_d);

  void Mtx44Add(Mtx44 *pResult, Mtx44 *pMtx0, Mtx44 *pMtx1);

  void Mtx44Transpose(Mtx44 *pResult, Mtx44 *pMtx0);

  void Mtx44ToArray(float* a, Mtx44 *In);

  void ArrayToMtx44(float* a, Mtx44 *pResult);

  double Mtx44determinant(const Mtx44* m);
  void Mtx44Inverse(Mtx44 *pMtx0, Mtx44 *pResult);

  std::ostream& operator<<(std::ostream& os, const Mtx44& mtx); 

}//namespace


#endif