#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "cocos-ext.h"
USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	m_pNode1 = NULL;
    m_pNode2 = NULL;
	setTouchEnabled( true );
	CCSize s =  CCDirector::sharedDirector()->getWinSize();
	/*CCSprite * spr = CCSprite::create("HelloWorld.png");
	spr->setPosition(ccp(s.width/2,s.height/2));
	spr->setScale(2.0f);
	this->addChild(spr);*/

	posx1 = posx2 = 0;

	
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize( 960, 640, kResolutionShowAll );
	CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths;

	searchPaths.push_back("publish");
	pFileUtils->setSearchPaths(searchPaths);
    ////////////////////////////////读取两个场景 pNode pNode2
    CCNode *pNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile("NewScene.json");
    CCNode *pNode2 = SceneReader::sharedSceneReader()->createNodeWithSceneFile("NewScene2.json");
   //---------------------------------------------------------------------------------------------
	//step1  一个做远景一个做中景
	addChild( pNode );
	addChild( pNode2 );
	CCNode* pSprite = GetNodeFromParent( pNode ,"testweapon1" );  //将场景中的一个子Node结点取出来控制
	pSprite->runAction( CCMoveBy::create( 10, ccp(1000, 0 ) ) );
	onCreateTouch( pNode, pNode2 );

	//step2  两个场景依次向后排列
	//CCArray *pArray = CCArray::create();
	//pArray->addObject( pNode );
	//pArray->addObject( pNode2 );
	//CCNode *pMergeParent = MergeNode( pArray );
    //addChild( pMergeParent );
	//onCreateTouch( pMergeParent, NULL );


    return true;
}
//------------------------------------------------------------
//
//
void HelloWorld::onCreateTouch( CCNode *pNode1, CCNode *pNode2 )
{
	m_pNode1 = pNode1;
    m_pNode2 = pNode2;
}
//-----------------------------------------------------------------------
//
//
CCNode* HelloWorld::MergeNode( CCArray* pArray  )
{
	CCSize s =  CCDirector::sharedDirector()->getWinSize();
	CCNode *ParantNode = CCNode::create();
	for( int i = 0; i < pArray->count(); i++ )
	{
		CCNode *pSubNode = (CCNode*)pArray->objectAtIndex(i);
		ParantNode->addChild( pSubNode );
		pSubNode->setPosition( ccpAdd( pSubNode->getPosition(), ccp( s.width * i, 0 ) ) );
	}
	//for( int i = 0; i < pArray->count(); i++ )
	//{
	//	CCNode *pSubNode = (CCNode*)pArray->objectAtIndex(i);

	//	for( int j = 0; j < pSubNode->getChildrenCount(); j++  )
	//	{
	//		CCNode *pSprite = (CCNode*)pSubNode->getChildren()->objectAtIndex(j);
	//		pSubNode->removeChild( pSprite );
	//		ParantNode->addChild( pSprite );
	//	}
	//}

	return ParantNode;
}
//------------------------------------------------------------
//
//
CCNode* HelloWorld::GetNodeFromParent( CCNode *parent, std::string key )
{
	for( int i = 0; i < parent->getChildrenCount(); i++ )
	{
		 CCNode *pSubNode = ( CCNode* )parent->getChildren()->objectAtIndex( i );
		 if( NULL != pSubNode->getComponent(key.c_str()) )
		 {
			 return pSubNode;
		 }
	}
	return NULL;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::registerWithTouchDispatcher(void)
{
        CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
//    int index = 0;
//    for (CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++,index++)
//    {
//        index++;
//        CCTouch* pTouch = (CCTouch*)(*iterTouch);
//        CCPoint location = pTouch->getLocation();
//        CCPoint perLocation = pTouch->getPreviousLocation();
//        float value = location.x - perLocation.x;
//        posx1 += value;
//        posx2 += (value / 2);
//        ///
////        printf("\n location.x:%f, location.y:%f",location.x,location.y);
//        _layerColor->setPosition(ccp(posx1, visibleSize.height/2));
//    }
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    int index = 0;
    for (CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++,index++)
    {
        index++;
        CCTouch* pTouch = (CCTouch*)(*iterTouch);
        CCPoint location = pTouch->getLocation();
        CCPoint perLocation = pTouch->getPreviousLocation();
        float value = location.x - perLocation.x;
        posx1 += value;
        posx2 += (value / 2);
		if( NULL != m_pNode1 )
		{
			m_pNode1->setPosition(ccp(posx1,0));
		}
		if( NULL != m_pNode2 )
		{
			m_pNode2->setPosition(ccp(posx2,0));
		}
    }
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
//    int index = 0;
//    for (CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++,index++)
//    {
//        index++;
//        CCTouch* pTouch = (CCTouch*)(*iterTouch);
//        CCPoint location = pTouch->getLocation();
//        CCPoint perLocation = pTouch->getPreviousLocation();
//        float value = location.x - perLocation.x;
//        posx1 += value;
//        posx2 += (value / 2);
//        ///
////        printf("\n location.x:%f, location.y:%f",location.x,location.y);
//        _layerColor->setPosition(ccp(posx1, visibleSize.height/2));
//    }
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{

}

