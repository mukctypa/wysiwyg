#include "cocos2d.h"
#include "GameScene.h"
#include "LetterSprite.h"

using namespace cocos2d;

GameScene::GameScene()
{
	this->m_pTargetSprite = CCSprite::create( "drop.png" );
}

bool GameScene::init()
{

	/*CCLabelTTF * pLabel = CCLabelTTF::create(
		"Game scene",
		"Arial",
		10 );*/

	CCMenuItemImage * pOkItem = CCMenuItemImage::create(
			"ok.png",
			"ok_tapped.png",
			this,
			menu_selector(GameScene::menuOkCallback) );

	CCMenuItemImage * pCancelItem = CCMenuItemImage::create(
			"clear.png",
			"clear_tapped.png",
			this,
			menu_selector(GameScene::menuOkCallback) );

	//pLabel->setPosition( ccp( 100, 100 ) );

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pOkItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	pCancelItem->setPosition( ccp(20, 20) );


	CCMenu* pMenu = CCMenu::create(pOkItem, pCancelItem, NULL);
    pMenu->setPosition( CCPointZero );
  
	this->addChild(pMenu, 1);

	//this->addChild( pLabel );

	addSpriteAtPosition( 0, 0, "A.png" );
	addSpriteAtPosition( 1, 0, "A.png" );
	addSpriteAtPosition( 2, 0, "A.png" );
	addSpriteAtPosition( 3, 0, "A.png" );

	addSpriteAtPosition( 0, 1, "A.png" );
	addSpriteAtPosition( 1, 1, "A.png" );
	addSpriteAtPosition( 2, 1, "A.png" );
	addSpriteAtPosition( 3, 1, "A.png" );

	addSpriteAtPosition( 0, 2, "A.png" );
	addSpriteAtPosition( 1, 2, "A.png" );
	addSpriteAtPosition( 2, 2, "A.png" );
	addSpriteAtPosition( 3, 2, "A.png" );

	addSpriteAtPosition( 0, 3, "A.png" );
	addSpriteAtPosition( 1, 3, "A.png" );
	addSpriteAtPosition( 2, 3, "A.png" );
	addSpriteAtPosition( 3, 3, "A.png" );

	this->m_pTargetSprite->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2 - 100, CCDirector::sharedDirector()->getWinSize().height - 20  ) );

	//this->m_pTargetSprite->setPosition( ccp(0, 0) );
	
	this->addChild( this->m_pTargetSprite );

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

void GameScene::menuOkCallback( CCObject * pSender )
{
	//TODO
	return;
}


void GameScene::menuClearCallback( CCObject * pSender )
{
	//TODO
	return;
}

    

void GameScene::addSpriteAtPosition( unsigned int x, unsigned int y, char * spriteName )
{
	assert( x < 4 );
	assert( y < 4 );
	assert( spriteName != NULL );

	LetterSprite * pSprite = LetterSprite::initWithLetter( "A.png", this->m_pTargetSprite );

	pSprite->setPosition( ccp( x * 72 + 17 + 72 / 2, y * 85 + 25 + 80 ) );



	this->addChild( pSprite );

	return;
}