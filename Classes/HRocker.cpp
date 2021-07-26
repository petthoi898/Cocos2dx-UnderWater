#include "HRocker.h"
#include "PauseGameScene.h"
#include "Definitions.h"
#include "ItemScene.h"
#include "CraftScene.h"
const double PI = 3.1415;
USING_NS_CC;

vector<Item*> HRocker::currentItem;
HRocker::HRocker()
{
	isCraft = false;
	showedItem = false;
	rocketRun = false;
	isInRocker = false;
	isInAttack = false;
}

HRocker* HRocker::createHRocker(const char *rockerImageName, const char *rockerBGImageName, Vec2 position, vector<Item*> cur)
{
	currentItem = cur;
	HRocker *layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

void HRocker::rockerInit(const char* rockerImageName, const char* rockerBGImageName, const Vec2 position)
{
	Sprite *spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	addChild(spRockerBG, 0, tag_rockerBG);

	Sprite *spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	addChild(spRocker, 1, tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRockerBG->getContentSize().width*0.5;//
	rocketDirection = -1; // represents the same joystick direction

	// button skill
	buttonAttack = Sprite::create("Button.png");
	buttonAttack->setPosition(position + Point(770, 30));
	buttonAttack->setVisible(true);
	buttonAttack->setScale(0.4f);
	addChild(buttonAttack, 2);
	buttonAttack->setTag(50);

	pauseGame = Sprite::create("gamecontrol/Settings Square Button.png");
	pauseGame->setScale(0.3f);
	pauseGame->setPosition(position + Point(850, 620));
	addChild(pauseGame, 2);

	// init balo item
	// quick slot
	quickSlot = Sprite::create("quickslot.png");
	quickSlot->setPosition(position + Point(403, -50));
	quickSlot->setScale(2.6f);
	addChild(quickSlot, -1);
	//quickSlot->setVisible(false);

	// Load item inventory
	extendedItem = Sprite::create("quickslot.png");
	extendedItem->setAnchorPoint(Point(0.5, 0));
	extendedItem->setPositionX(quickSlot->getPositionX());
	extendedItem->setPositionY(position.y + 55);
	extendedItem->setScale(2.6f);
	addChild(extendedItem);
	extendedItem->setVisible(false);

	// butotn more item
	buttonExtendItem = Sprite::create("up.png");
	buttonExtendItem->setPositionX(position.x + 400);
	buttonExtendItem->setPositionY(position.y + 20);
	buttonExtendItem->setScale(0.6f);
	addChild(buttonExtendItem, 3);
	// craft

	craft = Sprite::create("bua.png");
	craft->setPosition(position + Point(0, 100));
	craft->setScale(0.5f);
	//craft->setTag(50);
	addChild(craft, 1);


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto TouchListener = EventListenerTouchOneByOne::create();
	TouchListener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	TouchListener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	TouchListener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	TouchListener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);


	scaleAt = -1;
}


void HRocker::startRocker(bool _isStopOther)
{
	Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	Sprite *rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

}
void HRocker::stopRocker()
{
	Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	Sprite * rockerBG = (Sprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	this->removeChildByTag(tag_rocker); this->removeChildByTag(tag_rockerBG);

}
float HRocker::getRad(Vec2 pos1, Vec2 pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	float x = px2 - px1;
	float y = py1 - py2;
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cosAngle = x / xie;
	float rad = acos(cosAngle);
	if (py2 < py1)
	{
		rad = -rad;
	}
	return rad;
}

Vec2 getAngelePosition(float r, float angle) {
	return Point(r*cos(angle), r*sin(angle));
}

bool HRocker::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Vec2 Vec2 = pTouch->getLocation();
	Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
	if (rocker->getBoundingBox().containsPoint(Vec2))
	{
		isInRocker = true;
		isCanMove = true;
		CCLOG("In Joystick");
	}
	if (buttonAttack->getBoundingBox().containsPoint(Vec2)) {
		isInAttack = true;
		CCLOG("In Attack");
	}
	if (pauseGame->getBoundingBox().containsPoint(Vec2)) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		getParent()->visit();
		renderTexture->end();

		Director::getInstance()->pushScene(PauseGame::createScene(renderTexture));
	}
	if (buttonExtendItem->getBoundingBox().containsPoint(Vec2)) {
		if (!showedItem) {
			extendedItem->setVisible(true);
			for (int i = 8; i < quickItem.size(); i++) {
				quickItem.at(i)->getSprite()->setVisible(true);
			}
			showedItem = true;
		}
		else {
			extendedItem->setVisible(false);
			for (int i = 8; i < quickItem.size(); i++) {
				quickItem.at(i)->getSprite()->setVisible(false);
			}
			showedItem = false;
		}
	}
	auto size = quickItem.size();
	if (size > 8) size = 8;
	if (quickSlot->getBoundingBox().containsPoint(Vec2)) {
		if (scaleAt >= 0) {

			quickItem.at(scaleAt)->getSprite()->setScale(1);
		}
		if (scaleAt == int((Vec2.x - 310) / 48)) {
			quickItem.at(scaleAt)->getSprite()->setScale(1);
			scaleAt = -1;
		}
		else {
			scaleAt = (Vec2.x - 310) / 48;
			quickItem.at(scaleAt)->getSprite()->setScale(1.8f);
		}
	}
	
	if (craft->getBoundingBox().containsPoint(Vec2)) {
		auto node = (Sprite*)this->getChildByTag(50);
		auto node1 = (Sprite*)this->getChildByTag(tag_rockerBG);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
		renderTexture->begin();
		node->getParent()->visit();
		node1->getParent()->visit();
		renderTexture->end();
		
		Director::getInstance()->pushScene(CraftScene::createScene(renderTexture, currentItem));
		isCraft = true;
		
	}
	return true;
}
void HRocker::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	if (isInRocker) {
		if (!isCanMove)
		{
			return;
		}
		Vec2 Vec2 = pTouch->getLocation();
		Sprite *rocker = (Sprite *)this->getChildByTag(tag_rocker);
		float angle = getRad(rockerBGPosition, Vec2);
		if (sqrt(pow((rockerBGPosition.x - Vec2.x), 2) + pow((rockerBGPosition.y - Vec2.y), 2)) >= rockerBGR)
		{

			// to ensure that the internal length limit movement of the small circle
			rocker->setPosition(getAngelePosition(rockerBGR, angle) + Point(rockerBGPosition.x, rockerBGPosition.y));
			//	CCLOG("touch");
		}
		else rocker->setPosition(Vec2);
		if (angle >= -PI / 4 && angle < PI / 4)
		{
			rocketDirection = rocker_right;
			rocketRun = false;
			CCLOG("%d", rocketDirection);
		}
		else if (angle >= PI / 4 && angle < 3 * PI / 4)
		{
			rocketDirection = rocker_up;
			CCLOG("%d", rocketDirection);
		}
		else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI && angle < -3 * PI / 4))
		{
			rocketDirection = rocker_left;
			rocketRun = true;
			CCLOG("%d", rocketDirection);
		}
		else if (angle >= -3 * PI / 4 && angle < -PI / 4)
		{
			rocketDirection = rocker_down;
			CCLOG("%d", rocketDirection);
		}
		facePos = rocketDirection;
	}
}
void HRocker::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	if (!isCanMove)
	{
		return;
	}
	if (isInRocker) {
		Sprite *rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
		Sprite *rocker = (Sprite*)this->getChildByTag(tag_rocker);
		rocker->stopAllActions();
		rocker->runAction(MoveTo::create(0.08f, rockerBG->getPosition()));
		isCanMove = false;
		rocketDirection = rocker_stay;
		CCLOG("%d", rocketDirection);
		CCLOG("end");
		isInRocker = false;
	}
	if (isInAttack) {
		CCLOG("Attack animation");
		isInAttack = false;
	}
}
void HRocker::loadQuickItem(Point position, Size s) {
	int i = 1;
	for (auto item : quickItem) {
		if (i <= 8) {
			auto posX = getPositionX();
			auto posY = getPositionY();
			auto a = quickSlot->getPosition();
			item->getSprite()->setPositionX(position.x - s.width / 2 + 55 * i + 255);
			item->getSprite()->setPositionY(position.y - s.height / 2 + 50);
			item->getSprite()->setVisible(true);
			i++;
		}
		else break;
	}
	auto size = quickItem.size();
	if (size > 16)size = 16;
	int j = 1, k = 0;
	if (size > 8) {
		for (int i = 8; i < size; i++) {
			if (j <= 8) {
				quickItem.at(i)->getSprite()->setPositionX(position.x - s.width / 2 + 55 * j + 255);
				quickItem.at(i)->getSprite()->setPositionY(position.y - s.height / 2 + 190 + k * 59);
				j++;
			}
			else {
				k++;
				j = 1;
				quickItem.at(i)->getSprite()->setPositionX(position.x - s.width / 2 + 55 * j + 255);
				quickItem.at(i)->getSprite()->setPositionY(position.y - s.height / 2 + 190 + k * 59);
			}
		}
	}
}
