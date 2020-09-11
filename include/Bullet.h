#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Bullet 
{
public:
	Bullet();
	void CreateBullets(b2World& MyWorld, b2Vec2, b2Vec2 target, const bool& mask, float force);
	void RemoveBody();
	~Bullet();

private:
	b2Body* m_Bullets;
};
