#include "SceneEditor.h"
#include "libxml/tree.h"

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

		// ui
		
		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		button = CCMenuItemLabel::create(CCLabelTTF::create("SAVE", "Arial", 20), this, menu_selector(SceneEditor::buttonCallback));
		button->setPosition(ccp(400, 200));
		menu->addChild(button, 1, 1);

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
			if (blockSelected == block)
			{
				blockSelected->sprite->setOpacity(255);
				blockSelected = NULL;
			}
			else
			{
				if (blockSelected)
				{
					blockSelected->sprite->setOpacity(255);
				}
				blockSelected = block;
				block->sprite->setOpacity(127);
			}
		}
	}

	// put block
	if (CCRectMake(15,15,45*ScenePlay::COUNT_COL,45*ScenePlay::COUNT_ROW).containsPoint(m_tTouchPos))
	{
		int c = (m_tTouchPos.x-15)/45;
		int r = (m_tTouchPos.y-15)/45;

		if (blockSelected)
		{
			// add block
			if (arena[c][r])
			{
				// add on other block
				if (arena[c][ScenePlay::COUNT_ROW-1])
				{
					removeChild(arena[c][ScenePlay::COUNT_ROW-1], true);
				}
				for (int i=ScenePlay::COUNT_ROW-1; i>r; i--)
				{
					arena[c][i] = arena[c][i-1];
					if (arena[c][i])
					{
						arena[c][i]->setPosition(c*45+35,i*45+35);
					}
				}
			}
			arena[c][r] = LEUBlock::create(blockSelected->type);
			arena[c][r]->setPosition(c*45+35,r*45+35);
			addChild(arena[c][r]);
		}
		else
		{
			if (arena[c][r])
			{
				// clear block
				removeChild(arena[c][r], true);
				arena[c][r] = NULL;
			}
		}

	}
}

bool SceneEditor::saveToFile()
{
	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"level");

	xmlDocSetRootElement(doc,root_node);


	xmlNodePtr node;
	//xmlNodePtr son_node;
	xmlNodePtr content;
	char number[4] = "101";
	//CCMutableDictionary<std::string, CCString*>* dic;
	//vector<std::string> vc;
	//vector<std::string>::iterator it;
	//string key;

	// map
	node = xmlNewNode(NULL,BAD_CAST"map");

	content = xmlNewText(BAD_CAST(number));
	xmlAddChild(root_node,node);
	xmlAddChild(node,content);


	char fname[32]="level.xml";
// 	strcpy_s(fname, filename);
// 	strcat_s(fname, ".xml");
//	sprintf(fname, "level/%s.xml", filename);
	int nRel = xmlSaveFormatFileEnc(fname, doc, "UTF-8", 1);
	if (nRel == -1)
	{
		return false;
	}

	xmlFreeDoc(doc);
	
	return true;
}

void SceneEditor::buttonCallback( CCObject* pSender )
{
	saveToFile();
}

// void SceneEditor::menuCloseCallback(CCObject* pSender)
// {
//     // "close" menu item clicked
//     CCDirector::sharedDirector()->end();
// }

