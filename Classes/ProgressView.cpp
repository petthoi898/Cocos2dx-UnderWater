#include "ProgressView.h"
USING_NS_CC;
ProgressView::ProgressView()
	: progressBackground(NULL)
	, progressForeground(NULL)
	, totalProgress(0.0f)
	, currentProgress(0.0f)
	, scale(1.0f)
{

}
void ProgressView::setBackgroundTexture(const char *pName)
{
	progressBackground = Sprite::create(pName);
	this->addChild(progressBackground);
}

void ProgressView::setForegroundTexture(const char *pName)
{
	progressForeground = Sprite::create(pName);
	progressForeground->setAnchorPoint(Point(0.0f, 0.5f));//
	progressForeground->setPosition(Point(-progressForeground->getContentSize().width * 0.5f, 0));
	this->addChild(progressForeground);
}

void ProgressView::setTotalProgress(float total)
{
	if (progressForeground == NULL) { return; }
	scale = progressForeground->getContentSize().width / total;
	totalProgress = total;
}

void ProgressView::setCurrentProgress(float progress)
{
	if (progressForeground == NULL) { return; }
	if (progress <= 0.0f) { progress = 0.0f; }
	if (progress > totalProgress) { progress = totalProgress; }
	currentProgress = progress;
	float rectWidth = progress * scale;
	const Point from = progressForeground->getTextureRect().origin;
	const Rect rect = Rect(from.x, from.y, rectWidth, progressForeground->getContentSize().height);
	setForegroundTextureRect(rect);
}

void ProgressView::setForegroundTextureRect(const Rect &rect)
{
	progressForeground->setTextureRect(rect);
}



float ProgressView::getCurrentProgress() const
{
	return currentProgress;
}

float ProgressView::getTotalProgress() const
{
	return totalProgress;
}
