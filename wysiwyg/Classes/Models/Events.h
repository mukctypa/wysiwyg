#ifndef __EVENTS__H__
#define __EVENTS__H__

typedef enum
{
	Redraw
} GameEngieEvents;


typedef enum
{
	ValidateUserInputEvent	
} UIEvents;


typedef union
{
	GameEngieEvents engineEvent;
	UIEvents uiEvent;
} EventHolder;


class Event
{
	EventHolder event;

	//payload is placeholder where all parameters are stored.
	//convention: callee cleanups the pointer
	void * payload;
};



#endif