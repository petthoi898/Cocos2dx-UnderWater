#ifndef __ENEMY_H__  
#define __ENEMY_H__
#include "cocos2d.h"  
#include "ProgressView.h"
#include "Definitions.h"
#include "Item.h"
USING_NS_CC;
class Enemy : public Scene
{
public:
	Enemy();
	void initSpriteEnemy(Point position, std::string type);
	void initSpriteEnemyMedusa(Point position);
	void initSpriteEnemyDemon(Point position);
	void initSpriteEnemyDragon(Point position);
	void enemyAttack();
	void enemyHurt();
	void enemyDead();
	void enemyWalk();
	void removeEnemyDead();
	void enemyFollow(Point pos);
	float getMedusaDamage() { return MEDUSADAMAGE; }
	float getDragonDamage() { return DRAGONDAMAGE; }
	float getDemonDamage() { return DEMONDAMAGE; }
	void setViewEnemy(Point postion);
	void setItemEnemy(Item* item) { itemEnemy = item; };
	bool isDead;
	bool isHurt;
	bool isCollected;
	bool itemDroped;
	Sprite* enemySprite;
	Item* itemEnemy;
	ProgressView* viewEnemy;
	Point enemyPosition;
	std::string type;
	CREATE_FUNC(Enemy);
private:
	float positionY;
	float positionX;

};
#endif // __ENEMY_H__  