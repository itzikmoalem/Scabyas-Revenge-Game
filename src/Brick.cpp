#include "Brick.h"

Brick::Brick()
{
}

void Brick::setPlatfromSprite(sf::Sprite& sprite)
{
	m_platfromSprite = sprite;
}

sf::Sprite& Brick::getPlatfromSprite()
{
	return m_platfromSprite;
}

Brick::~Brick()
{
}
