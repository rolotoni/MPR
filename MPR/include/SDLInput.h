/////////////////////////////////////////////////////////////
// File  : SDLInput.h                                      //
// Author: Jesse Harrison                                  //
// Date  : 1/15/2012                                       //
// Breif : Input handling                                  //
/////////////////////////////////////////////////////////////

#ifndef SDLINPUT_H
#define SDLINPUT_H

namespace Framework
{
  class SDLInput : public ISystem 
  {
    public:
	  SDLInput();
	  ~SDLInput();
 
	  //inherited functions
	  virtual void Initialize();
	  virtual void Update(float dt);//Update the system every frame
	  virtual std::string GetName() {return "SDLInput";}
	  virtual void RecieveMessage(Message* m);
	 
  };

  //Message signaling that a key is pressed.
  class MessageCharacterKey : public Message
  {
    public:
	  MessageCharacterKey() : Message(Mid::CharacterKey), KeyPressed(0){};	
	  SDLKey character;//int
	  bool KeyPressed;
  };

  //Message signaling that a mouse button state has changed.
  class MouseButton: public Message
  {
    public:
	  enum MouseButtonIndexId
	  {
	    LeftMouse,
		RightMouse
	  };
	  MouseButton(void) 
	  : Message(Mid::MouseButton) ,  MouseButtonIndex(LeftMouse) , ButtonIsPressed(false), MousePosition(Vec2()) {};

	  MouseButtonIndexId MouseButtonIndex;
	  bool ButtonIsPressed;
	  Vec2 MousePosition;
  };

  //Message signaling that the mouse has moved.
  class MouseMove: public Message
  {
    public:
	  MouseMove(Vec2 position) : Message(Mid::MouseMove) , MousePosition(position) {};	
	  Vec2 MousePosition;
  };
}

#endif