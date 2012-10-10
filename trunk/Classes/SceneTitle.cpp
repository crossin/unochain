#include "SceneTitle.h"
#include "ScenePlayClassic.h"
#include "ScenePlayPuzzle.h"
#include "ScenePlayRace.h"
#include "ScenePlayEndless.h"


SceneTitle::SceneTitle(void)
{
}


SceneTitle::~SceneTitle(void)
{
}


CCScene* SceneTitle::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SceneTitle *layer = SceneTitle::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SceneTitle::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// ui
		CCLabelTTF* label = CCLabelTTF::create("Link'em Up","Arial", 36);
		label->setPosition( ccp(160, 300) );
		addChild(label);

		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		button = CCMenuItemLabel::create(CCLabelTTF::create("CLASSIC", "Arial", 20), this, menu_selector(SceneTitle::buttonCallback));
		button->setPosition(ccp(160, 200));
		menu->addChild(button, 1, 1);
		button = CCMenuItemLabel::create(CCLabelTTF::create("PUZZLE", "Arial", 20), this, menu_selector(SceneTitle::buttonCallback));
		button->setPosition(ccp(160, 160));
		menu->addChild(button, 1, 2);
		button = CCMenuItemLabel::create(CCLabelTTF::create("RACE", "Arial", 20), this, menu_selector(SceneTitle::buttonCallback));
		button->setPosition(ccp(160, 120));
		menu->addChild(button, 1, 3);
		button = CCMenuItemLabel::create(CCLabelTTF::create("ENDLESS", "Arial", 20), this, menu_selector(SceneTitle::buttonCallback));
		button->setPosition(ccp(160, 80));
		menu->addChild(button, 1, 4);

		bRet = true;
	} while (0);

	setTouchEnabled(true);

	scheduleUpdate();

	return bRet;
}

void SceneTitle::buttonCallback(CCObject* pSender)
{
	switch (((CCMenuItem*)pSender)->getTag())
	{
	case 1:
		CCDirector::sharedDirector()->replaceScene(ScenePlayClassic::scene());
		break;
	case 2:
		CCDirector::sharedDirector()->replaceScene(ScenePlayPuzzle::scene());
		break;
	case 3:
		CCDirector::sharedDirector()->replaceScene(ScenePlayRace::scene());
		break;
	case 4:
		CCDirector::sharedDirector()->replaceScene(ScenePlayEndless::scene());
		break;
	}

}