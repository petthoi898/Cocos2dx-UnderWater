#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Item.h"
USING_NS_CC;


typedef enum {
	tag_rocker,
	tag_rockerBG,
}tagForHRocker;
typedef enum {
	rocker_stay,
	rocker_right,
	rocker_up,
	rocker_left,
	rocker_down,
}tagDirecton;
class HRocker :public cocos2d::Layer
{
public:
	HRocker();
	static HRocker* createHRocker(const char *rockerImageName, const char *rockerBGImageName, Vec2 position, vector<Item*> cur);
	void startRocker(bool _isStopOther);
	void stopRocker();
	int rocketDirection;
	bool rocketRun;
	bool isInRocker;
	bool isInAttack;
	void loadQuickItem(Point position, Size size);
	Point getBagPosition() { return baloPosition; }
	Item* getQuickItemAt(int i) { return quickItem.at(i); }
	virtual bool onTouchBegan(Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, cocos2d::Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, cocos2d::Event *pEvent);
	void setQuickItem(vector<Item*> listItem) { quickItem = listItem; }
	bool isTouchOnItem(int i, Vec2 vec2) { return quickItem.at(i)->getSprite()->getBoundingBox().containsPoint(vec2); };
	CREATE_FUNC(HRocker);
	vector<Item*> quickItem;
	int scaleAt;
	int facePos;
	bool isCraft;
	bool showedItem;
private:
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, const Vec2 position);
	//pair<bool, int> scaleAt;
	bool isCanMove;
	float getRad(Vec2 pos1, Vec2 pos2);
	Vec2 rockerBGPosition;
	float rockerBGR;
	Hero*    hero;
	Sprite* pauseGame;
	Sprite* buttonAttack;
	Point baloPosition;
	Sprite* quickSlot;
	Sprite* itemExtend;
	Sprite* buttonExtendItem;
	Sprite* extendedItem;
	Sprite* craft;

	static vector<Item*> currentItem;
};

#endif