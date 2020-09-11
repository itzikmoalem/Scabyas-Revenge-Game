#pragma
#include "Objects.h"
#include <SFML/Graphics.hpp>
class Brick : public Objects
{
public:
	Brick();
	void setPlatfromSprite(sf::Sprite &sprite);
	sf::Sprite& getPlatfromSprite();
	~Brick();

private:
	sf::Sprite m_platfromSprite;


};

