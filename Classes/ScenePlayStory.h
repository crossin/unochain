#pragma once
#include "sceneplay.h"
class ScenePlayStory :
	public ScenePlay
{
public:
	ScenePlayStory(void);
	~ScenePlayStory(void);

	virtual bool init();  
	static CCScene* scene(int cpt, int lv);
	CREATE_FUNC(ScenePlayStory);

	static const int COMBO_INTERVAL = 2;
	static const int COMBO_LEVEL = 10;

	void update(float dt);

	void clearChain();

	CCSprite* tiles[COUNT_COL][COUNT_ROW];
	CCLabelTTF* textTime;
	CCLabelTTF* textMulti;
	CCSprite* progressbar;
	float gametime;
	int countCombo;
	float timeCombo;
	int multiBonus;
};

