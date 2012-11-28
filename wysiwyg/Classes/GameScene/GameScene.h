#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public cocos2d::CCLayer
{
protected:
	CCSprite * m_pTargetSprite;
    
public:
	virtual bool init();  
	GameScene();

    static cocos2d::CCScene* scene();
    

	//ok callback
	void menuOkCallback( CCObject * pSender );
	
	//clear callback
	void menuClearCallback( CCObject * pSender );

	void addSpriteAtPosition( unsigned int x, unsigned int y, char * spriteName );

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC( GameScene );
};





#endif