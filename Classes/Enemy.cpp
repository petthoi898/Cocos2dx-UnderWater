#include "Enemy.h"  
//#include "ProgressView.h"

USING_NS_CC;

Enemy::Enemy() {
	itemDroped = false;
	isCollected = false;
	//itemEnemy = NULL;
	isDead = false;
	isHurt = false;
}
void Enemy::enemyHurt() {
	CCLOG("Enemy Hurt Animation");
	if (isDead) return;
	auto animation = Animation::create();
	if ("dragon" == type) {
		for (int i = 1; i <= 2; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/dragon/Hurt%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("medusa" == type) {
		for (int i = 1; i <= 2; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/medusa/Hurt%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("demon" == type) {
		for (int i = 1; i <= 2; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/demon/Hurt%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}

	animation->setDelayPerUnit(0.5);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);
	auto act = Animate::create(animation);

	enemySprite->runAction(act);
	CCLOG("End Enemy Hurt Animation");
	isHurt = true;
}
void Enemy::enemyAttack() {
	if (!isHurt) return;
	CCLOG("Enemy Attack");
	auto animation = Animation::create();
	if ("dragon" == type) {
		for (int i = 1; i <= 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/dragon/Attack%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->addSpriteFrameWithFile("enemy/dragon/Attack1.png");
	}
	else if ("demon" == type) {
		for (int i = 1; i <= 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/demon/Attack%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->addSpriteFrameWithFile("enemy/demon/Attack1.png");
	}
	else if ("medusa" == type) {
		for (int i = 1; i <= 6; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/medusa/Attack%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
		animation->addSpriteFrameWithFile("enemy/medusa/Attack1.png");
	}
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);
	auto act = Animate::create(animation);
	CCLOG("Enemy Attack Finished");
	enemySprite->runAction(act);
	isHurt = true;
}
void Enemy::enemyDead() {
	if (isDead) return;
	isDead = true;
	auto animation = Animation::create();

	if ("dragon" == type) {
		for (int i = 1; i <= 5; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/dragon/Death%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("medusa" == type) {
		for (int i = 1; i <= 6; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/medusa/Death%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("demon" == type) {
		for (int i = 1; i <= 6; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/demon/Death%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);
	auto act = Animate::create(animation);
	enemySprite->runAction(act);
}
void Enemy::enemyWalk() {

	auto animation = Animation::create();
	if ("dragon" == type) {
		for (int i = 1; i <= 5; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/dragon/Walk%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("medusa" == type) {
		for (int i = 1; i <= 4; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/medusa/Walk%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}
	else if ("demon" == type) {
		for (int i = 1; i <= 6; i++)
		{
			char szName[100] = { 0 };
			sprintf(szName, "enemy/demon/Walk%d.png", i);
			animation->addSpriteFrameWithFile(szName);
		}
	}

	animation->setDelayPerUnit(0.5);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);
	auto act = Animate::create(animation);

	enemySprite->runAction(act);

}
void Enemy::initSpriteEnemy(Point position, std::string type) {
	this->type = type;
	auto animationEnemy = Animation::create();
	enemySprite = Sprite::create("enemy/dragon/Idle1.png");
	if ("dragon" == type) {
		enemySprite = Sprite::create("enemy/dragon/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle2.png");
		animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle3.png");
	}
	else if ("medusa" == type) {
		enemySprite = Sprite::create("enemy/medusa/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle2.png");
		animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle3.png");
	}
	else if ("demon" == type) {
		enemySprite = Sprite::create("enemy/demon/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle1.png");
		animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle2.png");
		animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle3.png");
	}
	auto animation = Animate::create(animationEnemy);
	enemySprite->runAction(animation);
	addChild(enemySprite, 2);
}
void Enemy::initSpriteEnemyMedusa(Point position) {
	enemyPosition = position;
	enemySprite = Sprite::create("enemy/medusa/Idle1.png");

	enemySprite->setPosition(position);
	auto animationEnemy = Animation::create();
	animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle1.png");
	animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle2.png");
	animationEnemy->addSpriteFrameWithFile("enemy/medusa/Idle3.png");
	animationEnemy->setDelayPerUnit(0.2f);
	animationEnemy->setRestoreOriginalFrame(false);
	animationEnemy->setLoops(-1);

	auto animation = Animate::create(animationEnemy);
	enemySprite->runAction(animation);
	addChild(enemySprite, 2);

}
void Enemy::initSpriteEnemyDemon(Point position) {
	enemyPosition = position;
	enemySprite = Sprite::create("enemy/demon/Idle1.png");
	enemySprite->setPosition(position);
	auto animationEnemy = Animation::create();
	animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle1.png");
	animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle2.png");
	animationEnemy->addSpriteFrameWithFile("enemy/demon/Idle3.png");
	animationEnemy->setDelayPerUnit(0.2f);
	animationEnemy->setRestoreOriginalFrame(false);
	animationEnemy->setLoops(-1);

	auto animation = Animate::create(animationEnemy);
	enemySprite->runAction(animation);
	addChild(enemySprite, 2);

}
void Enemy::initSpriteEnemyDragon(Point position) {
	
	enemyPosition = position;
	enemySprite = Sprite::create("enemy/dragon/Idle1.png");
	enemySprite->setPosition(position);
	auto animationEnemy = Animation::create();
	animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle1.png");
	animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle2.png");
	animationEnemy->addSpriteFrameWithFile("enemy/dragon/Idle3.png");
	animationEnemy->setDelayPerUnit(0.2f);
	animationEnemy->setRestoreOriginalFrame(false);
	animationEnemy->setLoops(-1);

	auto animation = Animate::create(animationEnemy);
	enemySprite->runAction(animation);
	addChild(enemySprite, 2);

}
void Enemy::setViewEnemy(Point enemyPosition) {
	viewEnemy = new ProgressView();
	viewEnemy->setPosition(enemyPosition);
	viewEnemy->setBackgroundTexture("character/xue_back.png");
	viewEnemy->setForegroundTexture("character/xue_fore.png");
	viewEnemy->setTotalProgress(100);
	viewEnemy->setCurrentProgress(100);
	this->addChild(viewEnemy, 2);
}
void Enemy::removeEnemyDead() {
	removeChild(enemySprite);
	removeChild(viewEnemy);
}
void Enemy::enemyFollow(Point position) {
	const Point pastPos = enemyPosition;
	auto distance = sqrt(pow(position.x - enemyPosition.x, 2) + pow(position.y - enemyPosition.y, 2));
	if (distance <= 80) {
		auto move = MoveTo::create(3.5f, position);
		auto walk = CallFunc::create([=]() {
			enemyWalk();
		});
		auto seq = Sequence::create(walk, move, NULL);
		enemySprite->runAction(seq);
	}
	else {
		auto move = MoveTo::create(2.5f, pastPos);
		auto walk = CallFunc::create([=]() {
			enemyWalk();
		});
		enemySprite->runAction(move);
	}
}