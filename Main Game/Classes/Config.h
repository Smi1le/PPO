#pragma warning (disable: 4996)

#pragma once
static const float SPEED_ENEMY_AND_PLAYER = 100.f;
static const float SPEED_BULLET = 150.f;
static const float ACTION_TIME = 0.5f;
static const int TAG_PLAYER = 88;
static const int TAG_BONUS_ADD_LIVES = 87;
static const int TAG_BONUS_EXPLOSION_ENEMYS = 86;
static const int TAG_ENEMY = 1530;
static const int TAG_BULLET_PLAYER = 1499;
static const int TAG_BULLET_ENEMY = 100;
static const int MAXIMUM_NUMBER_ENEMY_TANKS = 150.f;
static const auto MASK_PLAYER = 0x02;
static const auto MASK_BRICK = 0x03;
static const auto MASK_BUTTON = 0x04;
static const auto MASK_BULLET = 0x05;
static const auto MASK_EAGLE = 0x06;
static const auto MASK_ENEMY = 0x07;
static const auto MASK_BONUS = 0x08;
static const auto BORDER_CONTACT_BITMASK = 0xffff;

enum class STATE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAY
};
