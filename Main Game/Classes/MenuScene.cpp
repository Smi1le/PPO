#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* CMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CMenuScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool CMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("Menu/MenuScene.csb");
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
	auto pageView = rootNode->getChildByName("PageView");
	auto menu = pageView->getChildByName("Main");
	auto setting = pageView->getChildByName("Setting");

	cocos2d::ui::Button* playButton = menu->getChildByName<cocos2d::ui::Button*>("gotoGame");

	playButton->addTouchEventListener(CC_CALLBACK_1(CMenuScene::GoToGameScene, this));
    addChild(rootNode);

    return true;
}


void CMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = CGameScene::createScene(2);
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}