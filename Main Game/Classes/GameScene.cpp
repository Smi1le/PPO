#include "GameScene.h"
#include "Bonus.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <algorithm>
#include "GameOverScene.h"
#include "GameWinScene.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;

SGameState g_gameState;

Scene* CGameScene::createScene(int livesPlayer)
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	g_gameState.remainingNumberTanks = 20;
	g_gameState.numberLivesPlayer = livesPlayer;
	auto layer = CGameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool CGameScene::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
	if (!Layer::init())
	{
		return false;
	}

	auto tileMap = TMXTiledMap::create("Game/level.tmx");
	tileMap->setPosition(Vec2(64, 0));
	this->addChild(tileMap);
	if (!initGameObjects(tileMap))
	{
		return false;
	}
	
	m_animation.initPlayerAnimation();
	CreateButton();
	

	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CGameScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CGameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->setTouchEnabled(true);
	this->schedule(schedule_selector(CGameScene::ChangeDirEnemy), 5.0);
	this->schedule(schedule_selector(CGameScene::AddEnemy), 7.0);
	this->scheduleUpdate();
	return true;
}

bool CGameScene::initGameObjects(TMXTiledMap *tileMap)
{
	CCTMXObjectGroup *objectGroup = tileMap->objectGroupNamed("Objects");

	int i = 100;
	for (Value solid1 : objectGroup->getObjects())
	{
		ValueMap props = solid1.asValueMap();

		if (props.at("name").asString() == "DestroyedSolid")
		{
			CBrick *block = new CBrick();
			if (!block->init(this, Vec2(props.at("x").asFloat() + 77.f, props.at("y").asFloat() + 11.f), i++))
			{
				return false;
			}
		}
		else if (props.at("name").asString() == "Solid")
		{
			auto gateBody = PhysicsBody::createBox(Size(props.at("width").asFloat(), props.at("height").asFloat()));
			gateBody->setDynamic(false);
			gateBody->setContactTestBitmask(true);
			gateBody->setCollisionBitmask(BORDER_CONTACT_BITMASK);
			auto gateNode = GameSprite::gameSpriteWithFile("11.png");;
			gateNode->setPosition(Point(props.at("x").asFloat() + (props.at("width").asFloat() / 2.f) + 64.f,
				(props.at("y").asFloat() + (props.at("height").asFloat() / 2.f))));
			gateNode->setPhysicsBody(gateBody);
			this->addChild(gateNode);
		}
		else if (props.at("name").asString() == "health")
		{
			char score_buffer[10];
			sprintf(score_buffer, "%i", g_gameState.numberLivesPlayer);
			m_labelHealthPlayer = CCLabelTTF::create("", "Arial", props.at("height").asFloat());
			m_labelHealthPlayer->setPosition(ccp(props.at("x").asFloat() + 77.f, props.at("y").asFloat()));
			m_labelHealthPlayer->setColor({ 255, 255, 0 });
			m_labelHealthPlayer->setString(score_buffer);
			this->addChild(m_labelHealthPlayer);
		}
		else if (props.at("name").asString() == "player")
		{
			m_player = new (std::nothrow) CPlayer();
			g_gameState.posInitPlayer = Vec2(props.at("x").asFloat() + 77.f, props.at("y").asFloat() + 11.f);
			m_player->init(g_gameState.posInitPlayer, this);
		}
		else if (props.at("name").asString() == "respEnemy")
		{
			g_gameState.respPositions.push_back(props);
		}
		else if (props.at("name").asString() == "Bonus")
		{
			g_gameState.bonusesPositions.push_back(props);
		}
		else if (props.at("name").asString() == "eagle")
		{
			m_eagleSprite = GameSprite::gameSpriteWithFile("Game/eagle.png");
			auto bodyEagle = PhysicsBody::createBox(Size(props.at("width").asFloat(), props.at("height").asFloat()));
			bodyEagle->setGravityEnable(false);
			bodyEagle->setDynamic(false);
			bodyEagle->setRotationEnable(false);
			bodyEagle->setCollisionBitmask(MASK_EAGLE);
			bodyEagle->setContactTestBitmask(true);
			m_eagleSprite->setPhysicsBody(bodyEagle);
			m_eagleSprite->setPosition(Vec2(props.at("x").asFloat() + 90.f, props.at("y").asFloat() + 20.f));
			addChild(m_eagleSprite);
		}
	}
	return true;
}

void CGameScene::CreateButton()
{
	m_buttons.push_back(CButton::create(this, Vec2(50.f, 275.f), 1000, TypeButton::UP, "Up.png"));
	m_buttons.push_back(CButton::create(this, Vec2(50.f, 125.f), 1001, TypeButton::LEFT, "Left.png"));
	m_buttons.push_back(CButton::create(this, Vec2(50.f, 200.f), 1002, TypeButton::DOWN, "Down.png"));
	m_buttons.push_back(CButton::create(this, Vec2(50.f, 50.f), 1003, TypeButton::RIGHT, "Right.png"));

	auto fire = MenuItemImage::create("psd_2_.png", "psd_back.png", CC_CALLBACK_1(CGameScene::ShootPlayer, this));
	fire->setPosition(Point(860.f, 70.f));

	auto buttonFire = Menu::create(fire, NULL);
	buttonFire->setPosition(Point::ZERO);

	this->addChild(buttonFire);
}

bool CGameScene::onTouchBegan(Touch* touches, Event* event) {
	if (touches)
	{
		for (auto button : m_buttons)
		{
			if (button->IsContainsPoint(touches->getLocation()))
			{
				button->IsTouch = true;
			}
		}
		m_player->isMove = true;
		return true;
	}
	return false;
}

void CGameScene::onTouchEnded(Touch* touches, Event* event)
{
	for (auto button : m_buttons)
	{
		if (button->IsTouch)
		{
			button->IsTouch = false;
			m_player->isMove = false;
			m_player->Control(STATE::STAY);
		}
	}
}

void CGameScene::StepPlayer()
{
	for (auto button : m_buttons)
	{
		if (button->IsTouch)
		{
			if (button->GetTypeButton() == TypeButton::DOWN)
			{
				m_player->Control(STATE::DOWN);
			}
			if (button->GetTypeButton() == TypeButton::LEFT)
			{
				m_player->Control(STATE::LEFT);
			}
			if (button->GetTypeButton() == TypeButton::RIGHT)
			{
				m_player->Control(STATE::RIGHT);
			}
			if (button->GetTypeButton() == TypeButton::UP)
			{
				m_player->Control(STATE::UP);
			}
		}
	}
}

void CGameScene::update(float dt)
{
	if (g_gameState.numberLivesPlayer == -1)
	{
		GoToGameOverScene(this);
	}
	for (size_t i = 0; i != m_enemyList.size(); ++i)
	{
		int shoot = cocos2d::random(0, 50);
		if (shoot == 20 && !m_enemyList.at(i)->IsShot())
		{
			m_enemyList.at(i)->Shoot(this);
		}
	}
	if (m_player->isMove)
	{
		StepPlayer();
	}
	if (g_gameState.remainingNumberTanks == 0 && m_enemyList.empty())
	{
		auto scene = CGameWinScene::createScene();
		Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
	}
	if (m_needTimer)
	{
		m_timer += dt;
		if (m_timer >= 1.5f)
		{
			m_needTimer = false;
			m_player = new (std::nothrow) CPlayer();
			m_player->init(g_gameState.posInitPlayer, this);
			m_player->ReleasedBullet();
		}
	}

}

bool CGameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	//игрок и бордюр
	if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		m_player->isMove = false;
		return true;
	}
	//игрок и кирпич
	if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(MASK_BRICK == b->getCollisionBitmask())) ||
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(MASK_BRICK == a->getCollisionBitmask())))
	{
		m_player->isMove = false;
		return true;
	}
	//враг и кирпич
	if (((MASK_ENEMY == a->getCollisionBitmask()) &&
		(MASK_BRICK == b->getCollisionBitmask())) ||
		((MASK_ENEMY == b->getCollisionBitmask()) &&
		(MASK_BRICK == a->getCollisionBitmask())))
	{
		if (a->getNode() != NULL &&  b->getNode() != NULL)
		{
			int tag = MASK_ENEMY == a->getCollisionBitmask() ? a->getNode()->getTag() : b->getNode()->getTag();
			for (auto en : m_enemyList)
			{
				if (en->GetTag() == tag)
				{
					en->ChangeDirection();
					break;
				}
			}

			
		}
		return true;
	}
	//враг и враг
	if ((MASK_ENEMY == a->getCollisionBitmask()) &&
		(MASK_ENEMY == b->getCollisionBitmask()))
	{
		for (auto en : m_enemyList)
		{
			if (en->GetTag() == a->getNode()->getTag())
			{
				en->ChangeDirection();
			}
			if (en->GetTag() == b->getNode()->getTag())
			{
				en->ChangeDirection();
			}
		}
		return true;
	}

	//Пуля и пуля
	if ((MASK_BULLET == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask()))
	{
		if (a->getNode() != NULL && b->getNode() != NULL)
		{
			int PlayerBullet = a->getNode()->getTag();
			int EnemyBullet = b->getNode()->getTag();
			if (b->getNode()->getTag() == TAG_BULLET_PLAYER)
			{
				PlayerBullet = b->getNode()->getTag();
				EnemyBullet = a->getNode()->getTag();
			}
			for (auto enemy : m_enemyList)
			{
				if (EnemyBullet == enemy->GetBulletTag())
				{
					enemy->ChangeResolution();
				}
			}
			m_player->ChangeResolution();
			this->addChild(m_animation.Explosion(a->getNode()->getPosition()));
			this->addChild(m_animation.Explosion(b->getNode()->getPosition()));
			removeChildByTag(EnemyBullet);
			removeChildByTag(PlayerBullet);
		}
		return true;
	}
	//Враг и бордюр
	if (((MASK_ENEMY == a->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == b->getCollisionBitmask())) ||
		((MASK_ENEMY == b->getCollisionBitmask()) &&
		(BORDER_CONTACT_BITMASK == a->getCollisionBitmask())))
	{
		int tag = MASK_ENEMY == a->getCollisionBitmask() ? a->getNode()->getTag() : b->getNode()->getTag();
		for (auto en : m_enemyList)
		{
			if (en->GetTag() == tag)
			{
				en->ChangeDirection();
				break;
			}
		}
		return true;
	}
	// Пуля игрока и враг
	if (((MASK_ENEMY == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((MASK_ENEMY == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		int tagA = a->getNode()->getTag();
		int tagB = b->getNode()->getTag();
		if (tagA == TAG_BULLET_PLAYER || tagB == TAG_BULLET_PLAYER)
		{
			for (size_t i = 0; i != m_enemyList.size(); ++i)
			{
				if (tagB == m_enemyList.at(i)->GetTag() || 
					tagA == m_enemyList.at(i)->GetTag())
				{
					m_enemyList.erase(m_enemyList.begin() + i);
					break;
				}
			}
			--g_gameState.numberEnemys;
			m_player->ChangeResolution();
			this->addChild(m_animation.Explosion(a->getNode()->getPosition()));
			this->addChild(m_animation.Explosion(b->getNode()->getPosition()));
			removeChildByTag(tagB);
			removeChildByTag(tagA);
			return true;
		}
		return false;
	}
	//Игрок и пуля
	if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||	
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		int tagA = a->getNode()->getTag();
		int tagB = b->getNode()->getTag();
		auto posBul = a->getNode()->getPosition();
		for (size_t i = 0; i != m_enemyList.size(); ++i)
		{
			if (tagA == m_enemyList.at(i)->GetBulletTag() ||
				tagB == m_enemyList.at(i)->GetBulletTag())
			{	
				m_needTimer = true;
				this->addChild(m_animation.Explosion(m_player->GetPosition()));
				this->addChild(m_animation.Explosion(posBul));
				removeChildByTag(m_player->GetTag());
				removeChildByTag(tagA);
				MinusPlayerLives();
				m_enemyList.at(i)->ChangeResolution();
				break;
			}	
		}
		
		return true;
	}
	//Бордюр и пуля
	if (((BORDER_CONTACT_BITMASK == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((BORDER_CONTACT_BITMASK == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		int tagBullet = a->getNode()->getTag();
		auto pos = a->getPosition();
		if (MASK_BULLET == b->getCollisionBitmask())
		{
			pos = b->getPosition();
			tagBullet = b->getNode()->getTag();
		}
		if (tagBullet == TAG_BULLET_PLAYER)
		{
			m_player->ChangeResolution();
		}
		else
		{
			for (size_t i = 0; i != m_enemyList.size(); ++i)
			{
				if (tagBullet == m_enemyList.at(i)->GetBulletTag())
				{
					m_enemyList.at(i)->ChangeResolution();
					break;
				}
			}
		}
		addChild(m_animation.Explosion(pos));
		removeChildByTag(tagBullet);
		return true;
	}
	//Кирпич и пуля
	if (((MASK_BRICK == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((MASK_BRICK == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		int tagA = INT_MAX;
		int tagB = INT_MAX;
		if (a->getNode() != NULL)
		{
			tagA = a->getNode()->getTag();
			this->addChild(m_animation.Explosion(a->getPosition()));
			removeChildByTag(tagA);
		}
		if (b->getNode() != NULL)
		{
			tagB = b->getNode()->getTag();
			this->addChild(m_animation.Explosion(b->getPosition()));
			removeChildByTag(tagB);
		}
		if (tagA == TAG_BULLET_PLAYER || tagB == TAG_BULLET_PLAYER)
		{
			m_player->ChangeResolution();
		}
		else
		{
			for (size_t i = 0; i != m_enemyList.size(); ++i)
			{
				if (tagA == m_enemyList.at(i)->GetBulletTag() || 
					tagB == m_enemyList.at(i)->GetBulletTag())
				{
					m_enemyList.at(i)->ChangeResolution();
					break;
				}
			}
		}
		
		
		return true;
	}
	//Eagle и пуля
	if (((MASK_EAGLE == a->getCollisionBitmask()) &&
		(MASK_BULLET == b->getCollisionBitmask())) ||
		((MASK_EAGLE == b->getCollisionBitmask()) &&
		(MASK_BULLET == a->getCollisionBitmask())))
	{
		int tagA = INT_MAX;
		int tagB = INT_MAX;
		if (a->getNode() != NULL)
		{
			tagA = a->getNode()->getTag();
			this->addChild(m_animation.Explosion(a->getPosition()));
			removeChildByTag(tagA);
		}
		if (b->getNode() != NULL)
		{
			tagB = b->getNode()->getTag();
			this->addChild(m_animation.Explosion(b->getPosition()));
			removeChildByTag(tagB);
		}

		GoToGameOverScene(this);
		return true;
	}
	if (((MASK_PLAYER == a->getCollisionBitmask()) &&
		(MASK_BONUS == b->getCollisionBitmask())) ||
		((MASK_PLAYER == b->getCollisionBitmask()) &&
		(MASK_BONUS == a->getCollisionBitmask())))
	{
		int tagA = INT_MAX;
		auto bonusBody = MASK_BONUS == b->getCollisionBitmask() ? b : a;
		if (TAG_BONUS_ADD_LIVES == bonusBody->getNode()->getTag())
		{
			char score_buffer[10];
			sprintf(score_buffer, "%i", ++g_gameState.numberLivesPlayer);
			m_labelHealthPlayer->setString(score_buffer);
			removeChildByTag(TAG_BONUS_ADD_LIVES);
		}
		else if (TAG_BONUS_EXPLOSION_ENEMYS == bonusBody->getNode()->getTag())
		{
			for (auto enemy : m_enemyList)
			{
				--g_gameState.numberEnemys;
				this->addChild(m_animation.Explosion(enemy->GetPosition()));
				removeChildByTag(enemy->GetTag());
			}
			removeChildByTag(TAG_BONUS_EXPLOSION_ENEMYS);
			m_enemyList.clear();
		}
		return true;
	}
	m_player->isMove = true;
	return false;
}

void CGameScene::ShootPlayer(cocos2d::Ref *ref)
{
	auto node = this->getChildByTag(TAG_BULLET_PLAYER);
	if (node == NULL)
	{
		m_player->ReleasedBullet();
	}
	if (!m_player->IsShot())
	{
		m_player->Shoot(this);
	}
}

void CGameScene::ChangeDirEnemy(float dt)
{
	int i = 0;
	for (auto enemy : m_enemyList)
	{
		enemy->ChangeDirection();
	}
}

void CGameScene::AddEnemy(float dt)
{
	if (g_gameState.numberEnemys < 5 && g_gameState.remainingNumberTanks != 0)
	{
		auto props = g_gameState.respPositions.at(g_gameState.numberRespPos++);
		auto enemyResp = new (std::nothrow) CEnemy();
		enemyResp->init(cocos2d::Vec2(props.at("x").asFloat() + 77.f,
			props.at("y").asFloat() + props.at("height").asFloat() / 2.f), STATE::DOWN,
			--g_gameState.remainingNumberTanks, this); // 100 100
		m_enemyList.push_back(enemyResp);
		++g_gameState.numberEnemys;
		if (g_gameState.numberRespPos == g_gameState.respPositions.size())
		{
			g_gameState.numberRespPos = 0;
		}
		if ((20 - g_gameState.remainingNumberTanks) % 6 == 0)
		{
			AddBonus();
		}
	}
}

void CGameScene::GoToGameOverScene(cocos2d::Ref *sender)
{
	auto scene = CGameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void CGameScene::MinusPlayerLives()
{
	char score_buffer[10];
	sprintf(score_buffer, "%i", --g_gameState.numberLivesPlayer);
	m_labelHealthPlayer->setString(score_buffer);
}

void CGameScene::AddBonus()
{
	ValueMap bonusMap = g_gameState.bonusesPositions.at(g_gameState.bonusNumber);
	if (g_gameState.bonusNumber == 0)
	{
		addChild(CBonus::create(Vec2(bonusMap.at("x").asFloat() + 90.f, bonusMap.at("y").asFloat() + 20.f),
			this, TAG_BONUS_EXPLOSION_ENEMYS));
		g_gameState.bonusNumber++;
	}
	else
	{
		addChild(CBonus::create(Vec2(bonusMap.at("x").asFloat() + 90.f, bonusMap.at("y").asFloat() + 20.f),
			this, TAG_BONUS_ADD_LIVES));
		g_gameState.bonusNumber--;

	}
}