#pragma once

#include "Infantry.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <AssetManager.h>
#include <Globals.h>
#include <Bullet.h>
class AKSoldier : public Infantry
{
public:
	/*Infantry(b2World& MyWorld, const int Enum, const sf::Vector2f& vec, AssetManager*& manage);
	void setSoldierSprite(sf::Sprite& sprite);
	sf::Sprite& getSoldierSprite();
	~Infantry();*/
	//virtual void SpawnSoldier(sf::RenderWindow& window) override;
	//virtual sf::Sprite& getSoldierSprite() override;

	void SpawnSoldier(sf::RenderWindow& window);
	virtual sf::Sprite& getSoldierSprite() override;
	void CreateArm(const int num);
	AKSoldier(b2World& MyWorld,const sf::Vector2f& vec, const int num);
	virtual void CheckProximity(const sf::Vector2f &vec, sf::RenderWindow& window, sf::Clock& time, const bool sound) override;
	virtual  b2Body* GetSoldierBody()  override;
	virtual  b2Body* GetSoldierArm()  override;
	virtual bool isDead() override;
	virtual void setDead(const bool k) override;

	

	void MakeJoint();


private:
	AssetManager* manage = manage->getInstance();

	sf::CircleShape m_Range;

	sf::Sprite m_soldierSprite;
	sf::Sprite m_ArmSprite;
	b2World& m_MyWorld;
	b2Body* m_body;
	b2Body* m_arm;
	float Arm_Angle;

	b2RevoluteJoint* m_joint;
	bool m_dead ;
	bool m_LeftDirection;

	sf::Sound AK_Shot;
};
