#include "ScenePlayRace.h"
#include "SceneEnd.h"


ScenePlayRace::ScenePlayRace(void)
{
}


ScenePlayRace::~ScenePlayRace(void)
{
}


CCScene* ScenePlayRace::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlayRace *layer = ScenePlayRace::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlayRace::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! ScenePlay::init());

		gametime = 30;
		pointNow = 0;

		// ui
		textTime = CCLabelTTF::create("", "Arial", 24);
		CC_BREAK_IF(!textTime);
		textTime->setPosition(ccp(300, 460));
		addChild(textTime);

		textScore = CCLabelTTF::create("0", "Arial", 24);
		CC_BREAK_IF(!textScore);
		textScore->setPosition(ccp(20, 460));
		addChild(textScore);

		bRet = true;
	} while (0);

	return bRet;
}

void ScenePlayRace::update(float dt)
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


void ScenePlayRace::clearChain()
{
	clearAndRefill(true);
	// add point
	pointNow += chainSelected->count();
	char strScore[4];
	sprintf(strScore, "%d", pointNow);
	textScore->setString(strScore);
}