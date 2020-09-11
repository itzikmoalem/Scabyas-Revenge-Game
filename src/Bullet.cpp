#include "Bullet.h"
#include <Globals.h>

Bullet::Bullet()
{

}

void Bullet::CreateBullets(b2World& MyWorld, b2Vec2 pos, b2Vec2 target,const bool& mask, float force)
{
	//Create the Bullets

	b2BodyDef BodyDef;
	BodyDef.position = pos;
	BodyDef.type = b2_dynamicBody;
	BodyDef.bullet = true;
	m_Bullets = MyWorld.CreateBody(&BodyDef);

	b2CircleShape Shape;
	Shape.m_radius = 3 * (b2_pi / 180);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1;

	FixtureDef.filter.categoryBits = BULLET;
	if (mask)
	{
		FixtureDef.filter.maskBits = BOUNDARY | ENEMY_HELI | ENEMY_SOLDIER | PLATFORM;
		FixtureDef.userData = (void*)66;
	}
	else
	{
		FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | FRIENDLY_SOLDIER;
		FixtureDef.userData = (void*)67;
	}
	FixtureDef.shape = &Shape;

	m_Bullets->CreateFixture(&FixtureDef);

	m_Bullets->SetUserData((void*)25);

	auto hyp = target - m_Bullets->GetPosition();
	hyp.Normalize();
	m_Bullets->ApplyLinearImpulse(b2Vec2(force * hyp.x, force * hyp.y), m_Bullets->GetWorldCenter(), true);

}

void Bullet::RemoveBody()
{


}

Bullet::~Bullet()
{
	
}
