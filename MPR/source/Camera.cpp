/////////////////////////////////////////////////////////////
// File  : Camera.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Camera definition                               //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "Camera.h"
#include "Graphics.h"
#include "SDLInput.h"
#include "Geometry.h"

namespace Framework
{
  Camera* CAMERA;
  Camera::Camera() 
  {
	Phi = 0;
	Theta = -PI/2.0f; //start looking down negative z
	CAMERA = this;
    MousePress = false;
  }
  Camera::~Camera()
  {
  }
  void Camera::Init()
  {
    Target.Set(0.0f,0.0f,0.0f);
	Up.Set(0.0f,1.0f,0.0f);
	Pos.Set(0.0f,0.0f,300.0f);
	Dir.Set(0.0f,0.0f,0.0f);
	Right.Set(1.0f,0.0f,0.0f);
	Fov = 60.0f;
	ClipNear = 0.08f;
	ClipFar = 3000.0f;
	ratio = 1.0f / (ClipNear/ClipFar);
	
	// compute width and height of the near and far plane sections
	tang = 2.0f * tan(Fov * 0.5f);
	nh = ClipNear * tang;
	nw = nh * ratio;
	fh = ClipFar * tang;
	fw = fh * ratio;
  }
  void Camera::LoadMatrix()
  {
	Vec3 pos;
	float radius = 0.5f;
	float t = cos(Phi);   // distance to y-axis after being rotated up
    pos.y = radius * sin(Phi);
    pos.x = radius * t*cos(Theta);
    pos.z = radius * t*sin(Theta);

	Target = Pos + pos; 
	Dir = Target - Pos;
	Dir.Normalize();
	Up.Cross(Dir, &Right);
	
	gluLookAt(Pos.x, Pos.y, Pos.z, Target.x, Target.y, Target.z, Up.x, Up.y, Up.z);
    
	//SetFrustum();
  }

  void Camera::RecieveMessage( Message* m )
  {
	  switch(m->MessageId)
	  {
        case Mid::CharacterKey:
	    {
		  float CamSpeed = 400;
		  // Cast to the derived message type
	      MessageCharacterKey * key = (MessageCharacterKey*)m;
		  if(key->character == SDLK_w && key->KeyPressed)
		    Pos += Dir * CamSpeed * .016f;
		  if(key->character == SDLK_a && key->KeyPressed)
		    Pos += Right * CamSpeed * .016f;
		  if(key->character == SDLK_s && key->KeyPressed)
		    Pos -= Dir * CamSpeed * .016f;
		  if(key->character == SDLK_d && key->KeyPressed)
		    Pos -= Right * CamSpeed * .016f;

          break;
		}
		case Mid::MouseButton:
		{
		  MouseButton* mb = (MouseButton*)m;
		  if(mb->MouseButtonIndex == mb->LeftMouse && mb->ButtonIsPressed)
		    MousePress = true;
		  else if(mb->MouseButtonIndex == mb->LeftMouse && !mb->ButtonIsPressed)
			MousePress = false;

		  break;
		}
	    case Mid::MouseMove:
	    {
		  if(MousePress)
		  {
		    MouseMove* mouse = (MouseMove*)m;
		    Theta += mouse->MousePosition.x * .01f;
		    Phi -= mouse->MousePosition.y * .01f;

			if(Phi > (PI * 0.5f))
			  Phi = (PI * 0.5f);
			if(Phi < -(PI * 0.5f))
			  Phi = -(PI * 0.5f);

		  }
		  break;
		  
		}

	  }

  }

  void Camera::SetFrustum()
  {
	// compute the centers of the near and far planes
	Vec3 nc = Pos + Dir * ClipNear;
	Vec3 fc = Pos + Dir * ClipFar;

	// compute the 4 corners of the frustum on the near plane
	ntl = nc + (Up * (nh * 0.5f)) - (Right * (nw * 0.5f));
	ntr = nc + (Up * (nh * 0.5f)) + (Right * (nw * 0.5f));
	nbl = nc - (Up * (nh * 0.5f)) - (Right * (nw * 0.5f));
	nbr = nc - (Up * (nh * 0.5f)) + (Right * (nw * 0.5f));

	// compute the 4 corners of the frustum on the far plane
	ftl = fc + (Up * (fh * 0.5f)) - (Right * (fw * 0.5f));
	ftr = fc + (Up * (fh * 0.5f)) + (Right * (fw * 0.5f));
	fbl = fc - (Up * (fh * 0.5f)) - (Right * (fw * 0.5f));
	fbr = fc - (Up * (fh * 0.5f)) + (Right * (fw * 0.5f));

	// compute the six planes
	// the function set3Points assumes that the points
	// are given in counter clockwise order
	pl[TOP].Set(ntr,ntl,ftl);
	pl[BOTTOM].Set(nbl,nbr,fbr);
	pl[LEFT].Set(ntl,nbl,fbl);
	pl[RIGHT].Set(nbr,ntr,fbr);
	pl[NEARP].Set(ntl,ntr,nbr);
	pl[FARP].Set(ftr,ftl,fbl);

  }

  int Camera::boxInFrustum(AABB &b)
  {
	int result = 1, out,in;
	// for each plane
	for(int i=0; i < 6; i++) 
	{
	  // reset counters for corners in and out
	  out=0;in=0;
	  // for each corner of the box do ...
	  // get out of the cycle as soon as a box as corners
	  // both inside and out of the frustum
	  for (int k = 0; k < 8; k++) 
	  {
	    // is the corner outside or inside
		if (Distance(b.GetVertex(k), pl[i]) < 0)
		  out++;
		else
		  in++;
	  }
	  //if all corners are out
	  if(!in)
	    return 0;
	  // if some corners are out and others are in
	  else if(out)
		result = 1;
	}
	return result;
  }

}//namespace

