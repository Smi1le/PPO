#include "GameLayer.h"
#include "TransitionalScene.h"
#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Config.h"

USING_NS_CC;

static std::shared_ptr<CGameState> g_gameState;

using namespace cocostudio::timeline;

Scene* CGameLayer::createScene(std::shared_ptr<CGameState> gameState)
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	g_gameState = gameState;
	auto layer = CGameLayer::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool CGameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();

	auto playItem = MenuItemImage::create("psd_2_.png", "psd_back.png", CC_CALLBACK_1(CGameLayer::gotoMenuScene, this));
	playItem->setPosition(Point(m_visibleSize.width - 25, m_visibleSize.height - 25));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	m_screenSize = CCDirector::sharedDirector()->getWinSize();

	auto sprite = GameSprite::create("background.png");
	sprite->setPosition(ccp(m_screenSize.width * 0.5, m_screenSize.height* 0.5));
	this->addChild(sprite, -1);

	auto gateBody = PhysicsBody::createBox(Size(m_visibleSize.width, 5.0f));
	gateBody->setDynamic(false);
	gateBody->setContactTestBitmask(true);
	gateBody->setContactTestBitmask(BORDER_CONTACT_BITMASK);
	gateBody->setCollisionBitmask(BORDER_CONTACT_BITMASK);
	auto gateNode = make_cc<Node>();
	gateNode->setPosition(Point(m_visibleSize.width / 2.0f, 0.0f));
	gateNode->setPhysicsBody(gateBody);
	addChild(gateNode);
	

	Point coordinates = { 0.1f, 0.85f };
	for (int i = 1; i <= MAX_NUMBER_BLOCKS; ++i)
	{
		CBlock* spr = new CBlock(this, ccp(coordinates.x, coordinates.y), TAG_START_BLOCK + i);
		m_blocks.push_back(spr);
		coordinates.x += 0.1f;
		if (i % 9 == 0)
		{
			coordinates = { 0.1f, coordinates.y - 0.05f };
		}
	}

	auto edgeBody = PhysicsBody::createEdgeBox(m_visibleSize, PhysicsMaterial(0, 0.5f, 0), 0);
	edgeBody->setDynamic(false);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(m_visibleSize.width / 2 + m_origin.x, m_visibleSize.height / 2 + m_origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
	
	m_player = new CRacket(this);
	
	CBall *_ball = new CBall(this, g_gameState->m_acc * g_gameState->m_level, m_player->GetPosition());
	m_ball.push_back(_ball);

	m_labelScore = CCLabelTTF::create("You score", "Arial", SIZE_LABEL);
	m_labelScore->setPosition(ccp(60, m_visibleSize.height - SIZE_LABEL));
	m_labelScore->setColor(COLOR_LABEL);
	m_labelScore->setTag(TAG_SCORE_LABEL);
	this->addChild(m_labelScore);

	m_playerScoreLabel = CCLabelTTF::create(std::to_string(g_gameState->m_score).c_str(), "Arial", SIZE_LABEL);
	m_playerScoreLabel->setPosition(ccp(135, m_visibleSize.height - SIZE_LABEL));
	m_playerScoreLabel->setColor(COLOR_LABEL);
	m_playerScoreLabel->setTag(TAG_PLAYER_SCORE_LABEL);
	this->addChild(m_playerScoreLabel);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CGameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CGameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CGameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CGameLayer::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	this->setTouchEnabled(true);
	
	this->scheduleUpdate();
	
	return true;
}

void CGameLayer::update(float dt)
{
	if (m_blocks.empty())
	{
		gotoTrancScene(this);
	}
	if (g_gameState->m_life == -1)
	{
		gotoGameOver(this);
	}

}

void CGameLayer::gotoGameOver(cocos2d::Ref *sender)
{
	auto scene = CGameOverScene::createScene(g_gameState);
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

bool CGameLayer::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	contact.getShapeA()->getTag();
	if (((MASK_BALL == a->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((MASK_BALL == b->getCollisionBitmask()) &&
			(BORDER_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		--g_gameState->m_life;
		this->removeChildByTag(TAG_BALL, true);
		auto it = m_ball.erase(m_ball.begin());
		CBall *_ball = new CBall(this, g_gameState->m_acc * g_gameState->m_level, m_player->GetPosition());
		m_ball.push_back(_ball);
		m_startBallMovement = false;
		return true;
	}

	if (((MASK_BALL == a->getCollisionBitmask()) &&
		(MASK_BLOCK == b->getCollisionBitmask())) ||
		((MASK_BALL == b->getCollisionBitmask()) &&
			(MASK_BLOCK == a->getCollisionBitmask())))
	{
		int pTag;
		if ((MASK_BALL == a->getCollisionBitmask()) && (MASK_BLOCK == b->getCollisionBitmask()))
		{
			pTag = b->getNode()->getTag();
		}
		else
		{
			pTag = a->getNode()->getTag();
		}

		int i = 0;
		for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it)
		{
			if (pTag == m_blocks[i]->getTag())
			{
				playerScore();
				m_blocks[i]->del(this);
				it = m_blocks.erase(it);
				--it;
			}
			++i;
		}
		return true;
	}
	else if ((a->getCollisionBitmask() == MASK_BALL && MASK_RACKET == b->getCollisionBitmask()) || 
		(b->getCollisionBitmask() == MASK_BALL && MASK_RACKET == a->getCollisionBitmask()))
	{
		return true;
	}
	return false;
}

bool CGameLayer::onTouchBegan(Touch* pTouches, CCEvent* event) {
	if (pTouches)
	{
		auto point = pTouches->getLocation();
		if (m_player->IsContainsPoint(point))
		{
			m_player->isTouch = true;
		}
	}
	return true;
}

void CGameLayer::gotoMenuScene(cocos2d::Ref *sender)
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void CGameLayer::gotoTrancScene(cocos2d::Ref *sender)
{
	auto scene = CTransitionalScene::createScene(g_gameState);
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void CGameLayer::onTouchMoved(Touch* pTouches, CCEvent* event) {
	if (pTouches)
	{
		auto point = pTouches->getLocation();
		if (m_player->isTouch)
		{
			m_player->Move(point);
			if (!m_startBallMovement)
			{
				m_ball[0]->Move(point);
			}
		}
	}
}

void CGameLayer::onTouchEnded(Touch* pTouches, CCEvent* event) {
	if (m_player->isTouch)
	{
		m_player->isTouch = false;
	}

	if (!m_startBallMovement)
	{
		m_ball[0]->Start();
		m_startBallMovement = true;
	}
}

void CGameLayer::playerScore()
{
	//SimpleAudioEngine::sharedEngine()->playEffect("score.wav");
	char score_buffer[10];
	++g_gameState->m_score;
	sprintf(score_buffer, "%i", g_gameState->m_score);
	m_playerScoreLabel->setString(score_buffer);
}