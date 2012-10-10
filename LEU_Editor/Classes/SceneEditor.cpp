#include "SceneEditor.h"
#include "LEUBlock.h"

using namespace cocos2d;

SceneEditor::SceneEditor(void)
{
}


SceneEditor::~SceneEditor(void)
{
	if (blockSelected)
	{
		blockSelected->release();
		blockSelected = NULL;
	}
}

CCScene* SceneEditor::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        SceneEditor *layer = SceneEditor::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SceneEditor::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		CCSprite* pSprite;
		for (int i = 0; i < ScenePlay::COUNT_COL; i++)
		{
			for(int j = 0; j < ScenePlay::COUNT_ROW; j++)
			{
				pSprite = CCSprite::create("grid.png");
				pSprite->setPosition(ccp(i*45+35,j*45+35));
				addChild(pSprite);
				arena[i][j] = NULL;
			}
		}

		sampleBlocks = CCArray::create();
		sampleBlocks->retain();

		LEUBlock* block;
		for (int i=1; i<=LEUBlock::COUNT_TYPE; i++)
		{
			block = LEUBlock::create(i);
			block->setPosition(360, 485-45*i);
			addChild(block);
			sampleBlocks->addObject(block);
		}

		blockSelected = NULL;

        bRet = true;
    } while (0);

	setTouchEnabled(true);


    return bRet;
}


void SceneEditor::ccTouchesEnded( CCSet* touches, CCEvent* event )
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint m_tTouchPos = convertTouchToNodeSpace(touch);

	// select block
	LEUBlock* block;
	for (int i=0; i<LEUBlock::COUNT_TYPE; i++)
	{
		block = (LEUBlock*)sampleBlocks->objectAtIndex(i);
		if (block->getRect().containsPoint(m_tTouchPos))
		{
			if (blockSelected)
			{
				blockSelected->sprite->setOpacity(255);
			}
			blockSelected = block;
			block->sprite->setOpacity(127);
		}
	}

	// put block
	if (blockSelected && CCRectMake(15,15,45*ScenePlay::COUNT_COL,45*ScenePlay::COUNT_ROW).containsPoint(m_tTouchPos))
	{
		int c = (m_tTouchPos.x-15)/45;
		int r = (m_tTouchPos.y-15)/45;
		if (!arena[c][r])
		{
			arena[c][r] = LEUBlock::create(blockSelected->type);
			arena[c][r]->setPosition(c*45+35,r*45+35);
			addChild(arena[c][r]);
		}
	}
}
// void SceneEditor::menuCloseCallback(CCObject* pSender)
// {
//     // "close" menu item clicked
//     CCDirector::sharedDirector()->end();
// }

