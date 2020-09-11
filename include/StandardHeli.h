#pragma once
#include "Helicopters.h"
#include "Globals.h"

class StandardHeli : public Helicopters
{
public:

	StandardHeli();
	~StandardHeli();
	StandardHeli(b2World& MyWorld, b2Vec2 location, AssetManager*& manage);

	void CreatePropeller();
	void CreateGun();
	void CreateJoint();

	virtual bool getStatus() override;
	virtual void SpawnHeli(sf::RenderWindow& window) override;
	virtual void movingHeli(const int time) override;
	virtual void SetGunRotaion() override;
	virtual void Shooter(sf::RenderWindow& window,sf::Clock& time, sf::Vector2f& pos) override;

private:

	bool m_Killed = false;
	float speed = SPEED_STANDARD_HELI;
	b2World& m_MyWorld;

	AssetManager* manage = manage->getInstance();
	sf::Sound HeliSound;
	int PosGun_X = 30;
	int m_life ;
	int PosPropeller_X = 30;

};

