#include "GameEngine.h"


GameEngine & GameEngine::getInstance()
{
	static GameEngine instance;
	return instance;
}

void GameEngine::init()
{
	//init all stuf
	this->m_state = ReadyToStart;
}


void GameEngine::start()
{
	//start game - create first set of letters, start timer
	this->m_state = InGame;
}


void GameEngine::logic()
{
	switch ( this->m_state )
	{
		case ReadyToStart:
		{
			//do nothing: game not started
			break;
		}
		case InGame:
		{
			//check if game field is not full
			break;
		}
	}
}
