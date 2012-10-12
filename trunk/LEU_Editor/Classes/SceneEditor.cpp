#include "SceneEditor.h"
#include "libxml/tree.h"
#include "text_input_node/CCTextFieldTTF.h"

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
		txtFile = CCTextFieldTTF::textFieldWithPlaceHolder("level","Arial",20);
		txtFile->setPosition(ccp(400, 240));
		addChild(txtFile);
		txtFile->attachWithIME();
		
		CCMenu* menu = CCMenu::create(NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);
		CCMenuItem* button;
		button = CCMenuItemLabel::create(CCLabelTTF::create("LOAD", "Arial", 20), this, menu_selector(SceneEditor::buttonCallback));
		button->setPosition(ccp(400, 200));
		menu->addChild(button, 1, 1);
		button = CCMenuItemLabel::create(CCLabelTTF::create("SAVE", "Arial", 20), this, menu_selector(SceneEditor::buttonCallback));
		button->setPosition(ccp(400, 150));
		menu->addChild(button, 1, 2);

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

void SceneEditor::buttonCallback( CCObject* pSender )
{
	switch ((((CCMenuItem*)pSender)->getTag()))
	{
	case 1:
		loadFromFile();
		break;
	case 2:
		saveToFile();
		break;
	}
}

bool SceneEditor::saveToFile()
{
	xmlDocPtr doc = xmlNewDoc(BAD_CAST"1.0");
	xmlNodePtr root_node = xmlNewNode(NULL,BAD_CAST"level");
	xmlDocSetRootElement(doc,root_node);

	xmlNodePtr node;
	xmlNodePtr content;

	// map
	char map[ScenePlay::COUNT_COL*ScenePlay::COUNT_ROW+1];
	for (int i = 0; i < ScenePlay::COUNT_COL; i++)
	{
		for(int j = 0; j < ScenePlay::COUNT_ROW; j++)
		{
			if (arena[i][j])
			{
				map[i*ScenePlay::COUNT_ROW+j] = '0' + arena[i][j]->type;
			} 
			else
			{
				map[i*ScenePlay::COUNT_ROW+j] = '0';
			}
		}
	}
	map[ScenePlay::COUNT_COL*ScenePlay::COUNT_ROW] = '\0';

	node = xmlNewNode(NULL,BAD_CAST"map");
	content = xmlNewText(BAD_CAST(map));
	xmlAddChild(root_node,node);
	xmlAddChild(node,content);


	char fname[32];
	sprintf(fname, "level/%s.xml", txtFile->getString());
	int nRel = xmlSaveFormatFileEnc(fname, doc, "UTF-8", 1);
	if (nRel == -1)
	{
		return false;
	}

	xmlFreeDoc(doc);
	
	return true;
}

bool SceneEditor::loadFromFile()
{
	xmlDocPtr doc;           
	xmlNodePtr curNode;

	char fname[32];
	sprintf(fname, "level/%s.xml", txtFile->getString());
    
	//doc = xmlReadFile(CCFileUtils::fullPathFromRelativePath(fname),"UTF-8",XML_PARSE_NOBLANKS);
	doc = xmlReadFile(fname,"UTF-8",XML_PARSE_NOBLANKS);
	/////////////////////////////////////////////////////////////////////////
	// for android
	// 	szDocName = CCFileUtils::fullPathFromRelativePath("level.xml");    
	// 	CCFileData data(szDocName, "rt");
	// 	unsigned long size = data.getSize();
	// 	char *pBuffer = (char*) data.getBuffer();
	// 	doc = xmlReadMemory(pBuffer, size, NULL, "UTF-8", XML_PARSE_NOBLANKS);
	//////////////////////////////////////////////////////////////////////////
	if (NULL == doc)
	{
		return false;
	}

	curNode = xmlDocGetRootElement(doc); 
	if (NULL == curNode)
	{
		xmlFreeDoc(doc);
		return false;
	}

	if (xmlStrcmp(curNode->name, BAD_CAST "level"))
	{
		xmlFreeDoc(doc);
		return false;
	}

	curNode = curNode->xmlChildrenNode;
	
	while(curNode != NULL)
	{
		
		// get map
		if (!xmlStrcmp(curNode->name, (const xmlChar *)"map"))
		{
			CCString* str = new CCString((const char*)xmlNodeGetContent(curNode));
			const char* map = str->getCString();
			int tp;
			for (int i = 0; i < ScenePlay::COUNT_COL; i++)
			{
				for(int j = 0; j < ScenePlay::COUNT_ROW; j++)
				{
					if (arena[i][j])
					{
						removeChild(arena[i][j], true);
						arena[i][j] = NULL;
					}
					tp = map[i*ScenePlay::COUNT_ROW+j] - '0';
					if (tp > 0)
					{
						arena[i][j] = LEUBlock::create(tp);
						arena[i][j]->setPosition(i*45+35,j*45+35);
						addChild(arena[i][j]);
					} 
				}
			}
			str->release();
		}

		
		curNode = curNode->next;
	}

	xmlFreeDoc(doc);

	return true;
}

// void SceneEditor::menuCloseCallback(CCObject* pSender)
// {
//     // "close" menu item clicked
//     CCDirector::sharedDirector()->end();
// }

