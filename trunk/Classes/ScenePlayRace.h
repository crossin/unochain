#pragma once
#include "sceneplay.h"
class ScenePlayRace :
	public ScenePlay
{
public:
	ScenePlayRace(void);
	~ScenePlayRace(void);

	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(ScenePlayRace);

	void update(float dt);

	void clearChain();

	CCLabelTTF* textTime;
	CCLabelTTF* textScore;
	float gametime;
	int pointNow;
};

