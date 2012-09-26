#include "ScenePlay.h"

ScenePlay::ScenePlay(void)
{
}


ScenePlay::~ScenePlay(void)
{
}

CCScene* ScenePlay::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlay *layer = ScenePlay::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlay::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		srand(time(0)); 

		// init game
		UnoBlock* pSymbol;
		for (int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 12; j++)
			{
				pSymbol = UnoBlock::unoblock();
				CC_BREAK_IF(!pSymbol);
				pSymbol->setPosition(ccp(i*40+20, j*40+20));
				addChild(pSymbol);
				arena[i][j] = pSymbol;
			}
		}


		bRet = true;
	} while (0);

	return bRet;
}