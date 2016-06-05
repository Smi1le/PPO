#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CMenuScene);
private:
	void GoToGameScene(cocos2d::Ref *sender);
};

#endif // __HELLOWORLD_SCENE_H__
