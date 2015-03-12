/////////////////////////////////////////////////////////////
// File  : Shaders.cpp                                     //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Shader function implementations                 //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "Shaders.h"


namespace Framework
{

  Shaders::Shaders()
  { 
    fShaderSource = 0;
    vShaderSource = 0;
  }
  Shaders::~Shaders()
  {
  }
  int Shaders::GetFileLength(const char* filename)
  {
    FILE* file;
  file = fopen( filename, "rb" );
  // set the file pointer to end of file
  //to get file size
    fseek( file, 0, SEEK_END );
    int size = ftell( file );

  fclose(file);

  return size;
  }
  char* Shaders::loadshader(const char* filename)
  {
    int size = GetFileLength(filename);

  std::ifstream infile(filename,std::ifstream::in);

    //allocate our shaders memory
  char* ShaderSource = new char[size];

    for(unsigned i = 0; infile.good(); ++i)
  {
    ShaderSource[i] = infile.get();
    if(infile.eof())
      ShaderSource[i] = 0;
  }
    
    infile.close();

    return ShaderSource;
  }
  int Shaders::unloadshader(const char* ShaderSource)
  {
    if (ShaderSource != 0)
      delete[] ShaderSource;

    ShaderSource = 0;
    return 0;
  }
  void Shaders::CompileShader(GLint shader)
  {
    GLint compiled;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_TRUE)
      return;// it compiled

    else if(compiled == GL_FALSE)
    {
      GLsizei slen = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &compiled);       

      GLchar* compiler_log = new GLchar[compiled];

    std::cout << "compile_failed_creating_log" << std::endl;
      glGetShaderInfoLog(shader, compiled, &slen, compiler_log);
    std::cout << "compiler_log:\n" << static_cast<char *>(compiler_log) << std::endl;
      delete [] compiler_log;
    }

  }
  void Shaders::LinkShader(GLuint program)
  {
    GLint linked = 1;

    //link to program
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE)
      std::cout << "link successful" << std::endl;    
    else 
    {
    GLsizei slen = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH , &linked);       

      GLchar* linker_log = new GLchar[linked];

    std::cout << "link_failed_creating_log" << std::endl;
      glGetProgramInfoLog(program, linked, &slen, linker_log);
    std::cout << "link_log:\n" << static_cast<char *>(linker_log) << std::endl;
      delete [] linker_log;
    }

  }
  GLuint Shaders::InitShaders(const char* vs_filename, const char* fs_filename)
  {
    //load both of our shaders from a file
  fShaderSource = loadshader(fs_filename);
  vShaderSource = loadshader(vs_filename);

  //create the shaders and our program
  void* p =  glCreateShader;
  if(!p) __asm int 3
    fShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
  vShaderObject = glCreateShader(GL_VERTEX_SHADER);
    GLuint Program = glCreateProgram();

  const char* fss = const_cast<const char*>(fShaderSource);
  const char* vss = const_cast<const char*>(vShaderSource);

    glShaderSource(fShaderObject, 1, &fss, NULL);
  glShaderSource(vShaderObject, 1, &vss, NULL);
    
    //compile the shaders
  CompileShader(fShaderObject);
  CompileShader(vShaderObject);


  //attach the shaders to our program 
  glAttachShader(Program, vShaderObject);
    glAttachShader(Program, fShaderObject);

    //link the shaders
  LinkShader(Program);

    //de-allocate memory for shaders
  unloadshader(fShaderSource);
    unloadshader(vShaderSource);

  return Program;
  }

}//namespace

