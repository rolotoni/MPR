/////////////////////////////////////////////////////////////
// File  : Matrix.cpp                                      //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Matrix Math                                     //
/////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "Matrix.h"
#include "BasicMath.h"

#define DEG_TO_RAD PI/180.0f

namespace Framework
{
  Vec3 Mtx44MultPoint(Vec3 pt, Mtx44 Mtx)
  {
  Vec4 temp(pt.x,pt.y, pt.z,1);
  temp = Mtx44MultPoint(temp,Mtx);
  return Vec3(temp.x,temp.y,temp.z);

  }

  Vec4 Mtx44MultPoint(Vec4 pt, Mtx44 Mtx)
  {
    Vec4 new_point;

  new_point.x = ((Mtx.m[0][0] * pt.x) + (Mtx.m[0][1] * pt.y) + (Mtx.m[0][2] * pt.z) + (Mtx.m[0][3] * pt.w));
  new_point.y = ((Mtx.m[1][0] * pt.x) + (Mtx.m[1][1] * pt.y) + (Mtx.m[1][2] * pt.z) + (Mtx.m[1][3] * pt.w));
  new_point.z = ((Mtx.m[2][0] * pt.x) + (Mtx.m[2][1] * pt.y) + (Mtx.m[2][2] * pt.z) + (Mtx.m[2][3] * pt.w));
  new_point.w = ((Mtx.m[3][0] * pt.x) + (Mtx.m[3][1] * pt.y) + (Mtx.m[3][2] * pt.z) + (Mtx.m[3][3] * pt.w));
  
  return new_point;
  }


  void Mtx44RotRadZ(Mtx44 *pResult, float angle)
  {
   
     angle *= DEG_TO_RAD; //convert to radians

     Mtx44Identity(pResult);

     pResult->m[0][0] = cos(angle);
     pResult->m[0][1] = -(sin(angle));
     pResult->m[1][0] = sin(angle);
     pResult->m[1][1] = cos(angle);

  }

  void Mtx44RotRadX(Mtx44 *pResult, float angle)
  {
   
     angle *= DEG_TO_RAD; //convert to radians

     Mtx44Identity(pResult);

     pResult->m[1][1] = cos(angle);
     pResult->m[1][2] = -(sin(angle));
     pResult->m[2][1] = sin(angle);
     pResult->m[2][2] = cos(angle);

  }

  void Mtx44RotRadY(Mtx44 *pResult, float angle)
  {
   
     angle *= DEG_TO_RAD; //convert to radians

     Mtx44Identity(pResult);

     pResult->m[0][0] = cos(angle);
     pResult->m[0][2] = sin(angle);
     pResult->m[2][0] = -(sin(angle));
     pResult->m[2][2] = cos(angle);

  }

  void Mtx44Trans(Mtx44 *pResult, float x, float y, float z)
  {
    Mtx44Identity(pResult);

    pResult->m[0][3] = x;
    pResult->m[1][3] = y;
    pResult->m[2][3] = z;
  }


  void Mtx44Scale(Mtx44 *pResult, float x, float y, float z)
  {
    Mtx44Identity(pResult);

    pResult->m[0][0] = x;
    pResult->m[1][1] = y;
    pResult->m[2][2] = z;

  }

  void Mtx44Identity(Mtx44 *pResult)
  {

    int pos1;
    int pos2;
    /*matrix size*/
      int row = 4;
    int col = 4;

    for(pos2 = 0; pos2 < row; pos2++)
    {
         for(pos1 = 0; pos1 < col; pos1++)
     {
       if(pos1 == pos2)
          pResult->m[pos1][pos2] = 1;
       else
        pResult->m[pos1][pos2] = 0;
     }
    }

  }

  void Mtx44Concat(Mtx44 *pResult, Mtx44 *pMtx0, Mtx44 *pMtx1)
  {
    //position in the matrix
    int pos1;
    int pos2;
    int i;

    Mtx44 temp;

    for(pos2 = 0; pos2 < 4; pos2++)
       for(pos1 = 0; pos1 < 4; pos1++)
       temp.m[pos1][pos2] = 0;
   
  
     for(i = 0; i < 4; i++)
       for(pos2 = 0; pos2 < 4; pos2++)
         for(pos1 = 0; pos1 < 4; pos1++)
         temp.m[i][pos2] += pMtx0->m[i][pos1] * pMtx1->m[pos1][pos2];

     for(pos2 = 0; pos2 < 4; pos2++)
       for(pos1 = 0; pos1 < 4; pos1++)
       pResult->m[pos1][pos2] = temp.m[pos1][pos2];


  }

  void Mtx44Add(Mtx44 *pResult, Mtx44 *pMtx0, Mtx44 *pMtx1)
  {
    Mtx44 temp;

    int pos1;
    int pos2;

    for(pos2 = 0; pos2 < 4; pos2++)
      for(pos1 = 0; pos1 < 4; pos1++)
      temp.m[pos1][pos2] = pMtx0->m[pos1][pos2] + pMtx1->m[pos1][pos2];


    for(pos2 = 0; pos2 < 4; pos2++)
      for(pos1 = 0; pos1 < 4; pos1++)
      pResult->m[pos1][pos2] = temp.m[pos1][pos2];


  }

  //turn matrix into perspective matrix to
  //project vertexes onto the projection plane
  void Mtx44Perspective(Mtx44 *pResult, float focal_d)
  {

    int pos1;
    int pos2;
    /*matrix size*/
      int row = 4;
    int col = 4;

    for(pos2 = 0; pos2 < row; pos2++)
    {
         for(pos1 = 0; pos1 < col; pos1++)
     {
       if(pos1 == pos2)
       {
         if(pos1 == row - 1)
               pResult->m[pos1][pos2] = 0;
       else
             pResult->m[pos1][pos2] = focal_d;
       }
       else
        pResult->m[pos1][pos2] = 0;
     }
    }

    //what axis are we projecting onto
    pResult->m[3][2] = -1; //-z

       
  }

  Mtx44 Mtx44Rotate(Vec3 &n, float angle)
  {
    Mtx44 m;

  angle *= DEG_TO_RAD;

    m.m[0][0] = cos(angle) + (1 - cos(angle)) * n.x * n.x;
    m.m[0][1] = -sin(angle) * n.z + (1 - cos(angle)) * n.x * n.y;
    m.m[0][2] = sin(angle) * n.y + (1 - cos(angle)) * n.x * n.z;
    m.m[0][3] = 0;

    m.m[1][0] = sin(angle) * n.z + (1 - cos(angle)) * n.x * n.y;
    m.m[1][1] = cos(angle) + (1 - cos(angle)) * n.y * n.y;
    m.m[1][2] = -sin(angle) * n.x + (1 - cos(angle)) * n.z * n.y;
    m.m[1][3] = 0;

    m.m[2][0] = -sin(angle) * n.y + (1 - cos(angle)) * n.x * n.z;
    m.m[2][1] = sin(angle) * n.x + (1 - cos(angle)) * n.z * n.y;
    m.m[2][2] = cos(angle) + (1 - cos(angle)) * n.z * n.z;
    m.m[2][3] = 0;

    m.m[3][0] = 0;
    m.m[3][1] = 0;
    m.m[3][2] = 0;
    m.m[3][3] = 1;

    return m;

  }

  void Mtx44Transpose(Mtx44 *pResult, Mtx44 *pMtx0)
  {
  Mtx44 m;
  //make copy of pMtx0 in case result is itself
  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
      m.m[i][j] = pMtx0->m[i][j];

  for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
      pResult->m[i][j] = m.m[j][i];
  }

  void Mtx44ToArray(float a[16], Mtx44 *In)
  {
    for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
        a[(4 * j) + i] = In->m[i][j];  
  }

  void ArrayToMtx44(float* a, Mtx44 *pResult)
  {
    for(int i = 0; i < 4; ++i)
    for(int j = 0; j < 4; ++j)
        pResult->m[i][j] = a[(4 * j) + i]; 
  }

  std::ostream& operator<<(std::ostream& os, const Mtx44& mtx)
  {
     //specify how to print a mtx
     os << "`|" << mtx.m[0][0] << mtx.m[0][1] << mtx.m[0][2] << mtx.m[0][3] << "| " << std::endl;
     os << " |" << mtx.m[1][0] << mtx.m[1][1] << mtx.m[1][2] << mtx.m[1][3] << "| " << std::endl;
     os << " |" << mtx.m[2][0] << mtx.m[2][1] << mtx.m[2][2] << mtx.m[2][3] << "| " << std::endl;
     os << " |" << mtx.m[3][0] << mtx.m[3][1] << mtx.m[3][2] << mtx.m[3][3] << "|," << std::endl;

     // returns a reference to the ostream
     return os;    
  }

  void Mtx44Inverse(Mtx44 *pMtx0, Mtx44 *pResult)
  {
    float det;
    int i;
  float v[16], ar[16];

  Mtx44ToArray(v, pMtx0);
  

  ar[0] = v[5]  * v[10] * v[15] - 
             v[5]  * v[11] * v[14] - 
             v[9]  * v[6]  * v[15] + 
             v[9]  * v[7]  * v[14] +
             v[13] * v[6]  * v[11] - 
             v[13] * v[7]  * v[10];

    ar[4] = -v[4]  * v[10] * v[15] + 
              v[4]  * v[11] * v[14] + 
              v[8]  * v[6]  * v[15] - 
              v[8]  * v[7]  * v[14] - 
              v[12] * v[6]  * v[11] + 
              v[12] * v[7]  * v[10];

    ar[8] = v[4]  * v[9] * v[15] - 
             v[4]  * v[11] * v[13] - 
             v[8]  * v[5] * v[15] + 
             v[8]  * v[7] * v[13] + 
             v[12] * v[5] * v[11] - 
             v[12] * v[7] * v[9];

    ar[12] = -v[4]  * v[9] * v[14] + 
               v[4]  * v[10] * v[13] +
               v[8]  * v[5] * v[14] - 
               v[8]  * v[6] * v[13] - 
               v[12] * v[5] * v[10] + 
               v[12] * v[6] * v[9];

    ar[1] = -v[1]  * v[10] * v[15] + 
              v[1]  * v[11] * v[14] + 
              v[9]  * v[2] * v[15] - 
              v[9]  * v[3] * v[14] - 
              v[13] * v[2] * v[11] + 
              v[13] * v[3] * v[10];

    ar[5] = v[0]  * v[10] * v[15] - 
             v[0]  * v[11] * v[14] - 
             v[8]  * v[2] * v[15] + 
             v[8]  * v[3] * v[14] + 
             v[12] * v[2] * v[11] - 
             v[12] * v[3] * v[10];

    ar[9] = -v[0]  * v[9] * v[15] + 
              v[0]  * v[11] * v[13] + 
              v[8]  * v[1] * v[15] - 
              v[8]  * v[3] * v[13] - 
              v[12] * v[1] * v[11] + 
              v[12] * v[3] * v[9];

    ar[13] = v[0]  * v[9] * v[14] - 
              v[0]  * v[10] * v[13] - 
              v[8]  * v[1] * v[14] + 
              v[8]  * v[2] * v[13] + 
              v[12] * v[1] * v[10] - 
              v[12] * v[2] * v[9];

    ar[2] = v[1]  * v[6] * v[15] - 
             v[1]  * v[7] * v[14] - 
             v[5]  * v[2] * v[15] + 
             v[5]  * v[3] * v[14] + 
             v[13] * v[2] * v[7] - 
             v[13] * v[3] * v[6];

    ar[6] = -v[0]  * v[6] * v[15] + 
              v[0]  * v[7] * v[14] + 
              v[4]  * v[2] * v[15] - 
              v[4]  * v[3] * v[14] - 
              v[12] * v[2] * v[7] + 
              v[12] * v[3] * v[6];

    ar[10] = v[0]  * v[5] * v[15] - 
              v[0]  * v[7] * v[13] - 
              v[4]  * v[1] * v[15] + 
              v[4]  * v[3] * v[13] + 
              v[12] * v[1] * v[7] - 
              v[12] * v[3] * v[5];

    ar[14] = -v[0]  * v[5] * v[14] + 
               v[0]  * v[6] * v[13] + 
               v[4]  * v[1] * v[14] - 
               v[4]  * v[2] * v[13] - 
               v[12] * v[1] * v[6] + 
               v[12] * v[2] * v[5];

    ar[3] = -v[1] * v[6] * v[11] + 
              v[1] * v[7] * v[10] + 
              v[5] * v[2] * v[11] - 
              v[5] * v[3] * v[10] - 
              v[9] * v[2] * v[7] + 
              v[9] * v[3] * v[6];

    ar[7] = v[0] * v[6] * v[11] - 
             v[0] * v[7] * v[10] - 
             v[4] * v[2] * v[11] + 
             v[4] * v[3] * v[10] + 
             v[8] * v[2] * v[7] - 
             v[8] * v[3] * v[6];

    ar[11] = -v[0] * v[5] * v[11] + 
               v[0] * v[7] * v[9] + 
               v[4] * v[1] * v[11] - 
               v[4] * v[3] * v[9] - 
               v[8] * v[1] * v[7] + 
               v[8] * v[3] * v[5];

    ar[15] = v[0] * v[5] * v[10] - 
              v[0] * v[6] * v[9] - 
              v[4] * v[1] * v[10] + 
              v[4] * v[2] * v[9] + 
              v[8] * v[1] * v[6] - 
              v[8] * v[2] * v[5];

    det = v[0] * ar[0] + v[1] * ar[4] + v[2] * ar[8] + v[3] * ar[12];

  //fail
    //if (det == 0)
    //{
    //}

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
        ar[i] *= det;

    ArrayToMtx44(ar, pResult);

}

}//namespace

