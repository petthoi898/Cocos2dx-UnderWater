
#ifndef __UNDER_WATER_SCENE_H__
#define __UNDER_WATER_SCENE_H__
#include "Enemy.h"
#include "cocos2d.h"
#include "HRocker.h"
#include "Hero.h"
#include "ProgressView.h"
#include "Item.h"
#include "Information.h"
using namespace cocos2d;

class UnderWater : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(Information* infor);

	virtual bool init();
	// In the public section
	void setViewPointCenter(Point position);
	void combat(Enemy* enemy);
	virtual void update(float delta);
	bool isRectCollision(Rect rect1, Rect rect2);
	CREATE_FUNC(UnderWater);

private:

	TMXTiledMap *_tileMap;
	TMXLayer *_background;
	TMXLayer *_blockage;
	HRocker*  rocker;
	Hero*    hero;
	vector<Enemy*> enemy;
	ProgressView* view;
	Sprite* aroundCharacter;
	Sprite* character;
	vector<Item*> listItem;
	vector<Item*> collectedItem;
	Sprite* tele;
	Node* cameraView;
	static Information* infor;
};

#endif // __UNDER_WATER_SCENE_H__
