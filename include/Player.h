#pragma once

#include <AssetManager.h>
#include <Globals.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <MyContactListener.h>
#include <HUD.h>
#include <Bullet.h>
#include <set>
#include <Objects.h>


class Player : public Objects
{
public:
	Player(b2World& MyWorld, b2Vec2);
	void ChangeView(sf::RenderWindow& window, sf::View& view, sf::Sprite& screen);
	void SpawnPlayer(sf::RenderWindow &window, sf::Clock &Timer,const bool SoundFX);
	void CreateJoint();
	void CreateBody();
	void CreateHead();
	void CreateArm();
	void CreateLegs(b2Vec2 location);

	bool isStand();
	sf::Sprite& getPlayerBodySprite();
	sf::Sprite& getPlayerLegsSprite();
	sf::Sprite& getPlayerArmSprite();
	sf::Sprite& getPlayerHeadSprite();

	~Player();

private:

	b2Body* m_Body;
	b2Body* m_Arm;
	b2Body* m_Legs;
	b2Body* m_Head;
	b2RevoluteJoint* m_joint1;
	b2RevoluteJoint* m_joint2;
	AssetManager* manage = manage->getInstance();
	b2World& m_MyWorld;
	sf::Sprite m_PlayerLegs;
	sf::Sprite m_PlayerHead;
	sf::Sprite m_PlayerBody;
	sf::Sprite m_PlayerArm;
	int m_gunIndex;
	float Arm_Angle;
	b2Vec2 m_target;
	std::vector<Bullet*> m_Bullets;
	std::set<b2Body*> BulletsScheduledForRemoval;
	bool m_stand = true;

	sf::Sound m_pistol;
};
