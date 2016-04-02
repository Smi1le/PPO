#pragma once

class CGameState
{
public:
	CGameState(int score, float acc, int level, int life)
		: m_score(score), m_acc(acc), m_level(level), m_life(life)
	{

	}
	~CGameState() = default;
	int m_score;
	float m_acc;
	int m_level;
	int m_life;
};