/////////////////////////////////////////////////////////////
// File  : Geometry.h                                      //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : CS350 Framework Geometry header                 //
/////////////////////////////////////////////////////////////

#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace Framework
{

  // ---------------------------------------------------------------------------
  // calculate the projection of a given point to other entity

  Vec3 Project(const Vec3 & p, const Line3D & line);
  Vec3 Project(const Vec3 & p, const Plane3D & plane);

  // ---------------------------------------------------------------------------
  // calculate the distance from one entity to another

  // point to another entity
  float Distance(const Vec3 & p, const Vec3 & q);
  float Distance(const Vec3 & p, const Line3D & line);
  float Distance(const Vec3 & p, const Seg3D & segment);
  float Distance(const Vec3 & p, const Ray3D & ray);
  float Distance(const Vec3 & p, const Plane3D & plane);
  float Distance(const Vec3 & p, const Triangle & triangle);
  float Distance(const Vec3 & p, const Sphere & sphere);
  float Distance(const Vec3 & p, const AABB & aabb);

  // line to another entity
  float Distance(const Line3D & line0, const Line3D & line1);
  float Distance(const Line3D & line, const Sphere & sphere);

  // segment to another entity
  float Distance(const Seg3D & seg0, const Seg3D & seg1);

  // ---------------------------------------------------------------------------
  // check if the given point is contained within another entity

  // point is contained within another entity
  bool Contains(const Vec3 & p, const Line3D & line);
  bool Contains(const Vec3 & p, const Seg3D & segment);
  bool Contains(const Vec3 & p, const Ray3D & ray);
  bool Contains(const Vec3 & p, const Plane3D & plane);
  bool Contains(const Vec3 & p, const Triangle & triangle);
  bool Contains(const Vec3 & p, const Sphere & sphere);
  bool Contains(const Vec3 & p, const AABB & aabb);

  // ---------------------------------------------------------------------------
  // calculate intersection between one entity with another
  // * pOut is the 1st intersection point between the 2 entities
  // * pT? is the 'time' of the intersection point

  // pT = time for line
  bool Intersect(const Line3D & line, const Plane3D & plane, Vec3 *ipOut = 0, float *pT = 0);

  // pT = time for line
  bool Intersect(const Seg3D & segment, const Plane3D & plane, Vec3 *ipOut = 0, float *pT = 0); 
  bool Intersect(const Seg3D & segment, const Triangle & triangle, Vec3 *ipOut = 0, float *pT = 0);

  // pT = time for the ray
  bool Intersect(const Ray3D & ray, const Plane3D & plane, Vec3 *ipOut = 0, float *pT = 0);
  bool Intersect(const Ray3D & ray, const Triangle & triangle, Vec3 *ipOut = 0, float *pT = 0);
  bool Intersect(const Ray3D & ray, const Sphere & sphere, Vec3 *ipOut = 0, float *pT = 0);
  bool Intersect(const Ray3D & ray, const AABB & aabb, Vec3 *ipOut = 0, float *pT = 0);

  // no intersection ouput-data
  bool Intersect(const Sphere & sphere0, const Sphere & sphere1);
  bool Intersect(const Triangle & triangle0, const Triangle & triangle1);
  bool Intersect(const AABB & aabb0, const AABB & aabb1);

  // ---------------------------------------------------------------------------
  // entity relationship testing

  // check angle between 2 entities
  // * return valus is in radians
  float Angle(const Line3D & line0, const Line3D & line1);
  float Angle(const Line3D & line, const Plane3D & plane);
  float Angle(const Plane3D & plane0, const Plane3D & plane1);

  // check if 2 entities are parallel
  bool Parallel(const Line3D & line0, const Line3D & line1);
  bool Parallel(const Line3D & line, const Plane3D & plane);
  bool Parallel(const Plane3D & plane0, const Plane3D & plane1);

  // check if 2 entities are perpendicular
  bool Perpendicular(const Line3D & line0, const Line3D & line1);
  bool Perpendicular(const Line3D & line, const Plane3D & plane);
  bool Perpendicular(const Plane3D & plane0, const Plane3D & plane1);

  // check if 2 entities are coplanar
  bool Coplanar(const Line3D & line, const Plane3D & plane);
  bool Coplanar(const Plane3D & plane0, const Plane3D & plane1);

}//namespace
#endif 