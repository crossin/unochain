#include "ScenePlayStory.h"
#include "SceneEnd.h"


ScenePlayStory::ScenePlayStory(void)
{
}


ScenePlayStory::~ScenePlayStory(void)
{
}


CCScene* ScenePlayStory::scene(int cpt, int lv)
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		ScenePlayStory *layer = ScenePlayStory::create();
		CC_BREAK_IF(! layer);
		char filename[16];
		sprintf(filename, "level/%d%02d.xml", cpt, lv);
		layer->loadMap(filename);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool ScenePlayStory::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! ScenePlay::init());

		gametime = 90;
		countCombo = 0;
		timeCombo = 0;
		multiBonus = 1;

		// ui
		textTime = CCLabelTTF::create("", "Arial", 24);
		CC_BREAK_IF(!textTime);
		textTime->setPosition(ccp(300, 460));
		addChild(textTime);
		textMulti = CCLabelTTF::create("", "Arial", 24);
		CC_BREAK_IF(!textMulti);
		textMulti->setPosition(ccp(20, 460));
		addChild(textMulti);

		progressbar = CCSprite::create("bar.png");
		CC_BREAK_IF(!progressbar);
		progressbar->setPosition(ccp(40, 450));
		progressbar->setAnchorPoint(CCPointZero);
		progressbar->setTextureRect(CCRectMake(0,0,0,20));
		addChild(progressbar);

		// tiles
		for (int i = 0; i < COUNT_COL; i++)
		{
			for(int j = 0; j < COUNT_ROW; j++)
			{
				tiles[i][j] = CCSprite::create("tile.png");
				tiles[i][j]->setPosition(ccp(i*LEUBlock::GRID_LENGTH+25, j*LEUBlock::GRID_LENGTH+20));
				addChild(tiles[i][j]);
			}
		}

		bRet = true;
	} while (0);

	return bRet;
}

void ScenePlayStory::update(float dt)
{
	gametime -= dt;
	char strTime[4];
	sprintf(strTime, "%d", (int)gametime);
	textTime->setString(strTime);
	if (gametime < 0)
	{
		CCDirector::sharedDirector()->replaceScene(SceneEnd::scene());
	}
	timeCombo += dt;
	if (timeCombo > COMBO_INTERVAL && countCombo > 0)
	{
		countCombo = 0;
		multiBonus = 1;
		textMulti->setString("");
		progressbar->setTextureRect(CCRectMake(0,0,0,20));
	}
}


void ScenePlayStory::clearChain()
{
	clearAndRefill(true);
	// clear tile
	CCObject* obj;
	LEUBlock* pBlock;
	CCARRAY_FOREACH(chainSelected, obj)
	{
		pBlock = (LEUBlock*)obj;
		if (tiles[pBlock->col][pBlock->row])
		{
			removeChild(tiles[pBlock->col][pBlock->row], true);
			tiles[pBlock->col][pBlock->row] = NULL;
		}
	}
	// add point
	timeCombo = 0;
	countCombo += chainSelected->count() - 2;
	multiBonus = countCombo / COMBO_LEVEL + 1;
	if (multiBonus > 1)
	{
		char num[4];
		sprintf(num, "X%d", multiBonus);
		textMulti->setString(num);
	}
	else
	{
		textMulti->setString("");
	}
	progressbar->setTextureRect(CCRectMake(0,0,180.0*(countCombo%COMBO_LEVEL)/COMBO_LEVEL,20));

	// check win
	for (int i = 0; i < COUNT_COL; i++)
	{
		for(int j = 0; j < COUNT_ROW; j++)
		{
			if (tiles[i][j])
			{
				return;
			}
		}
	}
	CCDirector::sharedDirector()->replaceScene(SceneEnd::scene(true));
}