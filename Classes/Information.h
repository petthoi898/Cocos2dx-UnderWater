#ifndef _INFORMATION_H_
#define _INFORMATION_H_
#include "cocos2d.h"
#include "Hero.h"
#include "ProgressView.h"
#include "HRocker.h"
#include "Item.h"

USING_NS_CC;

class Information
{
public:
	Information(HRocker* rocker, Hero* hero, Node* camera, ProgressView* view, vector<Item*> listItem) { this->rocker = rocker, this->hero = hero, this->cameraView = camera, this->view = view, item = listItem; };
public:
	HRocker*  rocker;
	Hero*    hero;
	Node* cameraView;
	ProgressView* view;
	Sprite* aroundCharacter;
	Sprite* character;
	vector<Item*> item;
};


#endif // _INFORMATION_H_
