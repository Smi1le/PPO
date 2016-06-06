#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

Scene* CGameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = CGameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool CGameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("GameOver/GameOverScene.csb");
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);
	auto pageView = rootNode->getChildByName("PageView");
	auto menu = pageView->getChildByName("Panel");

	cocos2d::ui::Button* menuButton = menu->getChildByName<cocos2d::ui::Button*>("gotoMenu");

	menuButton->addTouchEventListener(CC_CALLBACK_1(CGameOverScene::GoToMenuScene, this));
	addChild(rootNode);

	return true;
}


void CGameOverScene::GoToMenuScene(cocos2d::Ref *sender)
{
	auto scene = CMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}