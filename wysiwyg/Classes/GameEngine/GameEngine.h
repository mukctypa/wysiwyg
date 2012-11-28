#ifndef __GAMEENGINE__H__
#define __GAMEENGINE__H__

#include "MessageBus.h"

typedef enum
{
	ReadyToStart,
	InGame,
	VaidateUserInput,
	AddLetters,
	RemoveLetters,
	GameEnd,
} GameState;


typedef enum
{
	ValidateWord,
	Clear
} UserEventType;

typedef enum
{
	DrawLetters,
	UpdatePoints,
	GameEnded
} EngineEventType;

struct EngineMessage
{
	GameState state;
	void * arg;	
};


struct UserMessage
{
	UserEventType type;
	void * arg;
};


class GameEngine
{

protected:
	void logic();
	void logicWrapper();

	MessageBus<EngineMessage, UserMessage> m_bus;

	GameState m_state;
	GameEngine() 
	{
	}

public: 
	static GameEngine & getInstance();
	void init(); 
	void start();

	EngineMessage * getMessage();
	void putMessage( const UserMessage & msg );

};

#endif