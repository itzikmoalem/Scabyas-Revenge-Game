#pragma once
#include "Objects.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <stdlib.h>

class GiftBox : public Objects
{
public:
	GiftBox (b2World& MyWorld, const sf::Vector2f& vec, AssetManager*& manage,int& giftsNum,const bool box);
	GiftBox();
	void setGiftSprite(sf::Sprite& sprite);
	sf::Sprite& getGiftBoxSprite();
	void setCodeName(const char& c);
	char getCodeName();
	void AmmoGift(Player& player,HUD& stats);
	void ScoreGift(Player& player, HUD& stats);
	void HukusPukus();
	~GiftBox ();

private:
	sf::Sprite m_sprite;
	b2World& m_MyWorld;
	b2Body* m_body;
	char code;

};
