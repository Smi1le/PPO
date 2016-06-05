#ifndef __GAMESPRITE_H__
#define __GAMESPRITE_H__

#include "cocos2d.h"

class GameSprite : public cocos2d::CCSprite {
public:
	CC_SYNTHESIZE(cocos2d::CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(cocos2d::CCPoint, _vector, Vector);
	CC_SYNTHESIZE(cocos2d::CCTouch *, _touch, Touch);

	GameSprite(void);
	~GameSprite(void);

	static GameSprite* gameSpriteWithFile(const char *pszFileName);
	virtual void setPosition(const cocos2d::CCPoint& pos);
};
#endif // __GAMESPRITE_H__y