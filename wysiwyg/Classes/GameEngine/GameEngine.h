#ifndef __GAMEENGINE__H__
#define __GAMEENGINE__H__

typedef enum
{
	ReadyToStart,
	InGame,
	VaidateUserInput,
	AddLetters,
	RemoveLetters,
	GameEnd,
} GameState;


class GameEngine
{

protected:
	void logic();
	void logicWrapper();

	GameState m_state;
	GameEngine() 
	{
	}

public: 
	static GameEngine & getInstance();
	void init(); 
	void start();

};

#endif