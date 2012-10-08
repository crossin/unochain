#include "ScenePlayEndless.h"


ScenePlayEndless::ScenePlayEndless(void)
{
}


ScenePlayEndless::~ScenePlayEndless(void)
{
}


CCScene* ScenePlayEndless::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlayEndless *layer = ScenePlayEndless::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlayEndless::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! ScenePlay::init());

		pointNow = 0;

		// ui
		textScore = CCLabelTTF::create("0", "Arial", 24);
		CC_BREAK_IF(!textScore);
		textScore->setPosition(ccp(20, 460));
		addChild(textScore);

		bRet = true;
	} while (0);

	return bRet;
}


void ScenePlayEndless::clearChain()
{
	clearAndRefill(true);
	// add point
	pointNow += chainSelected->count();
	char strScore[4];
	sprintf(strScore, "%d", pointNow);
	textScore->setString(strScore);
}