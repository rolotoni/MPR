/////////////////////////////////////////////////////////////
// File  : SDLSystem.cpp                                   //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : SDL implementations such as creating a window   //
//         and event handling                              //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "SDLWindowSystem.h"

namespace Framework
{

  SDLWindowSystem* WINDOW = NULL;

  SDLWindowSystem::SDLWindowSystem(int width, int height) : Width_(width), Height_(height) 
  {
  WINDOW = this;
    Window_ = NULL;
  }
  SDLWindowSystem::~SDLWindowSystem()
  {
    SDL_Quit();
  }

  void SDLWindowSystem::Activate()
  {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  Window_ = SDL_CreateWindow("Jesse_Harrison-MPR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width_, Height_, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  Context_ = SDL_GL_CreateContext(Window_);

  }

  void SDLWindowSystem::Event(SDL_Event* Event)
  {
  }

  void SDLWindowSystem::Initialize()
  {
    SDL_Init(SDL_INIT_EVERYTHING);
  Activate();
  }

  void SDLWindowSystem::Update(float dt)
  { 
  SDL_GL_SwapWindow(Window_);
  }
  void SDLWindowSystem::RecieveMessage(Message* message)
  {
    return;
  }
  void SDLWindowSystem::ToggleFullScreen(bool enable)
  {
    /*if(enable)
      return SDL_SetWindowFullscreen(Window_, SDL_TRUE) == 0;
    else
      return SDL_SetWindowFullscreen(Window_, SDL_FALSE) == 0;*/
  }

  int SDLWindowSystem::GetWidth()
  {
    return Width_;
  }
  int SDLWindowSystem::GetHeight()
  {
    return Height_;
  }

}//namespace

