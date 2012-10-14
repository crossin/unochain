#include "SceneChapter.h"
#include "SceneLevel.h"


SceneChapter::SceneChapter(void)
{
}


SceneChapter::~SceneChapter(void)
{
}


CCScene* SceneChapter::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SceneChapter *layer = SceneChapter::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SceneChapter::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// ui
		CCLabelTTF* label = CCLabelTTF::create("Story Mode","Arial", 36);
		label->setPosition( ccp(160, 460) );
		addChild(label);

		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		char name[16];
		for (int i=0; i<4; i++)
		{
			sprintf(name, "Chapter. %d", i+1);
			button = CCMenuItemLabel::create(CCLabelTTF::create(name, "Arial", 20), this, menu_selector(SceneChapter::buttonCallback));
			button->setPosition(ccp(80+i%2*160, 320-i/2*160));
			menu->addChild(button, 1, i+1);
		}

		bRet = true;
	} while (0);

	return bRet;
}

void SceneChapter::buttonCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(SceneLevel::scene(((CCMenuItem*)pSender)->getTag()));
}