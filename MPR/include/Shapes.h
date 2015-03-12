/////////////////////////////////////////////////////////////
// File  : Shapes.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 2/1/2012                                        //
// Breif : Basic Shapes class                              //
/////////////////////////////////////////////////////////////

#ifndef SHAPES_H
#define SHAPES_H

namespace Framework
{

  
  struct Vertex
  {
    Vec3 vertex;
    Vec3 normal;
    Vec4 color;
    Vertex(Vec3 v, Vec3 n, Vec4 c) : vertex(v), normal(n), color(c){}
    Vertex(const Vertex& rhs){this->vertex = rhs.vertex;this->normal = rhs.normal;this->color=rhs.color;}
    void Set(Vec3 v, Vec3 n, Vec4 c){vertex = v;normal=n;color=c;}
  };

  class Object
  {
    public:
      Object();
    Object(const Object& rhs);
    ~Object();
    Mtx44 GetTransform();

    int Type; //Plane, Cube, Sphere
    float SubDivions;
    Vec3 Position;
    Vec3 Scale;
    Vec3 RotAxis;
    float RotAngle;
    Vec4 Color; //r,g,b,a
    std::vector<Vertex> VtxVec;
    std::vector<Vertex> ModelVertsVec;
    AABB aabb;
  };

  class Shapes
  {
     public:
         enum
         {
         PLANE = 0, 
         CUBE, 
         SPHERE
         };
       
       Shapes();
       ~Shapes();
       static void Draw(Object* shape);
       static void DrawVerts(void);

     private:
       static void DrawPlane(Object* shape);
       static void DrawCube(Object* shape);
       static void DrawSphere(Object* shape);
       
  };

  
}

#endif