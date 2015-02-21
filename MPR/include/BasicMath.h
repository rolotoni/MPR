/////////////////////////////////////////////////////////////
// File  : Math.h                                          //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : CS350 Framework Math header                     //
/////////////////////////////////////////////////////////////

#ifndef MATH_H
#define MATH_H

//includes
#include <math.h>

//defines
#define Epsilon .001f
#define PI 3.1415926535897932384626433832795f

namespace Framework
{
  //------------------------------------------------------------------------------
  template <typename T>
  inline T Clamp(T value, const T mn, const T mx)
  {
	if(value < mn)
      value = mn;
    else if(value > mx)
      value = mx;

    return value;
  }

  //------------------------------------------------------------------------------
  // forward decls

  class Vec3;
  struct Seg3D;
  struct Ray3D;
  struct Line3D;

  //------------------------------------------------------------------------------
class Vec2
{
  public:
    // default
    Vec2(float i = 0.0f, float j = 0.0f);
	Vec2(const Vec2 & p1, const Vec2 & p2);
	Vec2(Vec2 &rhs);

    /// queries: ///
    // ||this|| ?= 0
    bool IsZero(void) const;

    /// modifiers: ///
    // x, y = 0
    void Zero(void);
    // |x|, |y|
    void Abs(void);
    // x = y = xyValue
    void Set(float xyValue);
    // x = i, y = j
    void Set(float i, float j);
    // x = -x, y = -y
    void Negate(void);
    // x = 1/x, y = 1/y
    void Inverse(void);
    // this/||this||
    void Normalize(void);

    // x = x * v.x
    // y = y * v.y    [ie, 'v' is a 2D-scalar]
    void Multiply(const Vec2 & v);

    /// named operators/operations: ///
    // ||this||
    float Magnitude(void) const;
    // 1/||this||
    float InvMagnitude(void) const;
    // ||this||^2 = this * this
    float MagSqrd(void) const;
    // this * v
    float Dot(const Vec2 & v) const;
    // this ^ v
    float Cross2D(const Vec2 & v) const;

    /// assignment: ///
    const Vec2 & operator=(const Vec2 & v);
    const Vec2 & operator+=(const Vec2 & v);
    const Vec2 & operator-=(const Vec2 & v);
    const Vec2 & operator*=(const float scalar);
    const Vec2 & operator/=(const float scalar);
    /// epsilon comparisons: ///
    bool operator==(const Vec2 & v) const;
    bool operator!=(const Vec2 & v) const;
    // binary: ///
    Vec2 operator+(const Vec2 & v) const;
    Vec2 operator-(const Vec2 & v) const;
    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;

	friend Vec2 operator*(float scalar, const Vec2 & rhs);
    friend Vec2 operator/(float scalar, const Vec2 & rhs);

  public:
    float x, y;

  private:
    Vec2 operator-(void);  // unary negation not allowed, use named function: 'Negate'
};

//------------------------------------------------------------------------------
class Vec3
{
  public:
    Vec3(float i = 0.0f, float j = 0.0f, float k = 0.0f);
	Vec3(const Vec3 & p1, const Vec3 & p2);
    Vec3(const Vec3& rhs);

    /// queries: ///
    bool IsZero(void) const;

    // modifications to *this or output of modified *this
    void Zero(void);
    void Abs(void);
    void Set(float xyzValue);
    void Set(float i, float j, float k);
    void Negate(void);
	Vec3 Neg(void);
    void Inverse(void);
    void Normalize(void);
	void Norm(Vec3 *vOut) const;
    void Multiply(const Vec3 & v);

    // ||this||
    float Magnitude(void) const;
    // 1/||this||
    float InvMagnitude(void) const;
    // ||this||^2 = this * this
    float MagSqrd(void) const;
    // this * v
    float Dot(const Vec3 & v) const;
    // this ^ v
    void Cross(const Vec3 & rhs, Vec3 *vOut) const;
    

    // assignment
    const Vec3 & operator=(const Vec3 & v);
    const Vec3 & operator+=(const Vec3 & v);
    const Vec3 & operator-=(const Vec3 & v);
    const Vec3 & operator*=(const float scalar);
    const Vec3 & operator/=(const float scalar);
    // epsilon comparisons
    bool operator==(const Vec3 & v) const;
    bool operator!=(const Vec3 & v) const;
	bool operator<(const Vec3 & v) const;
	bool operator>(const Vec3 & v) const;
    // binary operations
    Vec3 operator+(const Vec3 & v) const;
    Vec3 operator-(const Vec3 & v) const;
    Vec3 operator*(const float scalar) const;
    Vec3 operator/(const float scalar) const;

	friend Vec3 operator*(float scalar, const Vec3 & rhs);
    friend Vec3 operator/(float scalar, const Vec3 & rhs);

  public:
    float x, y, z;

  private:
    Vec3 operator-(void);
};

//------------------------------------------------------------------------------
class Vec4
{
  public:
    Vec4(float i = 0.0f, float j = 0.0f, float k = 0.0f, float f = 0.0f);
	Vec4(const Vec4 & p1, const Vec4 & p2);
    Vec4(const Vec4& rhs);

    /// queries: ///
    bool IsZero(void) const;

    // modifications to *this or output of modified *this
    void Zero(void);
    void Abs(void);
    void Set(float xyzValue);
    void Set(float i, float j, float k, float f);
    void Negate(void);
    void Inverse(void);
    void Normalize(void);
	void Norm(Vec4 *vOut) const;
    void Multiply(const Vec4 & v);

    // ||this||
    float Magnitude(void) const;
    // 1/||this||
    float InvMagnitude(void) const;
    // ||this||^2 = this * this
    float MagSqrd(void) const;
    // this * v
    float Dot(const Vec4 & v) const;
    
    // assignment
    const Vec4 & operator=(const Vec4 & v);
    const Vec4 & operator+=(const Vec4 & v);
    const Vec4 & operator-=(const Vec4 & v);
    const Vec4 & operator*=(const float scalar);
    const Vec4 & operator/=(const float scalar);
    // epsilon comparisons
    bool operator==(const Vec4 & v) const;
    bool operator!=(const Vec4 & v) const;
    // binary operations
    Vec4 operator+(const Vec4 & v) const;
    Vec4 operator-(const Vec4 & v) const;
    Vec4 operator*(const float scalar) const;
    Vec4 operator/(const float scalar) const;

	friend Vec4 operator*(float scalar, const Vec4 & rhs);
    friend Vec4 operator/(float scalar, const Vec4 & rhs);

  public:
    float x, y, z, w;

  private:
    Vec4 operator-(void);
};

//------------------------------------------------------------------------------
struct Seg3D
{
  public:
    Seg3D(void);
    Seg3D(const Vec3 & q1, const Vec3 & q2);

    bool operator==(const Seg3D & rhs);

    void Set(const Vec3 & q1, const Vec3 & q2);

  public:
    Vec3 p1;
    Vec3 p2;
};

//------------------------------------------------------------------------------
// not necessarily normalized
// UNI-directional
struct Ray3D
{
  public:
	Ray3D(void);
	Ray3D(Vec3 o, Vec3 d);
    bool operator==(const Ray3D & rhs);

    void Set(const Vec3 & point, const Vec3 & direction);

  public:
    Vec3 origin;
    Vec3 dir;
};

//------------------------------------------------------------------------------
// not necessarily normalized
// BI-directional
struct Line3D
{
  public:
	Line3D(void);
	Line3D(Vec3 p, Vec3 d);
    bool operator==(const Line3D & rhs);

    void Set(const Vec3 & point, const Vec3 & direction);

  public:
    Vec3 pp;   // any point on an infinite line
    Vec3 dir;  // defining vector of line, should be treated as bi-directional
};

//------------------------------------------------------------------------------
// plane normal not necessarily normalized
struct Plane3D
{
  public:
    Plane3D(void);
      // non-defualt constructor normalizes this->n
    Plane3D(const Vec3 & planeNormal, const Vec3 & p);

    bool operator==(const Plane3D & rhs);

    // 'Set' methods normalize this->n
    void Set(float nx, float ny, float nz, const Vec3 & p);
    void Set(const Vec3 & planeNormal, const Vec3 & p);
    void Set(const Vec3 & p0, const Vec3 & p1, const Vec3 &p2);

  public:
    float d;  // distance from plane to origin along the negative face-normal [ie, -n.Dot(pp)]
    Vec3 n;   // plane positive half-space face-normal
    Vec3 pp;  // a point on the plane
};

//------------------------------------------------------------------------------
struct Triangle
{
  public:
    Triangle(void);
    Triangle(const Vec3 & v0, const Vec3 & v1, const Vec3 & v2);

    void Set(const Vec3 & v0, const Vec3 & v1, const Vec3 & v2);

  public:
	Vec4 color;
    Vec3 p0;
    Vec3 p1;
    Vec3 p2;
};

//------------------------------------------------------------------------------
struct Sphere
{
  public:
    Sphere(void);
    Sphere(float r, const Vec3 & c);

    void Set(float r, const Vec3 & c);
    float RadiusSqrd(void) const;

  public:
    float radius;
    Vec3 center;
};

//------------------------------------------------------------------------------
struct AABB
{
  public:
    AABB(void);
    AABB(const Vec3 & r, const Vec3 & c);

    void Set(const Vec3 & r, const Vec3 & c);
    void MinMax(Vec3 *minOut, Vec3 *maxOut) const;
	Vec3 GetVertex(int point);

  public:
    Vec3 radii;
    Vec3 center;
};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
struct Portal
{
  public:
    Portal(void);
	void DrawPortal(void);

  public:
    Vec3 center,p1,p2,p3;
};

//------------------------------------------------------------------------------

}

#endif 