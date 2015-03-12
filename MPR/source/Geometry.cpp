/////////////////////////////////////////////////////////////
// File  : Geometry.cpp                                    //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : CS350 Framework Geometry implementations        //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "Geometry.h"

namespace Framework
{
  /******************************************************************************/
  Vec3 Project(const Vec3 & p, const Line3D & line)
  {
    return line.pp + (p - line.pp).Dot(line.dir) * line.dir;
  }

  /******************************************************************************/
  Vec3 Project(const Vec3 & p, const Plane3D & plane)
  {
    return p - (plane.n.Dot(p - plane.pp)/plane.n.Dot(plane.n)) * plane.n;
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Vec3 & q)
  {
    Vec3 v = p - q;
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Line3D & line)
  {
    Vec3 R = Project(p,line);
    return Distance(p,R);
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Seg3D & segment)
  {
    Vec3 s    = segment.p2 - segment.p1;
  
    //project p onto s
    float t = (p - segment.p1).Dot(s) / s.Dot(s);
  
    //if outside of the segment clamp t
    if( t < 0.0f)
      t = 0.0f;
    if( t > 1.0f)
      t = 1.0f;

    //projected position from clamped t
    Vec3 d = segment.p1 + t * s;

    return Distance(p,d);
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Ray3D & ray)
  {
    Vec3 s = (ray.origin + ray.dir) - ray.origin;
  
    //project p onto s
    float t = (p - ray.origin).Dot(s) / s.Dot(s);
  
    //if outside of the rays starting pos clamp t
    if( t < 0.0f)
      t = 0.0f;

    //projected position
    Vec3 d = ray.origin + t * s;

    return Distance(p,d);
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Plane3D & plane)
  {
    return plane.n.Dot(p) + plane.d;
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Triangle & triangle)
  {
    Vec3 AB = triangle.p1 - triangle.p0;
    Vec3 AC = triangle.p2 - triangle.p0;
    Vec3 BC = triangle.p2 - triangle.p1;
    Vec3 AP = p - triangle.p0;
    Vec3 BP = p - triangle.p1;
    Vec3 CP = p - triangle.p2;

    //distances
    float d1 = AB.Dot(AP);
    float d2 = AC.Dot(AP);
    float d3 = AB.Dot(BP);
    float d4 = AC.Dot(BP);
    float d5 = AB.Dot(CP);
    float d6 = AC.Dot(CP);

    //vertex cases
    //vertex A
    if(d1 < 0 && d2 < 0)
      return Distance(p, triangle.p0);
    if(d3 > 0 && d3 > d4) //vertex B
      return Distance(p, triangle.p1);
    if(d6 > 0 && d6 > d5) //vertex C
      return Distance(p, triangle.p2);

    //Edge Cases
    Vec3 N;
    triangle.p0.Cross(triangle.p1,&N);
    float K = 1 / (2 * N.Magnitude());
    float KQAB = K *(d4 * d1 - d2 * d3); 
    float KQAC = K *(d5 * d2 - d1 * d6);
    float KQBC = K *(d3 * d6 - d5 * d4);

    float t1 = d1 / (d1 - d3);
    float t2 = d2 / (d2 - d6);
    float t3 = (d4 - d3) / (d4 - d3 + d5 - d6);

    if(d1 >= 0 && d3 <= 0 && KQAB <= 0)
      return Distance(p, (triangle.p0 + t1 * AB));
    if(d2 >= 0 && d6 <= 0 && KQAC <= 0)
      return Distance(p, (triangle.p1 + t2 * AC));
    if((d4 - d3) >= 0 && (d5 - d6) >= 0 && KQBC <= 0)
      return Distance(p, (triangle.p2 + t3 * BC));

    float QBC = (d3 * d6 - d5 * d4);
    float QAB = (d4 * d1 - d2 * d3); 
    float QAC = (d5 * d2 - d1 * d6);
    float ABC = (QAC + QAB + QBC);

    float S = QAC / ABC;
    float T = QAB / ABC;

    Vec3 R  = triangle.p0 + AB * S + AC * T; 

    return Distance(p,R);
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const Sphere & sphere)
  {
    return Distance(p, sphere.center) - sphere.radius;
  }

  /******************************************************************************/
  float Distance(const Vec3 & p, const AABB & aabb)
  {
    Vec3 q;
    Vec3 bmin, bmax;
    aabb.MinMax(&bmax,&bmin);

    float v = p.x;
    if(v < bmin.x)
      v = bmin.x;
    if(v > bmax.x)
      v = bmax.x;
    q.x = v;

    v = p.y;
    if(v < bmin.y)
      v = bmin.y;
    if(v > bmax.y)
      v = bmax.y;
    q.y = v;

    v = p.z;
    if(v < bmin.z)
      v = bmin.z;
    if(v > bmax.z)
      v = bmax.z;
    q.z = v;

    return Distance(p,q);
  }

  /******************************************************************************/
  float Distance(const Line3D & line0, const Line3D & line1)
  {
    Vec3 u = line0.dir;
    Vec3 v = line1.dir;
    Vec3 r = line0.pp - line1.pp;

    float a = u.Dot(u);
    float b = u.Dot(v);
    float c = u.Dot(r); 
    float e = v.Dot(v);
    float f = v.Dot(r);
    float d = (a * e) - (b * b);
  

    float t = (a * f - b * c)/d;
    float s = (b * f - c * e)/d;
  
    Vec3 L1 = line0.pp + s * u;
    Vec3 L2 = line1.pp + t * v;

    return Distance(L1,L2);
  }

  /******************************************************************************/
  float Distance(const Line3D & line, const Sphere & sphere)
  {
    return Distance(sphere.center, line) - sphere.radius;
  }

  /******************************************************************************/
  float Clamp(float n, float min, float max) 
  {
    if (n < min) return min;
    if (n > max) return max;
    return n;
  }
  float Distance(const Seg3D & seg0, const Seg3D & seg1)
  {
    Vec3 c1,c2;
  Vec3 d1 = seg0.p2 - seg0.p1; // Direction vector of segment S1
  Vec3 d2 = seg1.p2 - seg1.p1; // Direction vector of segment S2
    Vec3 r  = seg0.p1 - seg1.p1;
  float a = d1.MagSqrd(); // Squared length of segment S1, always nonnegative
  float e = d2.MagSqrd(); // Squared length of segment S2, always nonnegative
    float f = d2.Dot(r);

  float s,t;

    // Check if either or both segments degenerate into points
    if (a <= Epsilon && e <= Epsilon)
  {
        // Both segments degenerate into points
        s = t = 0.0f;
        c1 = seg0.p1;
        c2 = seg1.p1;
        return (c1 - c2).Dot(c1 - c2);
    }
    if (a <= Epsilon)
  {
        // First segment degenerates into a point
        s = 0.0f;
        t = f / e; // s = 0 => t = (b*s + f) / e = f / e
        t = Clamp(t, 0.0f, 1.0f);
    } 
  else 
  {
      float c = d1.Dot(r);
      if (e <= Epsilon)
      {
        // Second segment degenerates into a point
        t = 0.0f;
        s = Clamp(-c / a, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c / a
      } 
    else
    {
        // The general nondegenerate case starts here
        float b = d1.Dot(d2);
        float denom = a*e-b*b; // Always nonnegative

        // If segments not parallel, compute closest point on L1 to L2, and
        // clamp to segment S1. Else pick arbitrary s (here 0)
        if (denom != 0.0f)
      {
          s = Clamp((b*f - c*e) / denom, 0.0f, 1.0f);
        } 
      else 
        s = 0.0f;

        // Compute point on L2 closest to S1(s) using
        // t = Dot((P1+D1*s)-P2,D2) / Dot(D2,D2) = (b*s + f) / e
        t = (b*s + f) / e;

        // If t in [0,1] done. Else clamp t, recompute s for the new value
        // of t using s = Dot((P2+D2*t)-P1,D1) / Dot(D1,D1)= (t*b - c) / a
        // and clamp s to [0, 1]
        if (t < 0.0f)
      {
          t = 0.0f;
          s = Clamp(-c / a, 0.0f, 1.0f);
        } 
      else if (t > 1.0f)
      {
          t = 1.0f;
          s = Clamp((b - c) / a, 0.0f, 1.0f);
        }
    }
  }

    c1 = seg0.p1 + d1 * s;
    c2 = seg1.p1 + d2 * t;
    return Distance(c1,c2);
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Line3D & line)
  {
    Vec3 v = p - line.pp;
    float d = line.dir.Dot(v);
    float d_sqrd = d * d;
    float v_msqrd = v.MagSqrd();
    float l_msqrd = line.dir.MagSqrd();
    float Epsilon_sqrd = Epsilon * Epsilon;
  
    if(v.Dot(v) < Epsilon)
      return true;
    if(v.Dot(d) * v.Dot(d) == v.MagSqrd() * v.MagSqrd())
      return true;
    if(-Epsilon_sqrd <= 1 - (d_sqrd / (v_msqrd * l_msqrd)) && 
                              1 - (d_sqrd / (v_msqrd * l_msqrd)) <= Epsilon_sqrd)
      return true;

    return false; 

  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Seg3D & segment)
  {
    Vec3 s = p - segment.p1;
    Vec3 e = segment.p2 - segment.p1;
    float t = (s.Dot(e)) / (s.MagSqrd());
    Line3D line;
    line.Set(segment.p1 + e, e.Magnitude());

    return Contains(p, line) && (0.0f <= t  && t <= 1.0f);
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Ray3D & ray)
  {
    Vec3 s = p - ray.origin;
    Vec3 e = (ray.origin + ray.dir) - ray.origin;
    float t = (s.Dot(e)) / (s.MagSqrd());
    Line3D line;
    line.Set(ray.origin, e);
    return Contains(p, line) && (0.0f <= t);
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Plane3D & plane)
  {
    Vec3 s = p - plane.pp;

    float t = s.Dot(plane.n)/(plane.n.MagSqrd());
    float tn_sqrd = (t * plane.n.Magnitude()) * (t * plane.n.Magnitude());

    return (tn_sqrd <= Epsilon * Epsilon);
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Triangle & triangle)
  {
    //make sure point and triangle are coplanar
    Plane3D plane;
    (triangle.p0 - triangle.p1).Cross((triangle.p2 - triangle.p1), &plane.n);
    plane.d = -triangle.p1.Dot(plane.n);
    plane.pp = triangle.p0;

    if(!Contains(p,plane))
      return false;

    Vec3 AP = triangle.p0 - p;
    Vec3 BP = triangle.p1 - p;
    Vec3 CP = triangle.p2 - p;

    Vec3 N1;
    Vec3 N2;
    Vec3 N3;
    BP.Cross(CP, &N1);
    CP.Cross(AP, &N2);
    AP.Cross(BP, &N3);

    //check to make sure all normals
    //are facing the same direction
    if(N1.Dot(N2) <= Epsilon)
      return false;
    if(N1.Dot(N3) <= Epsilon)
      return false;


    return true;
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const Sphere & sphere)
  {
    Vec3 s = p - sphere.center;
    float s_sqrd = s.MagSqrd();
    float r_sqrd  = sphere.RadiusSqrd();

    return s_sqrd <= r_sqrd;
  }

  /******************************************************************************/
  bool Contains(const Vec3 & p, const AABB & aabb)
  {
    Vec3 min,max;
    aabb.MinMax(&max,&min);

    return min.x <= p.x && p.x <= max.x && min.y <= p.y
                    && p.y <= max.y && min.z <= p.z && p.z <= max.z;
  }

  /******************************************************************************/
  bool Intersect(const Line3D & line, const Plane3D & plane, Vec3 *ipOut, float *pT)
  {
    float r = plane.n.Dot(line.dir);
  
    if(-Epsilon <= r && r <= Epsilon)
      return false;
  
    *pT = -(plane.d + plane.n.Dot(line.pp))/r;
    *ipOut = line.pp + *pT * line.dir;

    return true;
  }

  /******************************************************************************/
  bool Intersect(const Seg3D & segment, const Plane3D & plane, Vec3 *ipOut, float *pT)
  {   
  
    if(!pT || !ipOut)
      return false;

    Vec3 s = segment.p2 - segment.p1;
  
    float r = plane.n.Dot(s);
  
    if(-Epsilon <= r && r <= Epsilon)
      return false;

    *pT = -(plane.d + plane.n.Dot(segment.p1))/r;

    if(0.0f <= *pT && *pT <= 1.0f)
    {
      *ipOut = segment.p1 + *pT * s;
    return true;
    }

    return false;
  }

  /******************************************************************************/
  bool Intersect(const Seg3D & segment, const Triangle & triangle, Vec3 *ipOut, float *pT)
  {
    //get the triangles plane
    Plane3D plane;
    (triangle.p0 - triangle.p1).Cross((triangle.p2 - triangle.p1), &plane.n);
    plane.d = -triangle.p1.Dot(plane.n);
    plane.pp = triangle.p0;

    //test segment plane intersection
    //if successful check if ip is contained in triangle
    //if so intersection is true
    if(Intersect(segment,plane,ipOut,pT))
      if(Contains(*ipOut,triangle))
      return true;
  
    return false;
  }

  /******************************************************************************/
  bool Intersect(const Ray3D & ray, const Plane3D & plane, Vec3 *ipOut, float *pT) 
  {
    if(!pT || !ipOut)
      return false;

    Vec3 s = ray.dir;
  
    float r = plane.n.Dot(s);
  
    if(-Epsilon <= r && r <= Epsilon)
      return false;

    *pT = -(plane.d + plane.n.Dot(ray.origin))/r;

    if(0.0f <= *pT)
    {
      *ipOut = ray.origin + *pT * s;
    return true;
    }

    return false;
  }

  /******************************************************************************/
  bool Intersect(const Ray3D & ray, const Triangle & triangle, Vec3 *ipOut, float *pT)
  {
    //get the triangles plane
    Plane3D plane;
    (triangle.p0 - triangle.p1).Cross((triangle.p2 - triangle.p1), &plane.n);
    plane.d = -triangle.p1.Dot(plane.n);
    plane.pp = triangle.p0;

    //test ray plane intersection
    //if successful check if ip is contained in triangle
    //if so intersection is true
    if(Intersect(ray,plane,ipOut,pT))
      if(Contains(*ipOut,triangle))
      return true;
  
    return false;
  }

  /******************************************************************************/
  bool Intersect(const Ray3D & ray, const Sphere & sphere, Vec3 *ipOut, float *pT)
  {
    // NOTE: assume ray direction is NOT normalized
    Vec3 s = ray.origin - sphere.center;
    Vec3 v;
    ray.dir.Norm(&v);
  
    float b = s.Dot(v);
    float c = s.Dot(s) - sphere.RadiusSqrd();

    //if the rays origin is outside of pointing away from the sphere
    if(c > Epsilon && b > Epsilon)
      return false;

    float discr = b*b - c;

    if(discr < Epsilon)
      return false;

    *pT = -b - sqrt(discr);

    if(*pT < Epsilon)
      *pT = 0;

    *ipOut = ray.origin + *pT * v;

    return true;
  }

  /******************************************************************************/
  bool Intersect(const Ray3D & ray, const AABB & aabb, Vec3 *ipOut, float *pT)
  {
    if(!pT || !ipOut)
      return false;

    float t_entry = -FLT_MAX;
    float t_exit  = FLT_MAX;
    Vec3 v = ray.dir;
    Vec3 aabbMin, aabbMax;
    aabb.MinMax(&aabbMax,&aabbMin);

    //outside x-slab do nothing
    if(-Epsilon <= v.x && v.x <= Epsilon)
    {
      //ray is parallel to slab
      if(aabbMax.x <= ray.origin.x || ray.origin.x <= aabbMin.x)
      return false;
    }
    else
    {
      float ood = 1.0f / v.x;
    float t1 = (aabbMin.x - ray.origin.x) * ood;
    float t2 = (aabbMax.x - ray.origin.x) * ood;

    if(t1 > t2)
    {
      float temp = t1;
      t1 = t2;
      t2 = temp;
    }

      t_entry = max(t_entry, t1);
    t_exit = min(t_exit, t2);

    if(t_exit < t_entry)
      return false;
    }
    //outside y-slab do nothing
    if(-Epsilon <= v.y && v.y <= Epsilon)
    {
      //ray is parallel to slab
      if(aabbMax.y <= ray.origin.y || ray.origin.y <= aabbMin.y)
      return false;
    }
    else
    {
      float ood = 1.0f / v.y;
    float t1 = (aabbMin.y - ray.origin.y) * ood;
    float t2 = (aabbMax.y - ray.origin.y) * ood;

    if(t1 > t2)
    {
      float temp = t1;
      t1 = t2;
      t2 = temp;
    }

      t_entry = max(t_entry, t1);
    t_exit = min(t_exit, t2);

    if(t_exit < t_entry)
      return false;
    }
    //outside z-slab do nothing
    if(-Epsilon <= v.z && v.z <= Epsilon)
    {
      //ray is parallel to slab
      if(aabbMax.z <= ray.origin.z || ray.origin.z <= aabbMin.z)
      return false;
    }
    else
    {
      float ood = 1.0f / v.z;
    float t1 = (aabbMin.z - ray.origin.z) * ood;
    float t2 = (aabbMax.z - ray.origin.z) * ood;
      if(t1 > t2)
    {
      float temp = t1;
      t1 = t2;
      t2 = temp;
    }
      t_entry = max(t_entry, t1);
    t_exit = min(t_exit, t2);

    if(t_exit < t_entry)
      return false;
    }

    *pT = t_entry;
    *ipOut = ray.origin + *pT * v;

    return true;
  }

  /******************************************************************************/
  bool Intersect(const Sphere & sphere0, const Sphere & sphere1)
  { 
    Vec3 s = sphere1.center - sphere0.center;

    if(s.Magnitude() - (sphere0.radius + sphere1.radius) <= Epsilon)
      return true;
                                                                                                       
    return false;
  }

  /******************************************************************************/
  bool Intersect(const Triangle & triangle0, const Triangle & triangle1)
  {
    Seg3D e0;
    Seg3D e1;
    Seg3D e2;
    Seg3D e3;
    Seg3D e4;
    Seg3D e5;
    e0.Set(triangle0.p1, triangle0.p0);
    e1.Set(triangle0.p2, triangle0.p0);
    e2.Set(triangle0.p2, triangle0.p1);
    e3.Set(triangle1.p1, triangle1.p0);
    e4.Set(triangle1.p2, triangle1.p0); 
    e5.Set(triangle1.p2, triangle1.p1);
    Vec3 q;
    float t;
  

    if(Intersect(e0, triangle1, &q, &t))
      return true;
    else if(Intersect(e1, triangle1, &q, &t))
    return true;
    else if(Intersect(e2, triangle1, &q, &t))
    return true;
    else if(Intersect(e3, triangle0, &q, &t))
      return true;
    else if(Intersect(e4, triangle0, &q, &t))
    return true;
    else if(Intersect(e5, triangle0, &q, &t))
    return true;
    else
      return false;
  }

  /******************************************************************************/
  bool Intersect(const AABB & aabb0, const AABB & aabb1)
  {
    if((aabb0.center.x - aabb1.center.x) <= (aabb0.radii.x + aabb1.radii.x))
      return true;
    if((aabb0.center.y - aabb1.center.y) <= (aabb0.radii.y + aabb1.radii.y))
      return true;
    if((aabb0.center.z - aabb1.center.z) <= (aabb0.radii.z + aabb1.radii.z))
      return true;

    return false;
  }

  /******************************************************************************/
  float Angle(const Line3D & line0, const Line3D & line1)
  {
    return acos(line0.dir.Dot(line1.dir) / (line0.dir.Magnitude() * line1.dir.Magnitude()));
  }

  /******************************************************************************/
  float Angle(const Line3D & line, const Plane3D & plane)
  {
    return asin(line.dir.Dot(plane.n) / (line.dir.Magnitude() * plane.n.Magnitude()));
  }

  /******************************************************************************/
  float Angle(const Plane3D & plane0, const Plane3D & plane1)
  {
    return acos(plane0.n.Dot(plane1.n) / (plane0.n.Magnitude() * plane1.n.Magnitude()));
  }

  /******************************************************************************/
  bool Parallel(const Line3D & line0, const Line3D & line1)
  { 
    Vec3 norm0;
  norm0 = line0.dir;
    norm0.Normalize();
    Vec3 norm1;
  norm1 = line1.dir;
    norm1.Normalize();

    return norm0 == norm1;
  }

  /******************************************************************************/
  bool Parallel(const Line3D & line, const Plane3D & plane)
  {
    if(-Epsilon <= line.dir.Dot(plane.n) && line.dir.Dot(plane.n) <= Epsilon)
      return true;

    return false;
  }

  /******************************************************************************/
  bool Parallel(const Plane3D & plane0, const Plane3D & plane1)
  {
    return plane0.n == plane1.n;
  }

  /******************************************************************************/
  bool Perpendicular(const Line3D & line0, const Line3D & line1)
  {
    if(-Epsilon <= line0.dir.Dot(line1.dir) && line0.dir.Dot(line1.dir) <= Epsilon)
      return true;

    return false;
  }

  /******************************************************************************/
  bool Perpendicular(const Line3D & line, const Plane3D & plane)
  {
    Vec3 pp = Project(line.pp, plane);
    Vec3 pv = plane.pp - pp;

    if(-Epsilon <= line.dir.Dot(pv) && line.dir.Dot(pv) <= Epsilon)
      return true;

    return false;
  }

  /******************************************************************************/
  bool Perpendicular(const Plane3D & plane0, const Plane3D & plane1)
  {
    if(-Epsilon <= plane0.n.Dot(plane1.n) && plane0.n.Dot(plane1.n) <= Epsilon)
      return true;

    return false;
  }

  /******************************************************************************/
  bool Coplanar(const Line3D & line, const Plane3D & plane)
  {
    if(-Epsilon <= Angle(line, plane) && Angle(line, plane) <= Epsilon)
      if(Contains(line.pp,plane))
        return true;

    return false;
  }

  /******************************************************************************/
  bool Coplanar(const Plane3D & plane0, const Plane3D & plane1)
  {
    if(!Parallel(plane0,plane1))
      if(!Contains(plane0.pp, plane1))
        return false;

    return true;
  }

// ---------------------------------------------------------------------------
}//namespace