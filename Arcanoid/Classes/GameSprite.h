#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public CCSprite {
public:
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);

	GameSprite(void);
	~GameSprite(void);

	static GameSprite* gameSpriteWithFile(const char *pszFileName);
	virtual void setPosition(const CCPoint& pos);
};
#endif // __GAMESPRITE_H__y