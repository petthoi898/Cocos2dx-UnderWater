#ifndef _ITEM_H_
#define _ITEM_H_
#include "cocos2d.h"
#include<iostream>
using namespace std;
USING_NS_CC;

class Item : public Scene
{
public:
	Item();
	Item(int tID, string tname, string tdescription, string timg, bool tusable, string ttype, Sprite* iitem);
	int getItemID();
	string getItemName();
	string getItemDescription();
	string getItemImg();
	bool getItemUsable();
	string getItemType();
	Sprite* getSprite() { return item; };
	void setSprite(Point pos) { item->setPosition(pos); }
	Item& operator =(const Item&item);
private:
	int ID;
	string name;
	string description;
	string img;
	bool usable;
	string type;
	Sprite* item;
};

inline Item::Item(int tID, string tname, string tdescription, string timg, bool tusable, string ttype, Sprite* iitem)
{
	ID = tID;
	name = tname;
	description = tdescription;
	img = timg;
	usable = tusable;
	type = ttype;
	item = iitem;
}

inline int Item::getItemID()
{
	return ID;
}

inline string Item::getItemName()
{
	return name;
}

inline string Item::getItemDescription()
{
	return description;
}

inline string Item::getItemImg()
{
	return img;
}

inline bool Item::getItemUsable()
{
	return usable;
}

inline string Item::getItemType()
{
	return type;
}

#endif // _ITEM_H_
