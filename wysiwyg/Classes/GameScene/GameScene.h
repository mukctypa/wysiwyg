#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;

#include "Models.h"
#include "LetterSprite.h"

class GameScene : public cocos2d::CCLayer
{
protected:
	CCSprite * m_pTargetSprite;
	LetterSequence m_selectedLetters;
	CCLabelTTF * m_pSelectedLettersLabel;
	CCLabelTTF * m_pPointsLabel;
	CCLabelTTF * m_pTimerLabel;
	
	void updateSelectedLetters();
	void updatePoints(  );

	//TODO
	std::string m_letters; 
	std::list<Word> my_list;

	unsigned int m_points;
	unsigned int m_seconds;

	void updateLetters();
	LetterSprite * m_lettersSpriteArray[16];
	void updateTimer( float p  );
public:
	virtual bool init();  
	GameScene();

    static cocos2d::CCScene* scene();
    

	//ok callback
	void menuOkCallback( CCObject * pSender );
	
	//clear callback
	void menuClearCallback( CCObject * pSender );

	void addSpriteAtPosition( unsigned int x, unsigned int y, AbstractLetter * letter, unsigned int letter_position );

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    
	void dragAndDropListner( CCObject * obj );

	CREATE_FUNC( GameScene );

	void engineLogic();

	void clearLetters();
};





#endif