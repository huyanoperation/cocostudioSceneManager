#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	cocos2d::CCNode* GetNodeFromParent( CCNode *parent, std::string key );
    
	cocos2d::CCNode* MergeNode( cocos2d::CCArray* pArray  );
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void onCreateTouch( CCNode* pNode1, CCNode* pNode2 );
    
    // implement the "static node()" method manually
    ///
    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    ///
    CCSize visibleSize;
    float posx1,posx2;
    CCNode * m_pNode1;
    CCNode * m_pNode2;


    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
