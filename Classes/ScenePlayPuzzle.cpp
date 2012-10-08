#include "ScenePlayPuzzle.h"


ScenePlayPuzzle::ScenePlayPuzzle(void)
{
}


ScenePlayPuzzle::~ScenePlayPuzzle(void)
{
}


CCScene* ScenePlayPuzzle::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlayPuzzle *layer = ScenePlayPuzzle::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlayPuzzle::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! ScenePlay::init());


		bRet = true;
	} while (0);

	return bRet;
}

void ScenePlayPuzzle::clearChain()
{
	clearAndRefill(false);
}
