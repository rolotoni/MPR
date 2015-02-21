/////////////////////////////////////////////////////////////
// File  : System.h                                        //
// Author: Chris Peters, Jesse Harrison                    //
// Date  : 1/15/2012                                       //
// Breif : Object Messaging System used by engine          //
//         for cross game object and system communication. //
//         Messages are passed as base class pointers and  //
//         downcast to their derived types by the receiver //
//         usually inside of a switchblock.                //
/////////////////////////////////////////////////////////////

#ifndef MESSAGE_H
#define MESSAGE_H

namespace Framework
{
	namespace Mid // Message id
	{
		enum MessageIdType
		{
			None,
			Quit,
			Collide,
			CharacterKey,
			MouseButton,
			MouseMove
		};
	}

	///Base message class. New message types are defined by deriving from this
	///class and mapping defined an element of the MessageIdType enumeration.
	class Message
	{
	public:
		Message(Mid::MessageIdType id) : MessageId(id){};
		Mid::MessageIdType MessageId;
		virtual ~Message(){};
	};

}

#endif
