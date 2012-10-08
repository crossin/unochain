#include "ScenePlayClassic.h"
#include "SceneEnd.h"


ScenePlayClassic::ScenePlayClassic(void)
{
}


ScenePlayClassic::~ScenePlayClassic(void)
{
}


CCScene* ScenePlayClassic::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlayClassic *layer = ScenePlayClassic::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlayClassic::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! ScenePlay::init());

		gametime = 30;
		pointWin = 50;
		pointNow = 0;

		// ui
		textTime = CCLabelTTF::create("", "Arial", 24);
		CC_BREAK_IF(!textTime);
		textTime->setPosition(ccp(300, 460));
		addChild(textTime);

		progressbar = CCSprite::create("bar.png");
		CC_BREAK_IF(!progressbar);
		progressbar->setPosition(ccp(20, 450));
		progressbar->setAnchorPoint(CCPointZero);
		progressbar->setTextureRect(CCRectMake(0,0,0,20));
		addChild(progressbar);

		bRet = true;
	} while (0);

	return bRet;
}

void ScenePlayClassic::update(float dt)
{
	gametime -= dt;
	char strTime[4];
	sprintf(strTime, "%d", (int)gametime);
	textTime->setString(strTime);
	if (gametime < 0)
	{
		CCDirector::sharedDirector()->replaceScene(SceneEnd::scene());
	}
}


void ScenePlayClassic::clearChain()
{
	clearAndRefill(true);
	// add point
	pointNow += chainSelected->count();
	if (pointNow >= pointWin)
	{
		CCDirector::sharedDirector()->replaceScene(SceneEnd::scene(true));
	}
	progressbar->setTextureRect(CCRectMake(0,0,240.0*pointNow/pointWin,20));
}