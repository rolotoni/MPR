/////////////////////////////////////////////////////////////
// File  : Shapes.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 2/1/2012                                        //
// Breif : Basic Shapes class                              //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "Shapes.h"


namespace Framework
{
  
  Shapes::Shapes()
  {
  }
  Shapes::~Shapes()
  {
  }
  void Shapes::DrawVerts()
  {
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//glVertexPointer(3,GL_FLOAT,sizeof(Vertex),&VtxVec[0].vertex);
	//glNormalPointer(GL_FLOAT,sizeof(Vertex),&VtxVec[0].normal);
	//glColorPointer(4,GL_FLOAT,sizeof(Vertex),&VtxVec[0].color);
 //   glDrawArrays(GL_TRIANGLE_STRIP, 0, VtxVec.size());

	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
  }
  void Shapes::Draw(Object* shape)
  {
	switch(shape->Type)
	{
	  case PLANE:
	    DrawPlane(shape);
		break;
	  case CUBE:
		DrawCube(shape);
		break;
	  case SPHERE:
		DrawSphere(shape);
		break;
	}

  }

  void Shapes::DrawPlane(Object* shape)
  {

	if(shape->SubDivions < 1)
	  shape->SubDivions = 1.0;
	float y = 0.5f;
	float x;
	float ySize = shape->SubDivions;
	float xSize = shape->SubDivions;
	float deltax = 1.0f / xSize;
	float deltay = 1.0f / ySize;


	//vertex
	Vertex v(Vec3(0.0f),Vec3(0.0f),Vec4(0.0f));

    for(int j = 0; j < ySize; ++j)
	{
	  x = -.5f;
	  for(int i = 0; i <= xSize; ++i)
	  {
		v.Set(Vec3(x,y,0),Vec3(x,y,0),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		v.Set(Vec3(x,y - deltay,0),Vec3(x,y - deltay,0),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		x += deltax;
	  }

	  y -= deltay;
	}

  }

  void Shapes::DrawCube(Object* shape)
  {

	if(shape->SubDivions < 1.0)
		shape->SubDivions = 1.0;

	float x;
    float y = 0.5f;
	float z = 0.5f;
	float ySize = shape->SubDivions;
	float xSize = shape->SubDivions;
	float zSize = shape->SubDivions;
	float deltax = 1.0f / xSize;
	float deltay = 1.0f / ySize;
	float deltaz = 1.0f / zSize;

	Vertex v(Vec3(0.0f),Vec3(0.0f),Vec4(0.0f));

    for(int j = 0; j < ySize; ++j)
	{
	  x = -.5f;
	  for(int i = 0; i <= xSize; ++i)
	  {
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);


		v.Set(Vec3(x,y - deltay,z),Vec3(x,y - deltay,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		x += deltax;
	  }

	  y -= deltay;
	}
	x = 0.5f;
	z = 0.5f;
	for(int j = 0; j < zSize; ++j)
	{
	  y = -.5f;
	  for(int i = 0; i <= ySize; ++i)
	  {
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		v.Set(Vec3(x,y,z - deltaz),Vec3(x,y,z - deltaz),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		y += deltay;
	  }

	  z -= deltaz;
	}
	y = 0.5f;
	z = -.5f;
	for(int j = 0; j < ySize; ++j)
	{
	  x = .5f;
	  for(int i = 0; i <= xSize; ++i)
	  {
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		v.Set(Vec3(x,y - deltay,z),Vec3(x,y - deltay,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		x -= deltax;
	  }

	  y -= deltay;
	}
    x = -.5f;
	z = -.5f;
	for(int j = 0; j < zSize; ++j)
	{
	  y = -.5f;
	  for(int i = 0; i <= ySize; ++i)
	  {
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		v.Set(Vec3(x,y,z+deltaz),Vec3(x,y,z+deltaz),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		y += deltay;
	  }

	  z += deltaz;
	}
	y = .5f;
	z = -.5f;
	for(int j = 0; j < zSize; ++j)
	{
	  x = -.5f;
	  for(int i = 0; i <= xSize; ++i)
	  {
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);


		v.Set(Vec3(x,y,z+deltaz),Vec3(x,y,z+deltaz),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		x += deltax;
	  }

	  z += deltaz;
	}
	y = -.5f;
	z = 0.5f;
	for(int j = 0; j < zSize; ++j)
	{
	  x = -.5f;
	  for(int i = 0; i <= xSize; ++i)
	  {

		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		v.Set(Vec3(x,y,z-deltaz),Vec3(x,y,z-deltaz),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		x += deltax;
	  }

	  z -= deltaz;
	}
  }

  void Shapes::DrawSphere(Object* shape)
  {
	if(shape->SubDivions < 10)
	  shape->SubDivions = 10;
	float ySize = shape->SubDivions;
	float xSize = shape->SubDivions;
	float Deltax = PI/xSize;
	float Deltay = (2.0f * PI)/ySize;
	float x,y,z,t,r;
	r = 0.5f;
 
	Vertex v(Vec3(0.0f),Vec3(0.0f),Vec4(0.0f));

	for(float i = -PI/2.0f; i <= PI/2.0f; i += Deltax)
	{
	  for(float j = -PI; j <= PI; j += Deltay)
	  {
		t = cos(i);   
        y = r * sin(i);
        x = r * t*cos(j);
        z = r * t*sin(j);
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);

		t = cos(i + Deltax);   
        y = r * sin(i + Deltax);
        x = r * t*cos(j);
        z = r * t*sin(j);
		v.Set(Vec3(x,y,z),Vec3(x,y,z),Vec4(shape->Color.x,shape->Color.y, shape->Color.z, shape->Color.w));
		shape->ModelVertsVec.push_back(v);
		
	  }
	  
	}
   
  }

  // --------------------------------------------------------------------------------------
  Object::Object()
  {
  }
  Object::Object(const Object& rhs)
  {
    Type = rhs.Type;
	SubDivions = rhs.SubDivions;
	Position = rhs.Position;
	RotAxis = rhs.RotAxis;
	RotAngle = rhs.RotAngle;
	Scale = rhs.Scale;
	Color = rhs.Color;
  }
  Object::~Object()
  {
  }

  Mtx44 Object::GetTransform()
  {
	 //GLfloat a[16];
	 Mtx44 r,t,s;

	 //glMatrixMode(GL_MODELVIEW);
	 //glPushMatrix();
	 //glLoadIdentity();
	 //glTranslatef(Position.x, Position.y, Position.z);
	 //glRotatef(RotAngle, RotAxis.x, RotAxis.y, RotAxis.z);
	 //glScalef(Scale.x, Scale.y, Scale.z);

	 //glGetFloatv (GL_MODELVIEW_MATRIX, a);
	 //ArrayToMtx44(a, &m);
	 //glPopMatrix();
	 Mtx44Trans(&t, Position.x,Position.y,Position.z);
	 r = Mtx44Rotate(RotAxis,RotAngle);
	 Mtx44Scale(&s, Scale.x,Scale.y,Scale.z);
	 Mtx44Concat(&r, &t, &r);
	 Mtx44Concat(&s, &r, &s);


	 return s;
  }
}//namespace

