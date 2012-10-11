#pragma once
#include "sceneplay.h"
class ScenePlayClassic :
	public ScenePlay
{
public:
	ScenePlayClassic(void);
	~ScenePlayClassic(void);

	virtual bool init();  
	static CCScene* scene(char* filename = "level/001.xml");
	CREATE_FUNC(ScenePlayClassic);

	void update(float dt);

	void clearChain();

	CCLabelTTF* textTime;
	CCSprite* progressbar;
	float gametime;
	int pointWin;
	int pointNow;
};

