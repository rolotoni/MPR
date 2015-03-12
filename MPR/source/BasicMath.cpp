/////////////////////////////////////////////////////////////
// File  : Math.cpp                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : CS350 Framework Math implementations            //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "BasicMath.h"
#include "Camera.h"

namespace Framework
{
  ////////////////////////////////Vec2/////////////////////////////
  Vec2::Vec2(float i, float j)
  {
    x = i;
    y = j;
  }

  // ---------------------------------------------------------------------------
  Vec2::Vec2(const Vec2 & p1, const Vec2 & p2)
  {
    this->x = p1.x - p2.x;
    this->y = p1.y - p2.y;
  }

  // ---------------------------------------------------------------------------
  Vec2::Vec2(Vec2 &rhs)
  {
    this->x = rhs.x;
    this->y = rhs.y;
  }

  // ---------------------------------------------------------------------------
  bool Vec2::IsZero(void) const
  {
    return (x == 0.0f) && (y == 0.0f);
  }

  // ---------------------------------------------------------------------------
  void Vec2::Zero(void)
  {
    x = 0.0f;
    y = 0.0f;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Abs(void)
  {
    x = fabsf(x);
    y = fabsf(y);
  }

  // ---------------------------------------------------------------------------
  void Vec2::Set(float xy)
  {
    x = y = xy;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Set(float i, float j)
  {
    x = i;
    y = j;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Negate(void)
  {
    x = -x;
    y = -y;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Inverse(void)
  {
    x = 1.0f/x;
    y = 1.0f/y;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Normalize(void)
  {
    float mag = this->Magnitude();
    x /= mag;
    y /= mag;
  }

  // ---------------------------------------------------------------------------
  void Vec2::Multiply(const Vec2 &v)
  {
    x *= v.x;
    y *= v.y;
  }

  // ---------------------------------------------------------------------------
  float Vec2::Magnitude(void) const
  {
    return sqrt((x*x) + (y*y));
  }

  // ---------------------------------------------------------------------------
  float Vec2::InvMagnitude(void) const
  {
    return 1.0f / this->Magnitude();
  }

  // ---------------------------------------------------------------------------
  float Vec2::MagSqrd(void) const
  {
    return this->Dot(*this);
  }

  // ---------------------------------------------------------------------------
  float Vec2::Dot(const Vec2 &v) const
  {
    return (this->x * v.x) + (this->y * v.y);
  }

  // ---------------------------------------------------------------------------
  float Vec2::Cross2D(const Vec2 &v) const
  {
    return (this->x * v.y) - (this->y * v.x);
  }

  // ---------------------------------------------------------------------------
  const Vec2& Vec2::operator=(const Vec2 &v) 
  {
    this->x = v.x;
    this->y = v.y;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec2& Vec2::operator+=(const Vec2 &v)
  {
    this->x += v.x;
    this->y += v.y;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec2& Vec2::operator-=(const Vec2 &v)
  {
    this->x -= v.x;
    this->y -= v.y;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec2& Vec2::operator*=(const float scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec2& Vec2::operator/=(const float scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  bool Vec2::operator==(const Vec2 &v) const
  {
    if(((this->x - v.x) > Epsilon) || ((this->x - v.x) < -Epsilon))
      return false;
    else if(((this->y - v.y) > Epsilon) || ((this->y - v.y) < -Epsilon))
    return false;

    return true;
  }

  // ---------------------------------------------------------------------------
  bool Vec2::operator!=(const Vec2 &v) const
  {
    if(*this == v)
      return false;
    else
    return true;
  }

  // ---------------------------------------------------------------------------
  Vec2 Vec2::operator+(const Vec2 &v) const
  {
    Vec2 temp(this->x + v.x, this->y + v.y);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec2 Vec2::operator-(const Vec2 &v) const
  {
    Vec2 temp(this->x - v.x, this->y - v.y);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec2 Vec2::operator*(const float scalar) const
  {
    Vec2 temp(this->x * scalar, this->y * scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec2 Vec2::operator/(const float scalar) const
  {
    Vec2 temp(this->x / scalar, this->y / scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec2 operator*(float scalar, const Vec2 & rhs)
  {
    Vec2 lhs;
    lhs.x = rhs.x * scalar;
    lhs.y = rhs.y * scalar;
    return lhs;
  }

  // ---------------------------------------------------------------------------
    Vec2 operator/(float scalar, const Vec2 & rhs)
  {
    Vec2 lhs;
    lhs.x = rhs.x / scalar;
    lhs.y = rhs.y / scalar;
    return lhs;
  }
  
    ////////////////////////////////Vec3/////////////////////////////
  Vec3::Vec3(float i, float j, float k)
  {
    x = i;
    y = j;
    z = k;
  }

  // ---------------------------------------------------------------------------
  Vec3::Vec3(const Vec3 & p1, const Vec3 & p2)
  {
    this->x = p1.x - p2.x;
    this->y = p1.y - p2.y;
    this->z = p1.z - p2.z;
  }

    // ---------------------------------------------------------------------------
  Vec3::Vec3(const Vec3 &rhs)
  {
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
  }

  // ---------------------------------------------------------------------------
  bool Vec3::IsZero(void) const
  {
    return ((x < Epsilon && x > -Epsilon) &&
          (y < Epsilon && y > -Epsilon) &&
          (z < Epsilon && z > -Epsilon));
  }

  // ---------------------------------------------------------------------------
  void Vec3::Zero(void)
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Abs(void)
  {
    x = fabsf(x);
    y = fabsf(y);
    z = fabsf(z);
  }

  // ---------------------------------------------------------------------------
  void Vec3::Set(float xyz)
  {
    x = y = z = xyz;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Set(float i, float j, float k)
  {
    x = i;
    y = j;
    z = k;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Negate(void)
  {
    x = -x;
    y = -y;
    z = -z;
  }
  // ---------------------------------------------------------------------------
    Vec3 Vec3::Neg(void)
  {
    Vec3 v;
    v.x = -x;
    v.y = -y;
    v.z = -z;
    return v;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Inverse(void)
  {
    x = 1.0f/x;
    y = 1.0f/y;
    z = 1.0f/z;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Normalize(void)
  {
    float mag = this->Magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Norm(Vec3 *vOut) const
  {
    float mag = this->Magnitude();
    vOut->x =  x/mag;
    vOut->y =  y/mag;
    vOut->z =  z/mag;
  }

  // ---------------------------------------------------------------------------
  void Vec3::Multiply(const Vec3 &v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
  }

  // ---------------------------------------------------------------------------
  float Vec3::Magnitude(void) const
  {
    return sqrt((x*x) + (y*y) + (z*z));
  }

  // ---------------------------------------------------------------------------
  float Vec3::InvMagnitude(void) const
  {
    return 1.0f / this->Magnitude();
  }

  // ---------------------------------------------------------------------------
  float Vec3::MagSqrd(void) const
  {
    return this->Dot(*this);
  }

  // ---------------------------------------------------------------------------
  float Vec3::Dot(const Vec3 &v) const
  {
    return (x * v.x) + (y * v.y) + (z * v.z);
  }

  // ---------------------------------------------------------------------------
  void Vec3::Cross(const Vec3 &rhs, Vec3 *vOut) const
  {
      vOut->x = y * rhs.z - z * rhs.y;
    vOut->y = z * rhs.x - x * rhs.z;
    vOut->z = x * rhs.y - y * rhs.x;
  }

  // ---------------------------------------------------------------------------
  const Vec3& Vec3::operator=(const Vec3 &v) 
  {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec3& Vec3::operator+=(const Vec3 &v)
  {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec3& Vec3::operator-=(const Vec3 &v)
  {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec3& Vec3::operator*=(const float scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec3& Vec3::operator/=(const float scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  bool Vec3::operator==(const Vec3 &v) const
  {
    if(((this->x - v.x) > Epsilon) || ((this->x - v.x) < -Epsilon))
      return false;
    else if(((this->y - v.y) > Epsilon) || ((this->y - v.y) < -Epsilon))
    return false;
    else if(((this->z - v.z) > Epsilon) || ((this->z - v.z) < -Epsilon))
    return false;

    return true;
  }

  // ---------------------------------------------------------------------------
  bool Vec3::operator!=(const Vec3 &v) const
  {
    if(*this == v)
      return false;
    else
    return true;
  }
  // ---------------------------------------------------------------------------
  bool Vec3::operator<(const Vec3 & v) const
  {
    if(this->x <= v.x && this->y <= v.y && this->z <= v.z)
      return true;

    return false;
  }
  // ---------------------------------------------------------------------------
  bool Vec3::operator>(const Vec3 & v) const
  {
    if(this->x >= v.x && this->y >= v.y && this->z >= v.z)
      return true;

    return false;
  }
  // ---------------------------------------------------------------------------
  Vec3 Vec3::operator+(const Vec3 &v) const
  {
    Vec3 temp(this->x + v.x, this->y + v.y, this->z + v.z);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec3 Vec3::operator-(const Vec3 &v) const
  {
    Vec3 temp(this->x - v.x, this->y - v.y, this->z - v.z);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec3 Vec3::operator*(const float scalar) const
  {
    Vec3 temp(this->x * scalar, this->y * scalar, this->z * scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec3 Vec3::operator/(const float scalar) const
  {
    Vec3 temp(this->x / scalar, this->y / scalar, this->z / scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec3 operator*(float scalar, const Vec3 & rhs)
  {
    Vec3 lhs;
    lhs.x = rhs.x * scalar;
    lhs.y = rhs.y * scalar;
    lhs.z = rhs.z * scalar;
    return lhs;
  }

  // ---------------------------------------------------------------------------
    Vec3 operator/(float scalar, const Vec3 & rhs)
  {
    Vec3 lhs;
    lhs.x = rhs.x / scalar;
    lhs.y = rhs.y / scalar;
    lhs.z = rhs.z / scalar;
    return lhs;
  }

  ////////////////////////////////Vec4/////////////////////////////
  Vec4::Vec4(float i, float j, float k, float f)
  {
    x = i;
    y = j;
    z = k;
    w = f;
  }

  // ---------------------------------------------------------------------------
  Vec4::Vec4(const Vec4 & p1, const Vec4 & p2)
  {
    this->x = p1.x - p2.x;
    this->y = p1.y - p2.y;
    this->z = p1.z - p2.z;
    this->w = p1.w - p2.w;
  }

    // ---------------------------------------------------------------------------
  Vec4::Vec4(const Vec4 &rhs)
  {
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    this->w = rhs.w;
  }

  // ---------------------------------------------------------------------------
  bool Vec4::IsZero(void) const
  {
    return ((x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f));
  }

  // ---------------------------------------------------------------------------
  void Vec4::Zero(void)
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Abs(void)
  {
    x = fabsf(x);
    y = fabsf(y);
    z = fabsf(z);
    w = fabsf(w);
  }

  // ---------------------------------------------------------------------------
  void Vec4::Set(float xyzw)
  {
    x = y = z = w = xyzw;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Set(float i, float j, float k, float f)
  {
    x = i;
    y = j;
    z = k;
    w = f;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Negate(void)
  {
    x = -x;
    y = -y;
    z = -z;
    w = -w;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Inverse(void)
  {
    x = 1.0f/x;
    y = 1.0f/y;
    z = 1.0f/z;
    w = 1.0f/w;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Normalize(void)
  {
    float mag = this->Magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Norm(Vec4 *vOut) const
  {
    float mag = this->Magnitude();
    vOut->x =  x/mag;
    vOut->y =  y/mag;
    vOut->z =  z/mag;
    vOut->w =  w/mag;
  }

  // ---------------------------------------------------------------------------
  void Vec4::Multiply(const Vec4 &v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
  }

  // ---------------------------------------------------------------------------
  float Vec4::Magnitude(void) const
  {
    return sqrt((x*x) + (y*y) + (z*z) + (w*w));
  }

  // ---------------------------------------------------------------------------
  float Vec4::InvMagnitude(void) const
  {
    return 1.0f / this->Magnitude();
  }

  // ---------------------------------------------------------------------------
  float Vec4::MagSqrd(void) const
  {
    return this->Dot(*this);
  }

  // ---------------------------------------------------------------------------
  float Vec4::Dot(const Vec4 &v) const
  {
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z) + (this->w * v.w);
  }

  // ---------------------------------------------------------------------------
  const Vec4& Vec4::operator=(const Vec4 &v) 
  {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.z;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec4& Vec4::operator+=(const Vec4 &v)
  {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    this->w += v.w;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec4& Vec4::operator-=(const Vec4 &v)
  {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    this->w -= v.w;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec4& Vec4::operator*=(const float scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  const Vec4& Vec4::operator/=(const float scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
  }

  // ---------------------------------------------------------------------------
  bool Vec4::operator==(const Vec4 &v) const
  {
    if(((this->x - v.x) > Epsilon) || ((this->x - v.x) < -Epsilon))
      return false;
    else if(((this->y - v.y) > Epsilon) || ((this->y - v.y) < -Epsilon))
    return false;
    else if(((this->z - v.z) > Epsilon) || ((this->z - v.z) < -Epsilon))
    return false;
    else if(((this->w - v.w) > Epsilon) || ((this->w - v.w) < -Epsilon))
    return false;

    return true;
  }

  // ---------------------------------------------------------------------------
  bool Vec4::operator!=(const Vec4 &v) const
  {
    if(*this == v)
      return false;
    else
    return true;
  }

  // ---------------------------------------------------------------------------
  Vec4 Vec4::operator+(const Vec4 &v) const
  {
    Vec4 temp(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec4 Vec4::operator-(const Vec4 &v) const
  {
    Vec4 temp(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec4 Vec4::operator*(const float scalar) const
  {
    Vec4 temp(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec4 Vec4::operator/(const float scalar) const
  {
    Vec4 temp(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
    return temp;
  }

  // ---------------------------------------------------------------------------
  Vec4 operator*(float scalar, const Vec4 & rhs)
  {
    Vec4 lhs;
    lhs.x = rhs.x * scalar;
    lhs.y = rhs.y * scalar;
    lhs.z = rhs.z * scalar;
    lhs.w = rhs.w * scalar;
    return lhs;
  }

  // ---------------------------------------------------------------------------
    Vec4 operator/(float scalar, const Vec4 & rhs)
  {
    Vec4 lhs;
    lhs.x = rhs.x / scalar;
    lhs.y = rhs.y / scalar;
    lhs.z = rhs.z / scalar;
    lhs.w = rhs.w / scalar;
    return lhs;
  }

  ////////////////////////////////Segment3D/////////////////////////////
  Seg3D::Seg3D(void)
  {
  }

  // ---------------------------------------------------------------------------
  Seg3D::Seg3D(const Vec3 &q1, const Vec3 &q2)
  {
    p1 = q1;
    p2 = q2;
  }

  // ---------------------------------------------------------------------------
  bool Seg3D::operator==(const Seg3D &rhs)
  {
    Vec3 temp0(p1 - p2);
    Vec3 temp1(rhs.p1 - rhs.p2);
    temp0.Abs();
    temp1.Abs();
    return temp1 == temp0;
  }

  // ---------------------------------------------------------------------------
  void Seg3D::Set(const Vec3 &q1, const Vec3 &q2)
  {
    p1 = q1;
    p2 = q2;
  }
  ////////////////////////////////Ray3D/////////////////////////////
  Ray3D::Ray3D(void)
  {
  }

  Ray3D::Ray3D(Vec3 o, Vec3 d)
  {
    origin = o;
    dir = d;
  }

  // ---------------------------------------------------------------------------
  void Ray3D::Set(const Vec3 &point, const Vec3 &direction)
  {
    origin = point;
    dir = direction;
  }

  ////////////////////////////////Line3D/////////////////////////////
  Line3D::Line3D()
  {
  }
  
  // ---------------------------------------------------------------------------
  Line3D::Line3D(Vec3 p, Vec3 d)
  {
    pp = p;
    dir = d;
  }

  // ---------------------------------------------------------------------------
  void Line3D::Set(const Vec3 &point, const Vec3 &direction)
  {
    pp = point;
    dir = direction;
  }

  ////////////////////////////////Plane3D/////////////////////////////
  Plane3D::Plane3D(void)
  {
  }

  // ---------------------------------------------------------------------------
  Plane3D::Plane3D(const Vec3 &planeNormal, const Vec3 &p)
  {
    n = planeNormal;
    pp = p;
  }

  // ---------------------------------------------------------------------------
  void Plane3D::Set(float nx, float ny, float nz, const Vec3 &p)
  {
    n.x = nx;
    n.y = ny;
    n.z = nz;
    pp = p;
    d = -n.Dot(pp);
  }

  // ---------------------------------------------------------------------------
  void Plane3D::Set(const Vec3 &planeNormal, const Vec3 &p)
  {
    n = planeNormal;
    pp = p;
    d = -n.Dot(pp);
  }

  // ---------------------------------------------------------------------------
  void Plane3D::Set(const Vec3 &p0, const Vec3 &p1, const Vec3 &p2)
  {
    (p2 - p1).Cross((p2 - p0), &n);
     pp = p2;
     d = -n.Dot(pp);
  }

  ////////////////////////////////Triangle/////////////////////////////
  Triangle::Triangle(void)
  {
  }

  // ---------------------------------------------------------------------------
  Triangle::Triangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2)
  {
    p0 = v0;
    p1 = v1;
    p2 = v2;
  }

  // ---------------------------------------------------------------------------
  void Triangle::Set(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2)
  {
    p0 = v0;
    p1 = v1;
    p2 = v2;
  }

  ////////////////////////////////Sphere/////////////////////////////
  Sphere::Sphere(void)
  {
  }

  // ---------------------------------------------------------------------------
  Sphere::Sphere(float r, const Vec3 &c)
  {
    radius = r;
    center = c;
  }

  // ---------------------------------------------------------------------------
  void Sphere::Set(float r, const Vec3 &c)
  {
    radius = r;
    center = c;
  }

  // ---------------------------------------------------------------------------
  float Sphere::RadiusSqrd(void) const
  {
    return radius * radius;
  }

  ////////////////////////////////AABB/////////////////////////////
  AABB::AABB(void)
  {
  }

  // ---------------------------------------------------------------------------
  AABB::AABB(const Vec3 &r, const Vec3 &c)
  {
    radii = r;
    center = c;
  }

  // ---------------------------------------------------------------------------
  void AABB::Set(const Vec3 &r, const Vec3 &c)
  {
    radii = r;
    center = c;
  }

  // ---------------------------------------------------------------------------
  void AABB::MinMax(Vec3 *minOut, Vec3 *maxOut) const
  {
    minOut->x = this->center.x - this->radii.x;
      minOut->y = this->center.y - this->radii.y;
      minOut->z = this->center.z - this->radii.z;
    maxOut->x = this->center.x + this->radii.x;
      maxOut->y = this->center.y + this->radii.y;
      maxOut->z = this->center.z + this->radii.z;
  }

  Vec3 AABB::GetVertex(int point)
  {
    Vec3 maxOut, minOut;
    this->MinMax(&minOut, &maxOut);
    
    switch(point)
    {
      case 0:
      return minOut;
    case 1:
    {
      minOut.x += (this->radii.x * 2);
      return minOut;
    }
    case 2:
    {
      minOut.y += (this->radii.y * 2);
      return minOut;
    }
    case 3:
    {
      minOut.z += (this->radii.z * 2);
      return minOut;
    }
    case 4:
    {
      minOut.z += (this->radii.z * 2);
      minOut.y += (this->radii.y * 2);
      return minOut;
    }
    case 5:
    {
      minOut.z += (this->radii.z * 2);
      minOut.x += (this->radii.x * 2);
      return minOut;
    }
    case 6:
    {
      maxOut.z -= (this->radii.z * 2);
      return maxOut;
    }
    case 7:
      return maxOut;
    }

    return minOut;
  }

  ////////////////////////////////Portal/////////////////////////////
  Portal::Portal(void)
  {
  }

  void Portal::DrawPortal(void)
  {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(-300, 300, -300, 300);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
    glScalef(1,1,.01f);
    glTranslatef(-150,-150,0);
    glRotatef(CAMERA->Phi, 1, 0, 0);
    glRotatef(CAMERA->Theta, 0, 1, 0);
      
      Vec3 verts[9];
      verts[0] = center;
      verts[1] = p1;
      verts[2] = p2;
      verts[3] = p3;
      glEnableClientState(GL_VERTEX_ARRAY);
      glColor3f(0,0,1);
      glPointSize(7.0f);
      glVertexPointer(3, GL_FLOAT, 0, verts);
      glDrawArrays(GL_POINTS, 0, 1);
      glColor3f(1, 1, 1);
      glDrawArrays(GL_POINTS, 1, 3);

      //c, v1, c, v2, c, v3, v1, v2, v3
      verts[0] = center;
      verts[1] = p1;
      verts[2] = center;
      verts[3] = p2;
      verts[4] = center;
      verts[5] = p3;
      verts[6] = p1;
      verts[7] = p2;
      verts[8] = p3;
      glColor3f(1,0,0);
      glVertexPointer(3, GL_FLOAT, 0, verts);
      glDrawArrays(GL_LINE_STRIP, 0, 6);
      glColor3f(0,1,0);
      glDrawArrays(GL_LINE_STRIP, 5, 4);

    verts[0] = center;
      verts[1] = Vec3();
    glColor3f(1,0,1);
      glDrawArrays(GL_LINE_STRIP, 0, 2);
      glDisableClientState(GL_VERTEX_ARRAY);

  }

}//namespace