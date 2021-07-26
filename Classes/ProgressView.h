#ifndef __PROGRESS_VIEW_H__  
#define __PROGRESS_VIEW_H__ 

#include "cocos2d.h"
USING_NS_CC;
class ProgressView : public Layer
{
public:
	ProgressView();
	void setBackgroundTexture(const char *pName);
	void setForegroundTexture(const char *pName);
	void setTotalProgress(float total);
	void setCurrentProgress(float progress);
	float getCurrentProgress() const;
	float getTotalProgress() const;
	bool getIsDead() { return currentProgress == 0 ? true : false; }
private:
	void setForegroundTextureRect(const Rect &rect);

private:
	Sprite *progressBackground;
	Sprite *progressForeground;
	float totalProgress;
	float currentProgress;
	float scale;
};

#endif // __PROGRESS_VIEW_H__  