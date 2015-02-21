/////////////////////////////////////////////////////////////
// File  : main.cpp                                        //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : CS350 Framework main file                       //
/////////////////////////////////////////////////////////////

//includes
#include "Precompiled.h"
#include "Core.h"
#include "SDLWindowSystem.h"
#include "SDLInput.h"
#include "Graphics.h"

using namespace Framework;

int main(int argc, char *argv[])
{
  //create core engine
  CoreEngine* engine = new CoreEngine();

  //create systems
  SDLWindowSystem* sdl_window = new SDLWindowSystem(800, 600);

  //add systems to engine
  engine->AddSystem(sdl_window);
  engine->AddSystem(new SDLInput());
  engine->AddSystem(new Graphics());

  //initialize the engine, all systems
  engine->Initialize();

  //Run the program
  engine->GameLoop();

  //Delete all the systems
  engine->DestroySystems();

  //Delete the engine itself
  delete engine;

  return 0;
}