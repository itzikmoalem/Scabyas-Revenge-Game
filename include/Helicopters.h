#pragma once
#include "Enemies.h"
#include <AssetManager.h>
#include <Globals.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <statehelpers.h>
#include <Bullet.h>

class Helicopters : public Enemies
{
public:
	Helicopters();
	virtual void SpawnHeli(sf::RenderWindow& window) = 0;
	virtual bool getStatus() = 0;
	virtual void movingHeli(const int time) = 0;
	virtual void SetGunRotaion() = 0;
	virtual void Shooter(sf::RenderWindow& ,sf::Clock& ,  sf::Vector2f& ) = 0;
	
	~Helicopters();

	void SetHeliBody(const sf::Sprite& b);
	sf::Sprite GetHeliBody();
	void SetHeliPropeller(const sf::Sprite& p);
	sf::Sprite GetHeliPropeller();
	void SetHeliGun(const sf::Sprite& g);
	sf::Sprite GetHeliGun();
	void SetJoint(b2RevoluteJoint* j);

	void Setb2Body(b2Body*& b);
	b2Body* getb2Body();
	void Setb2Gun(b2Body*& g);
	b2Body* getb2Gun();

	void SetLinearHelper(const b2Vec2& v);
	void SetPositionBodyHelper(const float& x, const float& y);
	void SetPositionGunHelper(const float& x, const float& y);



	//void SetGunRotaion();
	void MakeRotation(float f);


private:

	sf::Sprite m_heli_body;
	sf::Sprite m_heli_propeller;
	sf::Sprite m_heli_gun;
	b2Body* m_Body;
	b2Body* m_Gun;
	b2RevoluteJoint* m_joint;

};
