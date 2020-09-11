#pragma once
#include "Helicopters.h"
#include "Globals.h"
#include "MyContactListener.h"

class BombHeli : public Helicopters
{
public:
	BombHeli();
	~BombHeli();
	BombHeli(b2World& MyWorld, b2Vec2 location, AssetManager*& manage);

	void CreateGun();
	void CreatePropeller();
	//void CreateJoint();


	virtual bool getStatus() override;
	virtual void SpawnHeli(sf::RenderWindow& window) override;
	virtual void movingHeli(const int time) override;
	virtual void SetGunRotaion() override;
	virtual void Shooter(sf::RenderWindow& window, sf::Clock& time, sf::Vector2f& pos) override;

private:
	sf::Sprite m_health;
	sf::Sprite m_emptyHealth;
	bool m_Killed = false;

	float speed = SPEED_BOMB_HELI;
	b2World& m_MyWorld;

	AssetManager* manage = manage->getInstance();
	sf::Sound HeliSound;
	int PosGun_X = 30;

	int PosPropeller_X = 25;

	int m_life ;

};
