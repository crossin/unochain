#include "SceneEnd.h"


SceneEnd::SceneEnd(void)
{
}


SceneEnd::~SceneEnd(void)
{
}


CCScene* SceneEnd::scene(bool isWin/* = false*/)
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		SceneEnd *layer = SceneEnd::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);

		if (isWin)
		{
			layer->textDesc->setString("You Win!");
		}
	} while (0);

	return scene;
}

bool SceneEnd::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		textDesc = CCLabelTTF::create("You Lose!", "Arial", 24);
		CC_BREAK_IF(!textDesc);
		textDesc->setPosition(ccp(160, 240));
		addChild(textDesc);

		bRet = true;
	} while (0);

	return bRet;
}
