#include "SceneLevel.h"
#include "ScenePlayStory.h"


SceneLevel::SceneLevel(void)
{
}


SceneLevel::~SceneLevel(void)
{
}


CCScene* SceneLevel::scene(int cpt)
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SceneLevel *layer = SceneLevel::create();
		CC_BREAK_IF(! layer);
		layer->setChapter(cpt);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool SceneLevel::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// ui
		txtTitle = CCLabelTTF::create("Chapter. ", "Arial", 36);
		txtTitle->setPosition( ccp(160, 460) );
		addChild(txtTitle);

		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		char num[4];
		for (int i=0; i<12; i++)
		{
			sprintf(num, "%02d", i+1);
			button = CCMenuItemLabel::create(CCLabelTTF::create(num, "Arial", 20), this, menu_selector(SceneLevel::buttonCallback));
			button->setPosition(ccp(80+i%3*80, 360-i/3*80));
			menu->addChild(button, 1, i+1);
		}

		bRet = true;
	} while (0);

	return bRet;
}

void SceneLevel::buttonCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(ScenePlayStory::scene(chapter, ((CCMenuItem*)pSender)->getTag()));
}

void SceneLevel::setChapter( int cpt )
{
	chapter = cpt;
	char name[16];
	sprintf(name, "Chapter. %d", chapter);
	txtTitle->setString(name);
}
