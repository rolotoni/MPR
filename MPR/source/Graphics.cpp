/////////////////////////////////////////////////////////////
// File  : Graphics.cpp                                    //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Graphics implementations                        //
/////////////////////////////////////////////////////////////
#include "Precompiled.h"
#include "Shaders.h"
#include "Shapes.h"
#include "Graphics.h"
#include "SDLWindowSystem.h"
#include "SDLInput.h"
#include "Matrix.h"
#include "Camera.h"


namespace Framework
{
  //A global pointer to the instance of Graphics
  Graphics* GRAPHICS = NULL;

  ////////////Begin Graphics class /////////////////////////
  Graphics::Graphics()
  {
  GRAPHICS = this;
    MousePosition.Set(0,0);
  ObjPos = 0;
  }

  // ---------------------------------------------------------------------------
  Graphics::~Graphics()
  {
    UnloadAssets();
  }

  // ---------------------------------------------------------------------------
  void Graphics::Initialize()
  {

  // ======================================
  // setup default OpenGL states or values
  // ======================================
  // enable back face culling
  glEnable(GL_CULL_FACE);

  // enable depth test
  glEnable(GL_DEPTH_TEST);

  // set the clear color and depth value
  glClearColor(0.25, 0.25, 0.25, 1.0);
  glClearDepth(1.0f);

  // make sure GLEW initialized correctly
  if (glewInit() != GLEW_OK)
    HALT("fail to initialize GLEW!!");

  // make sure that there is OpenGL 2.0 support
  // * need at LEAST 2.0 for shaders
  if (!GLEW_VERSION_2_0)
    HALT("OpenGL 2.0 is not supported!!");  
    
  //get the objects to draw
  ReadScene("data/scenes/input.txt");
    //load assets and init shaders
    LoadAssets();
    // check for OpenGL error
  GL_ERROR();
  //initialize Spherical Camera
  Cam = new Camera();
  Cam->Init(); 
  }

  // ---------------------------------------------------------------------------
  void Graphics::Update(float dt)
  {
    // check for OpenGL error
  GL_ERROR();

  // push all current attributes to the stack
  glPushAttrib    (GL_ALL_ATTRIB_BITS);
  glPushClientAttrib  (GL_CLIENT_ALL_ATTRIB_BITS);

  // ===============================================================
  // clear the framebuffer and depth buffer to the specified values
  // ===============================================================

  glClear       (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // =================================================
  // setup the matrix for the transformation pipeline
  // =================================================


  // get the current window size
  ScreenWidth  = 800;
  ScreenHeight = 600;

  // set the viewport
  glViewport(0, 0, ScreenWidth, ScreenHeight);
  
  // load the projection matrix
  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  gluPerspective(Cam->Fov, ScreenWidth/ScreenHeight, Cam->ClipNear, Cam->ClipFar);


  // load the world->view (camera) matrix onto the stack. 
  // * Later on, just before each object is rendered, push the model->world matrix of that 
  //   object and pop the model->world matrix after object rendering.
  // * internally, sCamera.LoadMatrix will call gluLookAt with the current camera position 
  //   and target.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Cam->LoadMatrix();

  
  // check for OpenGL error
  GL_ERROR();

  // draw the scene
  DrawScene();
  
  // check for OpenGL error
  GL_ERROR();
  
  // restore the attribute
  glPopAttrib();
  glPopClientAttrib();
  }

  // ---------------------------------------------------------------------------
  void Graphics::DrawScene(void)
  {
  
  if (Shader->SPrograms[0])
  {
      glUseProgram(Shader->SPrograms[0]);
      
    // pass in uniforms to the shader
    glUniform3f(glGetUniformLocation(Shader->SPrograms[0], "light_pos"), Cam->Pos.x,Cam->Pos.y,Cam->Pos.z);
    glUniform3f(glGetUniformLocation(Shader->SPrograms[0], "light_dir"), Cam->Dir.x,Cam->Dir.y,Cam->Dir.z);
  
  }

    GLfloat a[16];
  Mtx44 m;
  
  //translate vertices to world space
    glMatrixMode(GL_MODELVIEW);
  for(unsigned i = 0; i < ObjVec.size() - 1; ++i)
  {
    glPushMatrix();
    glTranslatef(ObjVec[i]->Position.x, ObjVec[i]->Position.y, ObjVec[i]->Position.z);
    glRotatef(ObjVec[i]->RotAngle, ObjVec[i]->RotAxis.x, ObjVec[i]->RotAxis.y, ObjVec[i]->RotAxis.z);
    glScalef(ObjVec[i]->Scale.x, ObjVec[i]->Scale.y, ObjVec[i]->Scale.z);
    for(unsigned j = 0; j < ObjVec[i]->ModelVertsVec.size(); ++j)
    {
    glGetFloatv (GL_MODELVIEW_MATRIX, a);
      ArrayToMtx44(a, &m);
    Mtx44 y = ObjVec[i]->GetTransform();
    ObjVec[i]->VtxVec[j] = ObjVec[i]->ModelVertsVec[j];
    ObjVec[i]->VtxVec[j].vertex = Mtx44MultPoint(ObjVec[i]->ModelVertsVec[j].vertex, y);
    }
    glPopMatrix();
  }

    //draw selected object in wireframe
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3,GL_FLOAT,sizeof(Vertex),&ObjVec[ObjPos]->VtxVec[0].vertex);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, ObjVec[ObjPos]->VtxVec.size());

  glDisableClientState(GL_VERTEX_ARRAY);
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  GL_ERROR();
  //draw
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  for(unsigned i = 0; i < ObjVec.size() - 1; ++i)
  {
     glVertexPointer(3,GL_FLOAT,sizeof(Vertex),&ObjVec[i]->VtxVec[0].vertex);
     glNormalPointer(GL_FLOAT,sizeof(Vertex),&ObjVec[i]->VtxVec[0].normal);
     glColorPointer(4,GL_FLOAT,sizeof(Vertex),&ObjVec[i]->VtxVec[0].color);
       glDrawArrays(GL_TRIANGLE_STRIP, 0, ObjVec[i]->VtxVec.size());
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  for(unsigned i = 0; i < ObjVec.size() - 2; ++i)
  {
    if(MPR(ObjVec[i], ObjVec[i + 1]))
      std::cout << "intersect" << std::endl;
    else
    std::cout << "no-intersect" << std::endl;
  }
  ///
  GL_ERROR();
  // terminate the shader
    glUseProgram(0);

  }

  // ---------------------------------------------------------------------------
  void Graphics::LoadAssets(void)
  {

  //create shader instance
  Shader = new Shaders();
  //intitialize shaders
  Shader->SPrograms.push_back(Shader->InitShaders("data/shaders/phong.vs", "data/shaders/phong.fs"));

  Vec3 min;
  Vec3 max;

  GLfloat a[16];
  Mtx44 m;

  glMatrixMode(GL_MODELVIEW);
  for(unsigned i = 0; i < ObjVec.size() - 1; ++i)
  {
    glPushMatrix();
    glTranslatef(ObjVec[i]->Position.x, ObjVec[i]->Position.y, ObjVec[i]->Position.z);
    glRotatef(ObjVec[i]->RotAngle, ObjVec[i]->RotAxis.x, ObjVec[i]->RotAxis.y, ObjVec[i]->RotAxis.z);
    glScalef(ObjVec[i]->Scale.x, ObjVec[i]->Scale.y, ObjVec[i]->Scale.z);
    Shapes::Draw(ObjVec[i]);
    glPopMatrix();

    ObjVec[i]->VtxVec.reserve(ObjVec[i]->ModelVertsVec.size());

    for(unsigned j = 0; j < ObjVec[i]->ModelVertsVec.size(); ++j)
    {
    glGetFloatv (GL_MODELVIEW_MATRIX, a);
      ArrayToMtx44(a, &m);
    ObjVec[i]->VtxVec.push_back(ObjVec[i]->ModelVertsVec[j]);
    ObjVec[i]->VtxVec[j].vertex = Mtx44MultPoint(ObjVec[i]->ModelVertsVec[j].vertex, m);
    }

    //find min and max of the object
    min.x = FLT_MAX;
    min.y = FLT_MAX;
    min.z = FLT_MAX;
    max.x = -FLT_MAX;
    max.y = -FLT_MAX;
    max.z = -FLT_MAX;

    //get min and max values of the object
    for(unsigned j = 0; j < ObjVec[i]->VtxVec.size(); ++j)
    {
      //x-axis
      if(ObjVec[i]->VtxVec[j].vertex.x < min.x)
          min.x = ObjVec[i]->VtxVec[j].vertex.x;
      if(ObjVec[i]->VtxVec[j].vertex.x > max.x)
      max.x = ObjVec[i]->VtxVec[j].vertex.x;
      //y-axis
      if(ObjVec[i]->VtxVec[j].vertex.y < min.y)
          min.y = ObjVec[i]->VtxVec[j].vertex.y;
      if(ObjVec[i]->VtxVec[j].vertex.y > max.y)
      max.y = ObjVec[i]->VtxVec[j].vertex.y;
      //z-axis
      if(ObjVec[i]->VtxVec[j].vertex.z < min.z)
          min.z = ObjVec[i]->VtxVec[j].vertex.z;
      if(ObjVec[i]->VtxVec[j].vertex.z > max.z)
      max.z = ObjVec[i]->VtxVec[j].vertex.z;
    }

    ObjVec[i]->aabb.radii = ((max - min)/2.0f);
    ObjVec[i]->aabb.center  = (min + ObjVec[i]->aabb.radii);

  }


  }

  // ---------------------------------------------------------------------------
  void Graphics::UnloadAssets(void)
  {
    //delete the shaders
  delete Shader;

  //free objects
  for(unsigned i = 0; i < ObjVec.size(); ++i)
    delete ObjVec[i];

  delete Cam;
  }

  // ---------------------------------------------------------------------------
  void Graphics::RecieveMessage(Message* m)
  {
    //send the message to the camera
  Cam->RecieveMessage(m);
    switch(m->MessageId)
  {
      case Mid::CharacterKey:
    {
    // Cast to the derived message type
      MessageCharacterKey * key = (MessageCharacterKey*)m;
    if(key->character == SDLK_1 && key->KeyPressed)
    {
    }
    else if(key->character == SDLK_2 && key->KeyPressed)
    {
    }
    else if(key->character == SDLK_KP_PLUS && key->KeyPressed)
    {
      if(ObjPos < ObjVec.size() - 2)
        ++ObjPos;
      else
      ObjPos = 0;  
    }
    else if(key->character == SDLK_KP_MINUS && key->KeyPressed)
    {
      if(ObjPos > 0)
        --ObjPos;
      else
      ObjPos = ObjVec.size() - 2;  
    }
    else if(key->character == SDLK_j && key->KeyPressed)
    {
      ObjVec[ObjPos]->Position.x -= 2;
    }
      else if(key->character == SDLK_l && key->KeyPressed)
    {
      ObjVec[ObjPos]->Position.x += 2;

      ///this is used to calculate new bounding box for object
      //Vec3 min,max;
      //min.x = FLT_MAX;
        //   min.y = FLT_MAX;
        //   min.z = FLT_MAX;
        //   max.x = -FLT_MAX;
        //   max.y = -FLT_MAX;
        //   max.z = -FLT_MAX;
      //for(unsigned i = 0; i < ObjVec[ObjPos]->VtxVec.size(); ++i)
      //{
      //  if(ObjVec[ObjPos]->VtxVec[i].vertex.x < min.x)
          //          min.x = ObjVec[ObjPos]->VtxVec[i].vertex.x;
        //     if(ObjVec[ObjPos]->VtxVec[i].vertex.x > max.x)
      //    max.x = ObjVec[ObjPos]->VtxVec[i].vertex.x;
        //     //y-axis
        //     if(ObjVec[ObjPos]->VtxVec[i].vertex.y < min.y)
          //          min.y = ObjVec[ObjPos]->VtxVec[i].vertex.y;
        //     if(ObjVec[ObjPos]->VtxVec[i].vertex.y > max.y)
      //    max.y = ObjVec[ObjPos]->VtxVec[i].vertex.y;
        //     //z-axis
        //     if(ObjVec[ObjPos]->VtxVec[i].vertex.z < min.z)
          //          min.z = ObjVec[ObjPos]->VtxVec[i].vertex.z;
        //     if(ObjVec[ObjPos]->VtxVec[i].vertex.z > max.z)
      //    max.z = ObjVec[ObjPos]->VtxVec[i].vertex.z;
      //}

      //ObjVec[ObjPos]->aabb.radii   = ((max - min)/2.0f);
     //   ObjVec[ObjPos]->aabb.center  = (min + ObjVec[ObjPos]->aabb.radii);
    }
    else if(key->character == SDLK_i && key->KeyPressed)
    {
      ObjVec[ObjPos]->Position.y += 2;
    }
      else if(key->character == SDLK_k && key->KeyPressed)
    {

      ObjVec[ObjPos]->Position.y -= 2;
    }
    else if(key->character == SDLK_o && key->KeyPressed)
    {
      ObjVec[ObjPos]->Position.z += 2;
    }
    else if(key->character == SDLK_u && key->KeyPressed)
    {
      ObjVec[ObjPos]->Position.z -= 2;
    }
    }
  }
  }

  // ---------------------------------------------------------------------------
  void Graphics::ReadScene(std::string filename)
  {
    //file pointer to infile
  FILE* infile;
  
  //open the input file for reading
    infile = fopen(filename.c_str(), "r");

  //if the input file fails to open
  if(!infile)
  {
      std::cout << "error: file could not be opened" << std::endl;
    return;
  }

  //read from the file
  while(!feof(infile))
  {
    Object* obj = new Object;
    fscanf(infile,"%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &obj->Type, &obj->SubDivions, &obj->Position.x, &obj->Position.y,&obj->Position.z, 
      &obj->Scale.x, &obj->Scale.y, &obj->Scale.z, &obj->RotAxis.x, &obj->RotAxis.y, &obj->RotAxis.z, &obj->RotAngle, &obj->Color.x, &obj->Color.y, &obj->Color.z, &obj->Color.w);
    
    //if(obj->Type >= 0)
      ObjVec.push_back(obj);
    
  }


  fclose(infile);
  
  }
  bool Graphics::MPR(Object* a, Object* b)
  {
    //create initial portal
  if(InitialPortal(a, b))
  {
    portal.DrawPortal();
    return true;
  }

  //Discover better portal
  if(!Discovery(a,b))
  {
    portal.DrawPortal();
    return false;
  }
  
  //portal.DrawPortal();
  //Refinement
  portal.DrawPortal();
  return Refinement(a,b);
  }
  bool Graphics::InitialPortal(Object* a, Object* b)
  {
  //for our initial portal we will need a center and 3 points
    Vec3 sp1,sp2,sv,origin,temp;

  //get the center of the portal
  portal.center = a->Position - b->Position;

  //get the first support vector used to find farthest vertex
  //of the object in the given direction, initial is origin - center
  //because we want to try create our portal in the direction of the origin
  sv = origin - portal.center;

  //obtain the support points used to find our first point in our portal
  sp1 = FindSupport(sv, a);
  sp2 = FindSupport(sv.Neg(), b);
  portal.p1 = sp1 - sp2;

    portal.center.Cross(portal.p1,&temp);
  if(temp.IsZero())
    if(portal.center.Dot(portal.p1) < 0)
      return true;

  //get new support vector, perpindicular vector to origin, center and p1
  sv  = temp;
  sp1 = FindSupport(sv, a);
  sp2 = FindSupport(sv.Neg(), b);
  portal.p2 = sp1 - sp2;

  (portal.p1 - portal.center).Cross(portal.p2 - portal.center, &temp);
  //our next support vector comes from the normal of our first plane on the portal
  sv = temp;
  sp1 = FindSupport(sv, a);
  sp2 = FindSupport(sv.Neg(), b);
  portal.p3 = sp1 - sp2;
    
  return false;
  } 

  bool Graphics::Discovery(Object* a, Object* b)
  {
  Vec3 r = portal.center.Neg();
  Vec3 n1,n2,n3,temp;

  int count = 50;
  while(--count > 0)
  {
    //compute normals of portals planes
    (portal.p1 - portal.center).Cross((portal.p2 - portal.center),&n1);
    (portal.p2 - portal.center).Cross((portal.p3 - portal.center),&n2);
    (portal.p3 - portal.center).Cross((portal.p1 - portal.center),&n3);

    //get new points for portal if necessary
    if(r.Dot(n1) > 0)
    {
    portal.p3 = (FindSupport(n1, a) - FindSupport(n1.Neg(),b));
    temp = portal.p1;
    portal.p1 = portal.p2;
    portal.p2 = temp;
    }
    else if(r.Dot(n2) > 0)
    {
    portal.p1 = (FindSupport(n2, a) - FindSupport(n2.Neg(),b));
    temp = portal.p2;
    portal.p2 = portal.p3;
    portal.p3 = temp;
    }
    else if(r.Dot(n3) > 0)
    {
    portal.p2 = (FindSupport(n3, a) - FindSupport(n3.Neg(),b));
    temp = portal.p1;
    portal.p1 = portal.p3;
    portal.p3 = temp;
    }
    else
    return true;
  
  }

  return false;
  }
  bool Graphics::Refinement(Object* a, Object* b)
  {
  Vec3 n,p,temp;
  //arbitrary loop
    for(unsigned i = 0; i < 50; ++i)
  {
    //normal of the portal
    (portal.p3 - portal.p1).Cross(portal.p2 - portal.p1, &n);
    
    //check if origin is inside tetrahedron
    if(portal.p1.Dot(n) >= 0)
      return true;

    //check if origin is inside portal
    if(portal.p1.Dot(n) < Epsilon && portal.p1.Dot(n) > -Epsilon)
      return false;

    //new point in the direction of the normal
    p = FindSupport(n, a) - FindSupport(n.Neg(), b);

    //origin on far side of support plane
    if(p.Dot(n) < 0)
      return false;

    //origin is in p,portal.center,portal.p1 positive half space
    p.Cross(portal.p1,&temp);
    if(portal.center.Dot(temp) > 0)
    {
    //origin is in p,portal.center,portal.p2 positive half space
      p.Cross(portal.p2, &temp);
    if(portal.center.Dot(temp) < 0)
      portal.p3 = p;
    else
      portal.p1 = p;
    }
    else
    {
      p.Cross(portal.p3,&temp);
    if(portal.center.Dot(temp) > 0)
      portal.p2 = p;
    else
      portal.p1 = p;
    }

  }
    
  return true;
  }

  Vec3 Graphics::FindSupport(Vec3 sv, Object* obj)
  {
  float temp, max = -FLT_MAX;
  unsigned index = 0;
  Mtx44 m,t;

  //bring sv to objects local space
  t = obj->GetTransform();
  Mtx44Inverse(&t, &m);

  sv = Mtx44MultPoint(sv, m);

  for(unsigned i = 0; i < obj->VtxVec.size(); ++i)
  {
    temp = sv.Dot(obj->ModelVertsVec[i].vertex);
    if(temp > max)
    {
      max = temp;
    index = i;
    }
  }

    return obj->VtxVec[index].vertex;
  }

  /////////////End Graphics class/////////////////////////
  ////////////Begin Image class /////////////////////////
  Image::Image() :
           mpData(0), 
           mBPP(0), 
           mSizeX(0), 
           mSizeY(0)
         {
         }

  // ---------------------------------------------------------------------------
  Image::~Image()
  {
    if (mpData)
    delete [] mpData;
  }

  // ---------------------------------------------------------------------------
  Image* Image::Create(unsigned long sizeX, unsigned long sizeY,unsigned long bpp)
  {
    //SFW_ASSERT_PARM(sizeX && sizeY && ((bpp == 24) || (bpp == 32)));

  Image* pImage = new Image;
  //SFW_ASSERT_ALLOC(pImage);
  pImage->mBPP  = bpp;
  pImage->mSizeX  = sizeX;
  pImage->mSizeY  = sizeY;

  pImage->mpData  = new char[pImage->mSizeX * pImage->mSizeY * pImage->mBPP / 8];
  //SFW_ASSERT_ALLOC(pImage->mpData);

  // zero out the memory
  memset(pImage->mpData, 0, sizeof(char) * pImage->mSizeX * pImage->mSizeY * pImage->mBPP / 8);
  
  return pImage;
  }

  // ---------------------------------------------------------------------------
  Image* Image::Load(const char* pName)
  {
    //SFW_ASSERT_PARM(pName);
    
  Image* pImage = new Image;
  //SFW_ASSERT_ALLOC(pImage);

  // check the extension
  const char* pExt = pName + strlen(pName) - 4;
  //SFW_ASSERT_MESG(stricmp(pExt, ".TGA") == 0, "Can only load .TGA file!!");

  FILE* pFile = fopen(pName, "rb");
  //SFW_ASSERT_MESG(pFile, "Cannot open '%s'\n", pName);

  // get the file size
  fseek(pFile, 0, SEEK_END);
  long fileSize = ftell(pFile);
  fseek(pFile, 0, SEEK_SET);

  char* pFileData = new char [fileSize];
  //SFW_ASSERT_ALLOC(pFileData);

  // read in the data
  unsigned readSize = (unsigned)(fread(pFileData, 1, fileSize, pFile));
  //SFW_ASSERT_MESG(readSize == fileSize, "Error in reading '%s'\n", pName);

  if (pImage->loadTGA(pFileData, fileSize))
    return pImage;

  // deallocate the image
  delete pImage;

  return 0;
  }

  // ---------------------------------------------------------------------------
  void Image::Save(const char* pName)
  {
    //SFW_ASSERT_PARM(pName);

  // check the extension
  const char* pExt = pName + strlen(pName) - 4;

  if (_stricmp(pExt, ".TGA") == 0)
    saveTGA(pName);
  else if (_stricmp(pExt, ".TXT") == 0)
    saveTXT(pName);
  //else
    //SFW_HALT("Unsupported type!! (%s)", pExt);
  
  return;
  }

  // ---------------------------------------------------------------------------
  void Image::Free(Image* pImage)
  {
  if (!pImage)
    return;

  // deallocate the image
  delete pImage;
  }

  // ---------------------------------------------------------------------------
  bool Image::loadTGA(char* pData, unsigned dataSize)
  {
  //SFW_ASSERT_PARM(pData && dataSize)

  // get the image type
  char imageType = pData[2];
  //SFW_ASSERT_MESG(imageType == 2, "Only support uncompressed, true-color image");

  // get the bits per pixel
  mBPP = pData[16];
  //SFW_ASSERT_MESG((mBPP == 24) || (mBPP == 32), "Only support 24 or 32 bits image");

  // get image size
  mSizeX = (pData[13] << 8) | pData[12];
  mSizeY = (pData[15] << 8) | pData[14];

  // get the pointer to the image data area
  // * 18 is the header size
  // * the '0' entry is the number of bytes in the image id field (ignored!)
  char* pImageData = pData + 18 + pData[0];

  // allocate memory for the data
  mpData = new char[mSizeX * mSizeY * mBPP / 8];
  //SFW_ASSERT_ALLOC(mpData);

  // get the image descriptor to get the orientation
  // * bit 5 (0 = bottom, 1 = top)
  // * bit 4 (0 = left    1 = right)
  char desc = pData[17];
  unsigned rowSize = mSizeX * mBPP / 8;

  // check if need to mirror the image vertically
  if ((desc & 0x20) == 0)
  {
    // mirror data upside down
    for(unsigned y = 0; y < mSizeY; ++y)
    {
      unsigned* pSrc = (unsigned*)(pImageData + y * rowSize);
    unsigned* pDst = (unsigned*)(mpData     + (mSizeY - 1 - y) * rowSize);
    memcpy(pDst, pSrc, rowSize);
    }
  }
  else
  {
    memcpy(mpData, pImageData, mSizeY * rowSize);
  }

  // check if need to mirror the image horizontally
  if (desc & 0x10)
  {
    for (unsigned y = 0; y < mSizeY; ++y)
    {
      for (unsigned x = 0; x < mSizeX / 2; ++x)
    {
      char* pSrc = mpData + y * rowSize + x * mBPP / 8;
      char* pDst = mpData + y * rowSize + (mSizeX - 1 - x) * mBPP / 8;
        
      pSrc[0] ^= pDst[0]; pDst[0] ^= pSrc[0]; pSrc[0] ^= pDst[0];
      pSrc[1] ^= pDst[1]; pDst[1] ^= pSrc[1]; pSrc[1] ^= pDst[1];
      pSrc[2] ^= pDst[2]; pDst[2] ^= pSrc[2]; pSrc[2] ^= pDst[2];
        
      if (mBPP == 32)
      {
        pSrc[3] ^= pDst[3];
      pDst[3] ^= pSrc[3];
      pSrc[3] ^= pDst[3];
      }
    }
    }
  }

    return true;
  }

  // ---------------------------------------------------------------------------
  bool Image::saveTGA(const char* pName)
  {
  FILE* pFile = fopen(pName, "wb");
  //SFW_ASSERT_MESG(pFile, "Cannot open '%s'\n", pName);

  long header[18];
  memset(header, 0, sizeof(long) * 18);

  header[2] = 2;

  header[12] = mSizeX & 0x0000FF;
  header[13] = (mSizeX >> 8) & 0x00FF;
  header[14] = mSizeY & 0x0000FF;
  header[15] = (mSizeY >> 8) & 0x00FF;

  header[16] = mBPP;

  // set image orientation to (top, left)
  // * bit 5 (0 = bottom, 1 = top)
  // * bit 4 (0 = left    1 = right)
  header[17] = 0x20;

  if(mBPP == 32)
    header[17] |= 0x08;
  
  unsigned written = fwrite(header, 18, 1, pFile);
  //SFW_ASSERT_MESG(written, "fail to write!!");

  written = fwrite(mpData, mSizeX * mSizeY * mBPP / 8, 1, pFile);
  //SFW_ASSERT_MESG(written, "fail to write!!");

  fclose(pFile);

  return true;
  }

  // ---------------------------------------------------------------------------
  bool Image::saveTXT(const char* pName)
  {
    FILE* pFile = fopen(pName, "wt");
  //SFW_ASSERT_MESG(pFile, "Cannot open '%s'\n", pName);

  fprintf(pFile, "// Image width:  %d\n", mSizeX);
  fprintf(pFile, "// Image height: %d\n", mSizeY);
  fprintf(pFile, "// Image bpp:    %d\n", mBPP);
  
  int bytePerRow = mSizeX * mBPP / 8;

  for(unsigned y = 0; y < mSizeY; ++y)
  {
    for(unsigned x = 0; x < mSizeX; ++x)
    {
      for(unsigned b = 0; b < mBPP / 8; ++b)
    {
      fprintf(pFile, "0x%0.2x", mpData[bytePerRow * y + x * mBPP / 8 + b]);
          
      if ((y == mSizeY - 1) && (x == mSizeX - 1) && (b == mBPP / 8 - 1))
        break;

       fprintf(pFile, ", ");
    }
    }

    fprintf(pFile, "\n");
  }

  fprintf(pFile, "\n");

  return true;
  }
  /////////////End Image class/////////////////////////

}//namespace