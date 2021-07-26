#include "Hero.h"  
USING_NS_CC;

Hero::Hero()
{
	heroDamage = 0.0f;
	IsRunning = false;// not in play animation  
	HeroDirecton = false;// move to the right  
	Hero_name = NULL;
}

Hero::~Hero(void)
{

}
void Hero::InitHeroSprite(const char *hero_name)
{
	Hero_name = hero_name;
	this->m_HeroSprite = Sprite::create(hero_name);
	this->addChild(m_HeroSprite);
}
// animation can be run, attack, death, injury, etc.  
void Hero::SetAnimation(const char *name_plist, const char *name_png, const char *name_each, unsigned int num, bool run_directon)
{
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	if (IsRunning)
		return;
	Animation* animation = Animation::create();
	for (int i = 1; i <= num; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "character/hero_%s%d.png", name_each, i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1);
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;

	}
	
	Animate* act = Animate::create(animation);
	m_HeroSprite->runAction(act);
	IsRunning = true;

}
void Hero::StopAnimation()
{
	if (!IsRunning)
		return;
	m_HeroSprite->stopAllActions();// stop all current sprite animation  

	// restore the original initialization wizard map  
	this->removeChild(m_HeroSprite, TRUE);// delete the original spirit  
	m_HeroSprite = Sprite::create(Hero_name);// restore the original map like the wizard  
	m_HeroSprite->setFlippedX(HeroDirecton);
	this->addChild(m_HeroSprite);
	IsRunning = false;
	IsRunning = false;
}
void Hero::getAttackAmination() {
	if (IsRunning) return;
	Animation* animation = Animation::create();

	for (int i = 1; i <= 5; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "character/hero_attack%d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->addSpriteFrameWithFile("character/hero_idle1.png");

	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	Animate* act = Animate::create(animation);
	m_HeroSprite->runAction(act);
}