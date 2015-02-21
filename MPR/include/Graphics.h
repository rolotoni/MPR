/////////////////////////////////////////////////////////////
// File  : Graphics.h                                      //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Graphics header                                 //
/////////////////////////////////////////////////////////////

#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace Framework
{
  class Camera;
  class Object;
  class Shaders;
  class BVHTree;

  class Graphics : public ISystem
  {
    public:
      Graphics();
	  ~Graphics();

	  //base class functions
	  virtual void Initialize();
	  virtual void Update(float dt);//Update the system every frame
	  virtual void RecieveMessage(Message* m);
	  virtual std::string GetName() {return "Graphics";}  
	  Camera* Cam;
      

    private:
	  void LoadAssets(void);
	  void UnloadAssets(void);
	  void DrawScene(void);
	  void ReadScene(std::string filename);
	  //vector of texture object name
      GLuint TexId[4];
	  //the shaders
	  Shaders* Shader;
	  int ScreenWidth;
	  int ScreenHeight;
	  Vec2 MousePosition;
	  std::vector<Object*> ObjVec;

	  AABB scene;

	  //Minkowski Portal Refinement
	  Portal portal;
	  bool MPR(Object* obj0, Object* obj1);
	  bool InitialPortal(Object* obj0, Object* obj1);
	  bool Discovery(Object* a, Object* b);
	  bool Refinement(Object* a, Object* b);
	  Vec3 FindSupport(Vec3, Object* obj);
	  //////////////////////////////

	  //current object
	  unsigned ObjPos;
	  
  };

  //author Sun Tjen Fam
  class Image
  {
    public:
	  // create an empty image
	  // * bpp must be 24 or 32
	  static Image*	Create(unsigned long sizeX, unsigned long sizeY, unsigned long bpp = 32);

	  // load image from disk
	  static Image*	Load(const char* pName);

	  // free previously created/loaded image
	  static void Free(Image* pImage);
	
	  // save the image to disk
	  void	Save(const char* pName);

	  const char* Data() const {	return mpData;	}
	  char* Data()	           {	return mpData;	}
	  unsigned long	BPP  () const	   {	return mBPP;	}
	  unsigned long	SizeX() const	   {	return mSizeX;	}
	  unsigned long	SizeY() const	   {	return mSizeY;	}

   private:
	  char* mpData;
	  unsigned long	mBPP;
	  unsigned long	mSizeX;
	  unsigned long	mSizeY;

	  // ---------------------------------------------------------------------------
	  Image();
	  Image(const Image& rhs);
	  ~Image();
	  // ---------------------------------------------------------------------------
	
	  bool  loadTGA(char* pData, unsigned dataSize);
	  bool	saveTGA(const char* pName);
	  bool	saveTXT(const char* pName);
  };

  #define PRINT(...)	printf(__VA_ARGS__)

  #define HALT(...)										    \
  { 														\
	PRINT("HALT:\nLine: %d\nFunc: %s\nFile: %s\n",		    \
		__LINE__, __FUNCTION__, __FILE__);					\
	if (" "#__VA_ARGS__[1]) PRINT("Mesg: "__VA_ARGS__);		\
	PRINT("\n");											\
	_getch();												\
	exit(1);												\
  }

  #define GL_ERROR(...)    										\
  {																\
	GLenum glError = glGetError();								\
	if (glError != GL_NO_ERROR)									\
	{															\
		PRINT("GL_ERROR:\nLine: %d\nFunc: %s\nFile: %s\n",	    \
			__LINE__, __FUNCTION__, __FILE__);					\
		PRINT("Code: 0x%0.8x\n", glError);						\
		PRINT("Mesg: "__VA_ARGS__);								\
		PRINT("\n");											\
		_getch();												\
		exit(1);												\
	}															\
  }


  //A global pointer to the instance of the core
  extern Graphics* GRAPHICS;

}//namespace

#endif