#pragma once

#include "Enemies.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <AssetManager.h>
#include <Globals.h>


class Infantry : public Enemies
{
public:
	//Infantry(b2World& MyWorld, const int Enum, const sf::Vector2f& vec, AssetManager*& manage);
	Infantry();
	virtual sf::Sprite& getSoldierSprite() = 0;
	virtual void SpawnSoldier(sf::RenderWindow& window)=0;
	virtual void CheckProximity(const sf::Vector2f& vec, sf::RenderWindow& window, sf::Clock& time, const bool sound) = 0;
	virtual  b2Body* GetSoldierBody()  = 0 ;
	virtual  b2Body* GetSoldierArm()  = 0;
	virtual void setDead(const bool k) = 0;
	virtual bool isDead() = 0;
	//void setSoldierSprite(sf::Sprite& sprite);
	//virtual sf::Sprite& getSoldierSprite()=0;
	~Infantry();

private:
	//sf::Sprite m_soldierSprite;
};
