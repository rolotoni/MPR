/////////////////////////////////////////////////////////////
// File  : SDLInput.cpp                                    //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Input handling                                  //
/////////////////////////////////////////////////////////////

//Includes
#include "Precompiled.h"
#include "SDLInput.h"
#include "Camera.h"



namespace Framework
{
  SDLInput::SDLInput()
  {
  }

  // ---------------------------------------------------------------------------
  SDLInput::~SDLInput()
  {
  }

  // ---------------------------------------------------------------------------
  void SDLInput::Initialize()
  {
  }

  // ---------------------------------------------------------------------------
  void SDLInput::Update(float dt)
  {
  SDL_PumpEvents();
    SDL_Event Event;    //The SDL event that we will poll to get events.
 
    while (SDL_PollEvent(&Event))   //Poll our SDL key event for any keystrokes.
    {
      switch(Event.type)
    {
      case SDL_QUIT:
    {
        MessageQuit q;
        CORE->BroadcastMessage(&q);
      break;
    }
        case SDL_KEYDOWN:
        case SDL_KEYUP:
      {
      MessageCharacterKey key;
          key.character = Event.key.keysym.sym;
      key.KeyPressed = (Event.type == SDL_KEYUP) ? 0 : 1;
      CORE->BroadcastMessage(&key);
      break;
    }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    {
      MouseButton mb;
      mb.ButtonIsPressed = (Event.button.state == SDL_RELEASED) ? 0 : 1;
      mb.MousePosition = Vec2((float)Event.motion.x,(float)Event.motion.y);
      if(Event.type == SDL_BUTTON_LEFT)
      {
        mb.MouseButtonIndex = mb.LeftMouse;
      }
      else if(Event.type == SDL_BUTTON_RIGHT)
      {
        mb.MouseButtonIndex = mb.RightMouse;
      }
      CORE->BroadcastMessage(&mb);
      break;
    }
    case SDL_MOUSEMOTION:
    {
      MouseMove m(Vec2((float)Event.motion.xrel,(float)Event.motion.yrel));
      CORE->BroadcastMessage(&m);
      break;
    }
    }
  }

  }

  // ---------------------------------------------------------------------------
  void SDLInput::RecieveMessage(Message* m)
  {

  switch(m->MessageId)
  {
      case Mid::CharacterKey:
    {
    // Cast to the derived message type
      MessageCharacterKey * key = (MessageCharacterKey*)m;
    if(key->character == SDLK_ESCAPE)
    {
      MessageQuit q;
      CORE->BroadcastMessage(&q);
    }
        break;
    }
     case Mid::MouseButton:
     {
     break;
     }
  }
  
  }

  // ---------------------------------------------------------------------------

}//namespace

