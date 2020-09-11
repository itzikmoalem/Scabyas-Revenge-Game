#include "Enemies.h"

Enemies::Enemies() 
{
}


void Enemies::SetHp(int HP)
{
	m_HP = HP;
}

void Enemies::DecreaseHP()
{
	m_HP -= 20;
}

int Enemies::GetHp()
{
	return m_HP;
}

Enemies::~Enemies()
{
}
