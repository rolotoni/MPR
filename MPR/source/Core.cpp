/////////////////////////////////////////////////////////////
// File  : Core.cpp                                        //
// Author: Chris Peters, Jesse Harrison                    //
// Date  : 1/15/2012                                       //
// Breif : The core of the engine                          //
/////////////////////////////////////////////////////////////

#include "Precompiled.h"
#include "Core.h"


namespace Framework
{

  //A global pointer to the core
  CoreEngine* CORE;

  CoreEngine::CoreEngine()
  {
    LastTime = 0;
    GameActive = true;
    CORE = this; //Set the global pointer
  }

  CoreEngine::~CoreEngine()
  {
    //Nothing for the destructor to do
  }

  void CoreEngine::Initialize()
  {
    for (unsigned i = 0; i < Systems.size(); ++i)
      Systems[i]->Initialize();
  }

  void CoreEngine::GameLoop()
  {
    //Initialize the last time variable so our first frame
    //is "zero" seconds (and not some huge unknown number)
    LastTime = SDL_GetTicks();

    while (GameActive)
    {
      //Get the current time in milliseconds
      unsigned currenttime = SDL_GetTicks();
      //Convert it to the time passed since the last frame (in seconds)
    float dt = (currenttime - LastTime) / 1000.0f;
    //Update the when the last update started
    LastTime = currenttime;

    //Update every system and tell each one how much
    //time has passed since the last update
    for (unsigned i = 0; i < Systems.size(); ++i)
        Systems[i]->Update(dt);
    }

  }

  void CoreEngine::BroadcastMessage(Message* message)
  {
    //The message that tells the game to quit
    if (message->MessageId == Mid::Quit)
      GameActive = false;

    //Send the message to every system--each
    //system can figure out whether it cares
    //about a given message or not
    for (unsigned i = 0; i < Systems.size(); ++i)
      Systems[i]->RecieveMessage(message);
  }

  void CoreEngine::AddSystem(ISystem* system)
  {
    //Add a system to the core to be updated
    //every frame
    Systems.push_back(system);
  }

  void CoreEngine::DestroySystems()
  {     
    //Delete all the systems in reverse order
    //that they were added in (to minimize any
    //dependency problems between systems)
    for(std::vector<ISystem*>::reverse_iterator rit = Systems.rbegin(); rit != Systems.rend(); ++rit)
      delete *rit;
    /*for (unsigned i = 0; i < Systems.size(); ++i)
      delete Systems[Systems.size()-i-1];*/
  }

}//namespace