/////////////////////////////////////////////////////////////
// File  : Camera.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Camera definition                               //
/////////////////////////////////////////////////////////////

#ifndef CAMERA_H
#define CAMERA_H

namespace Framework
{
  class Camera
  {
     public:
       Camera();
     ~Camera();

     // load the camera transformation matrix on top of OpenGL modelview stack
       void LoadMatrix();
     void Init();
     void RecieveMessage(Message* m);

     void SetFrustum();
       int boxInFrustum(AABB &b);

         float Fov, ClipNear, ClipFar,ratio,tang;
     float nw,nh,fw,fh;
     Vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
       static enum {OUTSIDE, INTERSECT, INSIDE};

     //private:
     // camera target, position, up vector and direction
       Vec3 Target;//where the camera is looking
       Vec3 Pos;   //camera position
       Vec3 Up;    //Up vector
     Vec3 Dir;   //direction vector CamPos - Target
     Vec3 Right; //right vector
     float Phi, Theta;
     bool MousePress;
     Plane3D pl[6]; //view frustum

       enum 
       {
       TOP = 0, BOTTOM, LEFT,
       RIGHT, NEARP, FARP
       }; 
     
  };

   extern Camera* CAMERA;
}

#endif
