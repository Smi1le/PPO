#pragma once
static const float SPEED_ENEMY_AND_PLAYER = 100.f;
static const float SPEED_BULLET = 150.f;
static const int TAG_PLAYER = 88;
static const int TAG_BULLET_PLAYER = 1499;
static const int MAXIMUM_NUMBER_ENEMY_TANKS = 150.f;
static const auto MASK_PLAYER = 0x02;
static const auto MASK_BRICK = 0x03;
static const auto MASK_BUTTON = 0x04;
static const auto MASK_BULLET = 0x05;
static const auto BORDER_CONTACT_BITMASK = 0xffff;

enum class STATE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAY
};

template <class T, class ...TArgs>
T *make_cc(TArgs&&... args)
{
	T *ret = new (std::nothrow) T;
	if (ret && ret->init(std::forward<TArgs>(args)...)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}