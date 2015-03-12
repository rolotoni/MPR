/////////////////////////////////////////////////////////////
// File  : System.h                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Shader function definitions                     //
/////////////////////////////////////////////////////////////

#ifndef SHADERS_H
#define SHADERS_H

namespace Framework
{
  class Shaders
  {
    public:
      Shaders();
    ~Shaders();
    
      GLuint InitShaders(const char* vs_filename, const char* fs_filename);
    
    //vector of shader programs
    std::vector<GLuint> SPrograms;

    private:
    int GetFileLength(const char* filename);
      char* loadshader(const char* filename);
      int unloadshader(const char* ShaderSource);
      void CompileShader(GLint shader);
      void LinkShader(GLuint program);
    int fShaderObject;
      int vShaderObject;
      char* fShaderSource;
      char* vShaderSource;
    
  };
}

#endif