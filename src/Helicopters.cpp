#include "Helicopters.h"

Helicopters::Helicopters()
{
}


Helicopters::~Helicopters()
{
}



void Helicopters::SetHeliBody(const sf::Sprite& b)
{
	m_heli_body = b;
}

sf::Sprite Helicopters::GetHeliBody()
{
	return m_heli_body;
}

void Helicopters::SetHeliPropeller(const sf::Sprite& p)
{
	m_heli_propeller = p;
}

sf::Sprite Helicopters::GetHeliPropeller()
{
	return m_heli_propeller;
}

void Helicopters::SetHeliGun(const sf::Sprite& g)
{
	m_heli_gun = g;
}

sf::Sprite Helicopters::GetHeliGun()
{
	return m_heli_gun;
}

void Helicopters::SetJoint(b2RevoluteJoint* j)
{
	m_joint = (b2RevoluteJoint*)j;
}

void Helicopters::Setb2Body(b2Body*& b)
{
	m_Body = b;
}

b2Body* Helicopters::getb2Body()
{
	return m_Body;
}

void Helicopters::Setb2Gun(b2Body*& g)
{
	m_Gun = g;
}

b2Body* Helicopters::getb2Gun()
{
	return m_Gun;
}

void Helicopters::SetLinearHelper(const b2Vec2& v)
{
	m_Body->SetLinearVelocity(v);
}

void Helicopters::SetPositionBodyHelper(const float& x, const float& y)
{
	m_heli_body.setPosition(x, y);
}

void Helicopters::SetPositionGunHelper(const float& x, const float& y)
{
	m_heli_gun.setPosition(x, y);
}


void Helicopters::MakeRotation(float f)
{
	while (f > 180)
		f -= 180;

	m_heli_gun.setRotation(f);
}
