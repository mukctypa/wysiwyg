#ifndef _GAME_SCENE_H__
#define _GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    

	//play game callback
	void menuPlayeCallback( CCObject * pSender );


    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC( GameScene );
};





#endif