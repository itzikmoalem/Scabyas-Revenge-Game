#include "RPGSoldier.h"

void RPGSoldier::SpawnSoldier(sf::RenderWindow& window)
{
		window.draw(m_ArmSprite);
		window.draw(m_soldierSprite);

	m_Range.setPosition(m_soldierSprite.getPosition());
	window.draw(m_Range);
}

sf::Sprite& RPGSoldier::getSoldierSprite()
{
	return m_soldierSprite;
}

void RPGSoldier::CreateArm(AssetManager*& manage)
{
	m_ArmSprite.setTexture(manage->GetTexture(O_ENEMY_RPG_R));
	m_ArmSprite.setPosition(m_soldierSprite.getPosition().x + 15, m_soldierSprite.getPosition().y + 30);
	m_ArmSprite.setOrigin(manage->GetTexture(O_ENEMY_RPG_R).getSize().x / 2, manage->GetTexture(O_ENEMY_RPG_R).getSize().y / 2);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_soldierSprite.getPosition().x / SCALE, m_soldierSprite.getPosition().y / SCALE);
	BodyDef.type = b2_dynamicBody;

	m_arm = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_soldierSprite.getGlobalBounds().width / 2) / SCALE, (m_soldierSprite.getGlobalBounds().height / 2) / SCALE);;

	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = ENEMY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BULLET;
	FixtureDef.userData = (void*)88;

	m_arm->CreateFixture(&FixtureDef);

	m_arm->SetUserData((void*)641);
}

RPGSoldier::RPGSoldier(b2World& MyWorld,const sf::Vector2f& vec) : m_MyWorld(MyWorld)
{
	this->SetHp(150);
	m_soldierSprite.setTexture(manage->GetTexture(O_ENEMY_BODY2_R));
	m_soldierSprite.setPosition(vec);
	m_soldierSprite.setOrigin(manage->GetTexture(O_ENEMY_BODY2_R).getSize().x / 2, manage->GetTexture(O_ENEMY_BODY2_R).getSize().y / 1.5);
	//m_soldierSprite.scale(-1, 1);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(vec.x / SCALE, vec.y / SCALE);
	BodyDef.fixedRotation = true;
	BodyDef.type = b2_dynamicBody;

	m_body = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_soldierSprite.getGlobalBounds().width / 2) / SCALE, (m_soldierSprite.getGlobalBounds().height / 2) / SCALE);
	

	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = ENEMY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BULLET;
	FixtureDef.userData = (void*)88;

	m_body->CreateFixture(&FixtureDef);

	m_body->SetUserData((void*)620);

	//Create Range
	m_Range.setRadius(RPG_RANGE);
	m_Range.setOutlineColor(sf::Color::Green);
	m_Range.setFillColor(sf::Color::Transparent);
	//m_Range.setOrigin(m_Range.getRadius(),m_Range.getRadius());
	m_Range.setOrigin(m_Range.getRadius(), m_Range.getRadius());

	m_Range.setPosition(m_soldierSprite.getPosition());
	m_Range.setOutlineThickness(1);

	CreateArm(manage);
	MakeJoint();
}

void RPGSoldier::CheckProximity(const sf::Vector2f& vec, sf::RenderWindow& window, sf::Clock& time, const bool sound)
{
	b2Vec2 PlayerPos = { vec.x / SCALE ,vec.y / SCALE };// / SCALE, vec.y / SCALE

	if (m_soldierSprite.getPosition().x > vec.x)
	{
		m_ArmSprite.setPosition(m_soldierSprite.getPosition().x - 30, m_soldierSprite.getPosition().y -1);
		m_ArmSprite.setTexture(manage->GetTexture(O_ENEMY_AK_L));
		m_soldierSprite.setTexture(manage->GetTexture(O_ENEMY_BODY1_L));
		//m_ArmSprite.setRotation((m_arm->GetAngle() * -180) / b2_pi);

		window.draw(m_ArmSprite);
	}
	else
	{
		m_ArmSprite.setPosition(m_soldierSprite.getPosition().x + 30, m_soldierSprite.getPosition().y -1);
		m_ArmSprite.setTexture(manage->GetTexture(O_ENEMY_AK_R));
		m_soldierSprite.setTexture(manage->GetTexture(O_ENEMY_BODY1_R));
		//m_ArmSprite.setRotation(m_arm->GetAngle() * 180 / b2_pi);

		window.draw(m_ArmSprite);
	}

	if (m_Range.getGlobalBounds().contains(vec))
	{
		if (time.getElapsedTime().asSeconds() >= 0.7)
		{
			time.restart().asSeconds();
			Bullet NewBullet;
			NewBullet.CreateBullets(m_MyWorld, m_arm->GetPosition(), PlayerPos, false, 1);
		}

		float bodyAngle = m_arm->GetAngle();
		b2Vec2 toTarget = PlayerPos - m_body->GetPosition();

		float desiredAngle = atan2f(-toTarget.x, toTarget.y);

		float totalRotation = desiredAngle - bodyAngle;
		float change = 1 * 180 / b2_pi; //allow 1 degree rotation per time step
		float newAngle = bodyAngle + std::min(change, std::max(-change, totalRotation));
		m_arm->SetAngularVelocity(0);
		m_arm->SetTransform(m_arm->GetPosition(), newAngle);

		while (totalRotation < -180 * 360 / b2_pi) totalRotation += 360 * 180 / b2_pi;
		while (totalRotation > 180 * 360 / b2_pi) totalRotation -= 360 * 180 / b2_pi;
	}
	else
	{
		m_ArmSprite.setRotation(0);
	}

}

 b2Body* RPGSoldier::GetSoldierBody() 
{
	return m_body;
}
 bool RPGSoldier::isDead()
 {
	 return m_dead;
 }
 void RPGSoldier::setDead(const bool k)
 {
	 m_dead = k;
 }

 b2Body* RPGSoldier::GetSoldierArm() 
 {
	 return m_arm;
 }

void RPGSoldier::MakeJoint()
{
	b2RevoluteJointDef JointDef;
	b2RevoluteJoint* joint;

	//create the joint

	JointDef.bodyA = m_body;
	JointDef.bodyB = m_arm;

	JointDef.localAnchorA.Set(-(m_soldierSprite.getGlobalBounds().width / 2 - 50) / SCALE, ((m_soldierSprite.getGlobalBounds().height / 2 - 50)) / SCALE);
	JointDef.localAnchorB.Set(0, 0);
	JointDef.referenceAngle = 0;

	JointDef.enableLimit = true;
	JointDef.lowerAngle = 0;
	JointDef.upperAngle = 0;

	JointDef.collideConnected = true;

	joint = (b2RevoluteJoint*)m_MyWorld.CreateJoint(&JointDef);
	m_joint = joint;
}
