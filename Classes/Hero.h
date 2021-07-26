#ifndef __HERO_H__  
#define __HERO_H__  
#include "cocos2d.h"  
#include "Definitions.h"
#include "Item.h"
using namespace cocos2d;

class Hero :public cocos2d::Node
{
public:
	Hero(void);
	~Hero(void);
	void InitHeroSprite(const char *hero_name);
	void SetAnimation(const char *name_plist, const char *name_png, const char *name_each, const unsigned int num, bool run_directon);
	float getHeroDamage() { return heroDamage; }
	void setHeroDamage(float damage) { heroDamage = damage; }
	void getAttackAmination();
	Point getPositionHero() { return m_HeroSprite->getPosition(); }
	void StopAnimation();
	bool IsRunning;
	// direction of movement of the hero  
	bool HeroDirecton;
	CREATE_FUNC(Hero);
private:
	float heroDamage;
	Point position;
	Sprite* m_HeroSprite;// elf  
	const char *Hero_name;// used to save the initial state of the wizard picture name  
	std::vector<Item*> collectedItem;
};
#endif // __HERO_H__  