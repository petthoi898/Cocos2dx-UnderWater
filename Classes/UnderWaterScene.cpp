
#include "UnderWaterScene.h"

USING_NS_CC;
Information* UnderWater::infor = NULL;
Scene* UnderWater::createScene(Information* _infor)
{
	infor = _infor;
	return UnderWater::create();
}

// on "init" you need to initialize your instance
bool UnderWater::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	for (auto item : infor->item) {
		auto it = new  Item(item->getItemID(), item->getItemName(), item->getItemDescription(), item->getItemImg(), item->getItemUsable(), item->getItemType(), Sprite::create(item->getItemName()));
		collectedItem.push_back(it);
		addChild(it->getSprite(), 2);
	}
	_tileMap = TMXTiledMap::create("maps/under_water.tmx");
	_background = _tileMap->getLayer("Background");
	//_blockage = _tileMap->getLayer("Blockage");
	//_blockage->setVisible(false);
	addChild(_tileMap, -1);
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Object");
	//CCASSERT(NULL != objects, "'Object-Player' object group not found");
	auto playerShowUpPoint = objects->getObject("spawnpoint");
	CCASSERT(!playerShowUpPoint.empty(), "PlayerShowUpPoint object not found");

	int x = playerShowUpPoint["x"].asInt();
	int y = playerShowUpPoint["y"].asInt();
	//init list item



	for (int i = 1; i <= 20; i++) {
		char imageName[100] = { 0 };
		sprintf(imageName, "items/%d.png", i);
		auto sprite = Sprite::create(imageName);
		auto item = new Item(i, imageName, imageName, imageName, 0, imageName, sprite);
		addChild(item->getSprite(), 5);
		item->getSprite()->setVisible(false);
		listItem.push_back(item);
	}

	// spawn enemy
	auto groupEnemy = _tileMap->getObjectGroup("Monster");
	CCASSERT(NULL != groupEnemy, "'Enemy' object group not found");

	auto monster = groupEnemy->getObjects();
	auto iteratorMonster = monster.begin();
	for (; iteratorMonster != monster.end(); iteratorMonster++) {
		ValueMap& dict = (*iteratorMonster).asValueMap();
		if ("dragon" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyDragon(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x, y));
			enemySprite->type = "dragon";
			addChild(enemySprite, 1);
		}
		else if ("Medusa" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyMedusa(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x, y));
			enemySprite->type = "medusa";
			addChild(enemySprite, 1);
		}
		else if ("Medon" == dict["name"].asString()) {
			float x = dict["x"].asFloat();
			float y = dict["y"].asFloat();
			Enemy* enemySprite = new Enemy();
			enemySprite->initSpriteEnemyDemon(Point(x, y));
			int spriteNumber = random();
			spriteNumber %= listItem.size();
			enemySprite->setItemEnemy(listItem.at(spriteNumber));
			enemySprite->itemEnemy->setSprite(Point(x, y));
			enemySprite->itemEnemy->getSprite()->setVisible(false);
			enemy.push_back(enemySprite);
			enemySprite->setViewEnemy(Point(x, y));
			enemySprite->type = "demon";
			addChild(enemySprite, 1);
		}
	}

	hero = Hero::create();
	hero->InitHeroSprite("character/hero_idle1.png");
	hero->setPosition(x, y);
	hero->setScale(2.2f);
	this->addChild(hero, 1);

	cameraView = Node::create();
	cameraView->setContentSize(visibleSize);
	this->addChild(cameraView);
	this->runAction(Follow::create(cameraView));
	setViewPointCenter(hero->getPosition());

	rocker = HRocker::createHRocker("joystick_center.png", "joystick_bg.png", Point(100, 100), listItem);// where the first picture is a rocker button, the second as the background  
	rocker->setPosition(-cameraView->getContentSize().width / 2, -cameraView->getContentSize().height / 2);
	rocker->setTag(50);
	rocker->startRocker(true);

	cameraView->addChild(rocker, 2);

	auto characterInfo = Node::create();
	characterInfo->setPosition(Point(-320, 330));
	cameraView->addChild(characterInfo);

	view = new ProgressView();
	view->setScale(2.2f);
	view->setBackgroundTexture("character/xue_back.png");
	view->setForegroundTexture("character/xue_fore.png");
	view->setTotalProgress(100);
	view->setCurrentProgress(this->infor->view->getCurrentProgress());

	aroundCharacter = Sprite::create("character/kuang.png");
	character = Sprite::create("character/touxiang.png");
	character->setPosition(Point(-120, 0));

	characterInfo->addChild(character, 2);
	characterInfo->addChild(aroundCharacter, 2);
	characterInfo->addChild(view, 2);

	this->scheduleUpdate();


    return true;
}

void UnderWater::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getVisibleSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
	auto viewPoint = centerOfView - actualPosition;
	if (viewPoint.x > winSize.width / 2) {
		cameraView->setPosition(viewPoint);
	}
	else cameraView->setPosition(actualPosition);
}

void UnderWater::update(float delta)
{
	setViewPointCenter(hero->getPosition());
	rocker->setQuickItem(collectedItem);
	auto a = cameraView->getPosition();
	auto heroX = hero->getPositionX();
	auto heroY = hero->getPositionY();
	if (rocker->isInAttack) {
		hero->getAttackAmination();
		auto it = enemy.begin();
		for (it; it != enemy.end(); it++) {

			if (!(*it)->isDead) {
				auto position = (*it)->enemySprite->getPositionY();
				if (std::abs(hero->getPositionY() - position) < 30)
				{
					if (isRectCollision(Rect(heroX, heroY, 32, 32),
						Rect((*it)->enemySprite->getPositionX(), (*it)->enemySprite->getPositionY(), 256, 256)))
					{
						combat((*it));
						(*it)->isHurt = true;
					}
				}
			}
			else {
				auto itemX = (*it)->itemEnemy->getSprite()->getPositionX();
				auto itemY = (*it)->itemEnemy->getSprite()->getPositionY();
				auto ene = (*it);
				if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
							//rocker->setQuickItem(listItem);
						}

					}
				}
			}
			rocker->isInAttack = false;
		}
	}

	//load item
	
	if(rocker->showedItem) rocker->loadQuickItem(cameraView->getPosition(), cameraView->getContentSize());
	// run 
	switch (rocker->rocketDirection)
	{
	case 1:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x + 5, hero->getPosition().y)); // right away  
		break;
	case  2:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y + 5));   // go up  
		break;
	case 3:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x - 5, hero->getPosition().y));   //turn left  
		break;
	case 4:
		hero->SetAnimation("character/run_animation.plist", "character/run_animation.png", "run", 6, rocker->rocketRun);// "run_" is a collection of images in each image run_animation.png common name part  
		hero->setPosition(Point(hero->getPosition().x, hero->getPosition().y - 5));   // go down  
		break;
	default:
		hero->StopAnimation();// Stop all animation and motion  
		break;

	}
}
bool UnderWater::isRectCollision(Rect rect1, Rect rect2) {

	float x1 = rect1.origin.x;
	float y1 = rect1.origin.y;
	float w1 = rect1.size.width;
	float h1 = rect1.size.height;
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1 + w1 * 0.5 < x2 - w2 * 0.5)
		return false;
	else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)
		return false;
	else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)
		return false;
	else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
		return false;

	return true;
}
void UnderWater::combat(Enemy* ene) {
	auto position = ene->enemySprite->getPositionY();
	auto heroX = hero->getPositionX();
	auto heroY = hero->getPositionY();
	if (std::abs(hero->getPositionY() - position) < 30)
	{
		if (isRectCollision(Rect(heroX, heroY, 32, 32),
			Rect(ene->enemySprite->getPositionX(), ene->enemySprite->getPositionY(), 256, 256)))
		{
			if ("dragon" == ene->type) {
				//ene->enemyRotation(heroX);
				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getDragonDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
							//rocker->setQuickItem(listItem);
						}

					}
				}
			}
			else if ("medusa" == ene->type) {

				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getMedusaDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
							//rocker->setQuickItem(listItem);
						}

					}
				}
			}
			else if ("demon" == ene->type) {
				ene->enemyHurt();
				if (heroX < ene->enemyPosition.x) ene->enemySprite->setFlippedX(true);
				else ene->enemySprite->setFlippedX(false);
				ene->enemyFollow(Point(heroX, heroY));
				ene->enemyAttack();
				view->setCurrentProgress(view->getCurrentProgress() - ene->getDemonDamage());
				ene->viewEnemy->setCurrentProgress(ene->viewEnemy->getCurrentProgress() - hero->getHeroDamage());
				ene->isDead = ene->viewEnemy->getCurrentProgress() > 0 ? 0 : 1;
				if (ene->isDead) {
					ene->enemyDead();
					ene->removeEnemyDead();
					if (!ene->itemDroped) {
						ene->itemEnemy->getSprite()->setVisible(true);
						auto setpos = ene->enemyPosition;
						ene->itemEnemy->setSprite(setpos);
						auto pos = ene->itemEnemy->getSprite()->getPosition();
						auto moveUp = MoveTo::create(1, pos + Point(0, 30));
						auto moveDown = MoveTo::create(0.5f, pos);
						auto seq = Sequence::create(moveUp, moveDown, NULL);
						ene->itemEnemy->getSprite()->runAction(seq);
						ene->itemDroped = true;
					}
					if (!ene->isCollected) {
						auto itemX = ene->itemEnemy->getSprite()->getPositionX();
						auto itemY = ene->itemEnemy->getSprite()->getPositionY();
						if (isRectCollision(Rect(heroX, heroY, 32, 32), Rect(itemX, itemY, 32, 32))) {
							CCLOG("Collision item");
							auto moveDown = MoveTo::create(1, rocker->getBagPosition());
							auto visibleItem = CallFunc::create([=]() {
								ene->itemEnemy->getSprite()->setVisible(false);
							});
							auto seq = Sequence::create(moveDown, visibleItem, NULL);
							ene->itemEnemy->getSprite()->runAction(seq);
							ene->isCollected = true;
							collectedItem.push_back(ene->itemEnemy);
							rocker->setQuickItem(collectedItem);
						}

					}
				}
			}
		}
	}
}
