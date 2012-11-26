#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;

bool GameScene::init()
{

	/*CCLabelTTF * pLabel = CCLabelTTF::create(
		"Game scene",
		"Arial",
		10 );*/

	CCMenuItemImage * pPlayeItem = CCMenuItemImage::create(
			"play.png",
			"play_tapped.png",
			this,
			menu_selector(GameScene::menuPlayeCallback) );

	//pLabel->setPosition( ccp( 100, 100 ) );

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pPlayeItem->setPosition( CCPointZero );

	CCMenu* pMenu = CCMenu::create(pPlayeItem, NULL);
    pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
  
	this->addChild(pMenu, 1);

	//this->addChild( pLabel );



	return true;
}

CCScene* GameScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameScene *layer = GameScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

void GameScene::menuPlayeCallback( CCObject * pSender )
{
	CCScene * pScene = GameScene::scene();

	CCDirector::sharedDirector()->replaceScene( pScene );

	return;
}
    