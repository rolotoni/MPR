/////////////////////////////////////////////////////////////
// File  : Core.h                                          //
// Author: Chris Peters, Jesse Harrison                    //
// Date  : 1/15/2012                                       //
// Breif : The core of the engine                          //
/////////////////////////////////////////////////////////////

#ifndef CORE_H
#define CORE_H

#include "System.h"

namespace Framework
{
	///The core manages all the systems. Updating them, routing messages, and
	///destroying them when the program ends.
	class CoreEngine
	{
	  public:
	    CoreEngine();
		~CoreEngine();
		///Update all the systems until the program is no longer active.
		void GameLoop();
		///Destroy all systems in reverse order that they were added.
		void DestroySystems();
		///Broadcasts a message to all systems.
		void BroadcastMessage(Message* m);
		///Adds a new system to the game.
		void AddSystem(ISystem* system);
		///Initializes all systems in the game.
		void Initialize();

	  private:
		//Tracks all the systems the program uses
		std::vector<ISystem*> Systems;
		//The last time the game was updated
		unsigned LastTime;
		//Is the game running (true) or being shut down (false)?
		bool GameActive;
	};

	///Message to tell the program to quit
	class MessageQuit : public Message
	{
	  public:
		MessageQuit() : Message(Mid::Quit) {};
	};

	//A global pointer to the instance of the core
	extern CoreEngine* CORE;

}//namespace

#endif