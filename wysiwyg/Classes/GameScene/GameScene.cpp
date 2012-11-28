#include "cocos2d.h"
#include "GameScene.h"
#include "LetterSprite.h"

using namespace cocos2d;

//tmp: remove
#include <iostream>
#include <random>
#include <fstream>
#include <list>
#include <algorithm>
#include <sstream> 

#include <time.h>

#define MSG_LETTER_DROP "letter_drop"

GameScene::GameScene()
{
	this->m_pTargetSprite = CCSprite::create( "drop.png" );
	m_letters = "ABCDEFGHIJKLNMNOPQRSTVWXYZ****";
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
			menu_selector(GameScene::menuClearCallback) );

	//pLabel->setPosition( ccp( 100, 100 ) );

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pOkItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	pCancelItem->setPosition( ccp(20, 20) );


	CCMenu* pMenu = CCMenu::create(pOkItem, pCancelItem, NULL);
    pMenu->setPosition( CCPointZero );
  
	this->addChild(pMenu, 1);

	//this->addChild( pLabel );

	//get 16 letters
	std::default_random_engine generator( (unsigned int)time(0) );
	std::uniform_int_distribution<int> rand( 0, this->m_letters.size() - 1 );
	for ( int i = 0; i < 4; i++ )
		for ( int j = 0; j < 4; j++ )
		{
			int k = rand( generator );
			AbstractLetter * letter;
			if ( m_letters[k] != '*' )
				letter = new NormalLetter( m_letters[k] );
			else
				letter = new SpecialLetter();

			this->addSpriteAtPosition( i, j, letter );
		}

	this->m_pTargetSprite->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2 - 100, CCDirector::sharedDirector()->getWinSize().height - 20  ) );

	//this->m_pTargetSprite->setPosition( ccp(0, 0) );
	

	this->m_pSelectedLettersLabel = CCLabelTTF::create( "", "Arial", 24 );
	this->m_pSelectedLettersLabel->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2 + 75, CCDirector::sharedDirector()->getWinSize().height - 20 ) );
	this->addChild( this->m_pSelectedLettersLabel );

	this->addChild( this->m_pTargetSprite );

	this->m_points = 0;
	this->m_pPointsLabel = CCLabelTTF::create( "0", "Arial", 24 );
	this->m_pPointsLabel->setPosition( ccp( CCDirector::sharedDirector()->getWinSize().width / 2, 20 ) );
	this->addChild( this->m_pPointsLabel );
	
	
	CCNotificationCenter::sharedNotificationCenter()->addObserver( this, callfuncO_selector(GameScene::dragAndDropListner), MSG_LETTER_DROP, NULL );

	std::fstream file("English.txt");

	while ( !file.eof() )
	{
		std::string str; 
		std::getline(file, str);
		std::transform(str.begin(), str.end(),str.begin(), ::toupper);
		my_list.push_back( Word(str) );

	}

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
	if ( this->m_selectedLetters.size() == 0 )
		return;
	Word to_validate( &this->m_selectedLetters );
	for ( std::list<Word>::iterator it = my_list.begin(); it != my_list.end(); ++it )
	{ 
		if (  it->validate( to_validate) )
		{
			this->m_points += to_validate.getPoints();
			this->updatePoints();
			return;
		}
	}
	return;
}


void GameScene::menuClearCallback( CCObject * pSender )
{	
	this->m_selectedLetters.clear();
	this->updateSelectedLetters();
	return;
}

    

void GameScene::addSpriteAtPosition( unsigned int x, unsigned int y, AbstractLetter * letter )
{
	assert( x < 4 );
	assert( y < 4 );
	assert( letter != NULL );

	LetterSprite * pSprite = LetterSprite::initWithLetter( this->m_pTargetSprite, letter );

	pSprite->setPosition( ccp( x * 72 + 17 + 72 / 2, y * 85 + 25 + 80 ) );



	this->addChild( pSprite );

	return;
}


void GameScene::dragAndDropListner( CCObject * obj )
{
	AbstractLetter * letter = (AbstractLetter*)obj;
	this->m_selectedLetters.push_back( letter );
	this->updateSelectedLetters();
}

void GameScene::updateSelectedLetters()
{
	std::string text = "";

	for ( LetterSequence::iterator it = this->m_selectedLetters.begin(); it != this->m_selectedLetters.end(); ++it )
	{
		char l = (*it)->getRepresentation();
		text += std::string( &l, 1);
	}

	this->m_pSelectedLettersLabel->setString( text.c_str() );
}

std::string convertInt(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
} 

void GameScene::updatePoints()
{
	std::string points = convertInt( this->m_points );
	this->m_pPointsLabel->setString( points.c_str() );
	return;
}

void GameScene::engineLogic()
{
	//TODO
}