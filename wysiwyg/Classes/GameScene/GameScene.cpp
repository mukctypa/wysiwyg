#include "cocos2d.h"
#include "GameScene.h"

using namespace cocos2d;

bool GameScene::init()
{

	CCLabelTTF * pLabel = CCLabelTTF::create(
		"Game scene",
		"Arial",
		10 );

	pLabel->setPosition( ccp( 100, 100 ) );

	this->addChild( pLabel );


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
    