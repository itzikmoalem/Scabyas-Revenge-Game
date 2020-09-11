#pragma once
#include "Objects.h"
#include <AssetManager.h>
#include <Globals.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <statehelpers.h>


class Hostage : public Objects
{
public:
	//Hostage();

	Hostage(b2World& MyWorld, const sf::Vector2f& vec, AssetManager*& manage,const int host);
	void setHostageSprite(sf::Sprite& sprite);
	sf::Sprite& getHostageSprite();
	void hukusPukus();
	void setHostageBody(b2Body*& body);
	void SpawnHostage(sf::RenderWindow& window);
	void SetTextureRandomally(AssetManager*& manage);

	b2Body* &getHostageBody();

	~Hostage();

private:

	b2World& m_MyWorld;
	sf::Sprite m_sprite;
	b2Body* m_body;
	int m_HostageNum = 1;
};
