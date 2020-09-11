#include "Hostage.h"


/*Hostage::Hostage()
{
}*/

Hostage::Hostage(b2World& MyWorld, const sf::Vector2f& vec, AssetManager* &manage, const int host) : m_MyWorld(MyWorld)
{
	SetTextureRandomally(manage);

	m_sprite.scale(0.8, 0.8);
	m_sprite.setPosition(vec);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(vec.x / SCALE, vec.y / SCALE);
	BodyDef.type = b2_dynamicBody;

	m_body = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_sprite.getGlobalBounds().width / 3.4) / SCALE, (m_sprite.getGlobalBounds().height / 2.1) / SCALE);

	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.3;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = HOSTAGE;
	FixtureDef.filter.maskBits = FRIENDLY_SOLDIER | BOUNDARY | PLATFORM;
	m_body->CreateFixture(&FixtureDef);

	int Num = 70 + host;

	m_body->SetUserData((void*)(Num));
}

void Hostage::setHostageSprite(sf::Sprite& sprite)
{
	m_sprite = sprite;
}

sf::Sprite& Hostage::getHostageSprite()
{
	return m_sprite;
}

//This method delete the hostage
void Hostage::hukusPukus()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

void Hostage::setHostageBody(b2Body*& body)
{
	m_body = body;
}

void Hostage::SpawnHostage(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//This method set randomally texturs for the hostages
void Hostage::SetTextureRandomally(AssetManager*& manage)
{
	unsigned int random = rand() % 100;

	if (random < 33)
	{
		m_sprite.setTexture(manage->GetTexture(O_HOSTAGE1));
		m_sprite.setOrigin(manage->GetTexture(O_HOSTAGE1).getSize().x / 2, manage->GetTexture(O_HOSTAGE1).getSize().y / 2);
	}
	else if (random < 66 && random >= 33)
	{
		m_sprite.setTexture(manage->GetTexture(O_HOSTAGE2));
		m_sprite.setOrigin(manage->GetTexture(O_HOSTAGE2).getSize().x / 2, manage->GetTexture(O_HOSTAGE2).getSize().y / 2);
	}
	else
	{
		m_sprite.setTexture(manage->GetTexture(O_HOSTAGE3));
		m_sprite.setOrigin(manage->GetTexture(O_HOSTAGE3).getSize().x / 2, manage->GetTexture(O_HOSTAGE3).getSize().y / 2);
	}
}

b2Body*& Hostage::getHostageBody()
{
	return m_body;
}

Hostage::~Hostage()
{
	//std::cout << "Distractur" << std::endl;
	//m_MyWorld.DestroyBody(m_body);
}