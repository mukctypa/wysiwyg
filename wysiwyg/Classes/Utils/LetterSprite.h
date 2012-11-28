#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "cocos2d.h"
#include "Models.h"

USING_NS_CC;

typedef enum tagPaddleState 
{
    kPaddleStateGrabbed,
    kPaddleStateUngrabbed
} PaddleState; 

class LetterSprite : public CCSprite, public CCTargetedTouchDelegate
{
    PaddleState        m_state;
	CCSprite * m_pTargetSprite;
	const AbstractLetter * m_pLetter;

public:
    LetterSprite( CCSprite * m_pTargetSprite, const AbstractLetter * letter );
    virtual ~LetterSprite(void);

    CCRect rect();
	virtual void onEnter();
    virtual void onExit();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan( CCTouch* touch, CCEvent* event );
    virtual void ccTouchMoved( CCTouch* touch, CCEvent* event );
    virtual void ccTouchEnded( CCTouch* touch, CCEvent* event );


    virtual CCObject* copyWithZone(CCZone *pZone);

    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();

	//TODO: replace std::string file name with real letter
	static LetterSprite * initWithLetter( CCSprite * m_pTargetSprite, const AbstractLetter * letter );

	bool initWithTexture(CCTexture2D* aTexture); 
};

#endif
