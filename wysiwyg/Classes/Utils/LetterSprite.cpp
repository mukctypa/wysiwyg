#include "LetterSprite.h"
#include <iostream>

#define MSG_LETTER_DROP "letter_drop"

LetterSprite::LetterSprite( CCSprite * pTargetSprite, const AbstractLetter * letter ) : m_pTargetSprite( pTargetSprite ), m_pLetter( letter )
{
}

LetterSprite::~LetterSprite(void)
{
}

CCRect LetterSprite::rect()
{
    CCSize s = getTexture()->getContentSize();
    return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

LetterSprite* LetterSprite::initWithLetter( CCSprite * pTargetSprite, const AbstractLetter * letter )
{
	LetterSprite* pSprite = new LetterSprite( pTargetSprite, letter );
	char l = letter->getRepresentation();
	std::string fileName = std::string(	&l, 1);
	fileName.append( ".png" );
	CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage( fileName.c_str() ); 
	pSprite->initWithTexture( pTexture );
	pSprite->autorelease();
	return pSprite;
}


bool LetterSprite::initWithTexture(CCTexture2D* aTexture)
{
    if( CCSprite::initWithTexture(aTexture) ) 
    {
        m_state = kPaddleStateUngrabbed;
    }
    
    return true;
} 

void LetterSprite::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}

void LetterSprite::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}    

bool LetterSprite::containsTouchLocation(CCTouch* touch)
{
    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool LetterSprite::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (m_state != kPaddleStateUngrabbed) return false;
    if ( !containsTouchLocation(touch) ) return false;
    
    m_state = kPaddleStateGrabbed;
    return true;
}

void LetterSprite::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    // If it weren't for the TouchDispatcher, you would need to keep a reference
    // to the touch from touchBegan and check that the current touch is the same
    // as that one.
    // Actually, it would be even more complicated since in the Cocos dispatcher
    // you get CCSets instead of 1 UITouch, so you'd need to loop through the set
    // in each touchXXX method.
    
    CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");    
    
    CCPoint touchPoint = touch->getLocation();
    
    setPosition( ccp(touchPoint.x, touchPoint.y) );
}

CCObject* LetterSprite::copyWithZone(CCZone *pZone)
{
    this->retain();
    return this;
}

void LetterSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");    
    
    m_state = kPaddleStateUngrabbed;

	if ( this->m_pTargetSprite->boundingBox().containsPoint( touch->getLocation() ) )
	{
		std::cout << "Letter sprite is on target!" << std::endl;
		CCNotificationCenter::sharedNotificationCenter()->postNotification( MSG_LETTER_DROP, (CCObject*)this->m_pLetter);
		this->setVisible( false );

	}
} 

void LetterSprite::touchDelegateRetain()
{
    this->retain();
}

void LetterSprite::touchDelegateRelease()
{
    this->release();
}