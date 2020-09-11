#pragma once
#include "Objects.h"

class Enemies : public Objects
{
public:
	Enemies();
	void SetHp(int HP);
	void DecreaseHP();
	int GetHp();
	~Enemies();

private:
	int m_HP;
};
