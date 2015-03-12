/////////////////////////////////////////////////////////////
// File  : System.h                                        //
// Author: Chris Peters, Jesse Harrison                    //
// Date  : 1/15/2012                                       //
// Breif : Base System class for all systems               //
/////////////////////////////////////////////////////////////

#ifndef SYSTEM_H
#define SYSTEM_H

#include "Message.h"

namespace Framework
{
  ///System is a pure virtual base class (which is to say, an interface) that is
  ///the base class for all systems used by the game. 
  class ISystem
  {
     public:
     //Systems can receive all message sent from the Core. 
     //See Message.h for details.
     virtual void RecieveMessage(Message* message) {};

     //All systems are updated every game frame.
     virtual void Update(float timeslice) = 0;  

     //All systems provide a string name for debugging.
     virtual std::string GetName() = 0; 

     //Initialize the system.
     virtual void Initialize(){};
    
     //All systems need a virtual destructor to have their destructor called 
     virtual ~ISystem(){}           
  };
}

#endif