#include "SceneMenuClassic.h"


SceneMenuClassic::SceneMenuClassic(void)
{
}


SceneMenuClassic::~SceneMenuClassic(void)
{
}


CCScene* SceneMenuClassic::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SceneMenuClassic *layer = SceneMenuClassic::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SceneMenuClassic::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// ui
		CCLabelTTF* label = CCLabelTTF::create("Classis Mode","Arial", 36);
		label->setPosition( ccp(160, 460) );
		addChild(label);

		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		for ()
		{
		}



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