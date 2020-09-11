#include "Player.h"
#include <algorithm> 

Player::Player(b2World& MyWorld, b2Vec2 location) : m_MyWorld(MyWorld)
{
	CreateLegs(location);
	CreateBody();
	CreateHead();
	CreateArm();
	CreateJoint();

	m_pistol.setBuffer(manage->GetSound(S_PISTOL_SHOT));
	m_pistol.setVolume(10);
}

void Player::ChangeView(sf::RenderWindow& window, sf::View& view, sf::Sprite& screen)
{
	const float LeftBoundary = -20;
	const float RightBoundary = 1681;

	if (m_PlayerHead.getPosition().x > view.getCenter().x&& screen.getPosition().x < RightBoundary)
	{
		view.move(SPEED_PLAYER - 3, 0);
		screen.move(SPEED_PLAYER - 3, 0);
	}
	else if (m_Body->GetPosition().x <= view.getCenter().x && screen.getPosition().x > LeftBoundary)
	{
		view.move(-SPEED_PLAYER + 3, 0);
		screen.move(-SPEED_PLAYER + 3, 0);
	}
}

void Player::CreateJoint()
{
	b2RevoluteJointDef JointDef;

	//create the joint

	JointDef.bodyA = m_Legs;
	JointDef.bodyB = m_Body;

	JointDef.localAnchorA.Set(0, -((m_PlayerLegs.getGlobalBounds().height / 2) + 10) / SCALE);
	JointDef.localAnchorB.Set(0, 0);
	JointDef.referenceAngle = 0;

	JointDef.collideConnected = false;

	m_joint1 = (b2RevoluteJoint*)m_MyWorld.CreateJoint(&JointDef);

	JointDef.bodyB = m_Body;
	JointDef.bodyA = m_Head;

	JointDef.localAnchorA.Set(((m_PlayerBody.getGlobalBounds().width / 2) +5 ) / SCALE, ((m_PlayerBody.getGlobalBounds().height / 2) + 15) / SCALE);
	JointDef.localAnchorB.Set(0, 0);
	JointDef.referenceAngle = 0;

	JointDef.collideConnected = false;

	m_joint2 = (b2RevoluteJoint*)m_MyWorld.CreateJoint(&JointDef);
}

void Player::CreateBody()
{
	//Create the player's upperbody

	m_PlayerBody.setTexture(manage->GetTexture(O_BODY_R));
	m_PlayerBody.setPosition({ m_PlayerLegs.getPosition().x, m_PlayerLegs.getPosition().y });
	m_PlayerBody.setOrigin(manage->GetTexture(O_BODY_R).getSize().x / 2, manage->GetTexture(O_BODY_R).getSize().y / 2);
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_Legs->GetPosition().x, m_Legs->GetPosition().y);
	BodyDef.type = b2_dynamicBody;
	m_Body = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_PlayerBody.getGlobalBounds().width / 2) / SCALE, (m_PlayerBody.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = FRIENDLY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BOX | HOSTAGE | BULLET;
	FixtureDef.userData = (void*)90;

	m_Body->CreateFixture(&FixtureDef);

	m_Body->SetUserData((void*)82);
}

void Player::CreateHead()
{
	//Create the player's head
	m_PlayerHead.setTexture(manage->GetTexture(O_HEAD_R));
	m_PlayerHead.setPosition({ m_PlayerBody.getPosition().x, m_PlayerBody.getPosition().y });
	m_PlayerHead.setOrigin(manage->GetTexture(O_HEAD_R).getSize().x / 2, manage->GetTexture(O_HEAD_R).getSize().y / 2);
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_Body->GetPosition().x , m_Body->GetPosition().y);
	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	m_Head = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_PlayerHead.getGlobalBounds().width / 2) / SCALE, (m_PlayerHead.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = FRIENDLY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BOX | HOSTAGE | BULLET;
	FixtureDef.userData = (void*)90;

	m_Head->CreateFixture(&FixtureDef);

	m_Head->SetUserData((void*)81);
}

void Player::CreateArm()
{
	//Create the player's shooting Arm
	m_PlayerArm.setTexture(manage->GetTexture(O_ARM_PISTOL));
	m_PlayerArm.setPosition({ m_PlayerBody.getPosition().x, m_PlayerBody.getPosition().y });
	m_PlayerArm.setOrigin(m_PlayerArm.getOrigin().x, m_PlayerArm.getGlobalBounds().height / 2);
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(m_Body->GetPosition().x, m_Body->GetPosition().y);
	BodyDef.type = b2_dynamicBody;
	m_Arm = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_PlayerArm.getGlobalBounds().width / 2) / SCALE, (m_PlayerArm.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = FRIENDLY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BOX | HOSTAGE | BULLET;
	FixtureDef.userData = (void*)90;

	m_Arm->CreateFixture(&FixtureDef);

	m_Arm->SetUserData((void*)6);

}

void Player::CreateLegs(b2Vec2 location)
{
	//Create Legs

	m_MyWorld.SetContactListener(&manage->GetContactListener());

	m_PlayerLegs.setTexture(manage->GetTexture(O_LEGS_R1));
	m_PlayerLegs.setPosition(location.x, location.y);
	m_PlayerLegs.setOrigin(manage->GetTexture(O_LEGS_R1).getSize().x / 2, manage->GetTexture(O_LEGS_R1).getSize().y / 2);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(location.x / SCALE, location.y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	m_Legs = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((m_PlayerLegs.getGlobalBounds().width / 2) / SCALE, (m_PlayerLegs.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = FRIENDLY_SOLDIER;
	FixtureDef.filter.maskBits = BOUNDARY | PLATFORM | BOX | HOSTAGE | BULLET;
	FixtureDef.userData = (void*)90;

	m_Legs->CreateFixture(&FixtureDef);
	m_Legs->SetGravityScale(3);

	Shape.SetAsBox(0.7, 0.7);
	FixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_Legs->CreateFixture(&FixtureDef);
	footSensorFixture->SetUserData((void*)3);

	m_Legs->SetUserData((void*)8);
}

void Player::SpawnPlayer(sf::RenderWindow& window, sf::Clock &Timer, const bool SoundFX)
{
	b2Vec2 pos = m_Legs->GetWorldCenter();
	b2Vec2 vel = m_Legs->GetLinearVelocity();
	bool KeyPressed = false;

	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

	b2Vec2 MousePos = { worldPos.x / SCALE, worldPos.y / SCALE };
	m_target = MousePos;

	sf::Sprite Aim;
	Aim.setTexture(manage->GetTexture(O_AIM));
	Aim.scale(0.7, 0.7);
	Aim.setOrigin({ Aim.getGlobalBounds().width / 2,Aim.getGlobalBounds().height / 2 });
	Aim.setPosition(worldPos);

	window.draw(Aim);

	float bodyAngle = m_Body->GetAngle();
	b2Vec2 toTarget = MousePos - m_Body->GetPosition();
	float desiredAngle = atan2f(-toTarget.x, toTarget.y);

	float totalRotation = desiredAngle - bodyAngle;
	float change = 1 * 180 / b2_pi; //allow 1 degree rotation per time step
	float newAngle = bodyAngle + std::min(change, std::max(-change, totalRotation));

	m_Body->SetAngularVelocity(0);
	m_Body->SetTransform(m_Body->GetPosition(), newAngle);

	m_Arm->SetAngularVelocity(0);
	m_Arm->SetTransform(m_Arm->GetPosition(), newAngle + 19 * (180 / b2_pi));

	while (totalRotation < -180 * 180 / b2_pi) totalRotation += 360 * 180 / b2_pi;
	while (totalRotation > 180 * 180 / b2_pi) totalRotation -= 360 * 180 / b2_pi;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_stand = false;
		m_PlayerLegs.setTexture(manage->GetTexture(O_LEGS_R1));
		vel.x = 7;
		m_Legs->SetLinearVelocity(vel);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_stand = false;
		m_PlayerLegs.setTexture(manage->GetTexture(O_LEGS_L1));
		vel.x = -7;
		m_Legs->SetLinearVelocity(vel);
		KeyPressed = true;
	}
	else
	{
		m_PlayerLegs.setTexture(manage->GetTexture(O_LEGS_STAND));
		m_stand = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		KeyPressed = true;
		if (manage->GetContactListener().numFootContacts >= 1)
		{
			vel.y = -15;
			m_Legs->SetLinearVelocity(vel);
		}
		m_stand = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_PlayerLegs.setTexture(manage->GetTexture(O_BODY_JUMP_RIGHT));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_PlayerLegs.setTexture(manage->GetTexture(O_BODY_JUMP_LEFT));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_stand = false;
		KeyPressed = true;
		vel.y = 10;
		m_Legs->SetLinearVelocity(vel);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		KeyPressed = true;
		if (manage->GetContactListener().numFootContacts >= 1)
		{
			vel.y = -20;
			m_Legs->SetLinearVelocity(vel);
		}
		m_stand = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_PlayerLegs.setTexture(manage->GetTexture(O_BODY_JUMP_RIGHT));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_PlayerLegs.setTexture(manage->GetTexture(O_BODY_JUMP_LEFT));
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (Timer.getElapsedTime().asSeconds() >= 0.5)
		{
			Timer.restart().asSeconds();
			Bullet NewBullet;
			NewBullet.CreateBullets(m_MyWorld, m_Body->GetPosition(), m_target,true, 0.5);

			if (SoundFX)
				m_pistol.play();

			m_Bullets.push_back(&NewBullet);
		}
	}

	if (manage->GetContactListener().numFootContacts >= 1 && !KeyPressed)
	{
		m_Legs->SetLinearVelocity({ 0,0 });

	}




	for (b2Body* BodyIterator = m_MyWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if ((int)BodyIterator->GetUserData() == 8)	//Legs Player
		{
			m_PlayerLegs.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			
		}

		if ((int)BodyIterator->GetUserData() == 81)	//Head Player
		{

			m_PlayerHead.setPosition(SCALE* BodyIterator->GetPosition().x, SCALE* BodyIterator->GetPosition().y);
			m_PlayerHead.setRotation(m_Body->GetAngle() * (180 / b2_pi));


			if (m_PlayerHead.getRotation() >= 0 && m_PlayerHead.getRotation() < 180)
			{
				m_PlayerHead.setPosition(SCALE * BodyIterator->GetPosition().x + 25, SCALE * BodyIterator->GetPosition().y - 10);

				m_PlayerHead.setTexture(manage->GetTexture(O_HEAD_L));
			}
			else if (m_PlayerHead.getRotation() >= 180 && m_PlayerHead.getRotation() < 360)
			{
				m_PlayerHead.setPosition(SCALE * BodyIterator->GetPosition().x + 12 , SCALE * BodyIterator->GetPosition().y - 10);

				m_PlayerHead.setTexture(manage->GetTexture(O_HEAD_R));
			}

			m_PlayerHead.setRotation(0);
			
		}

		if ((int)BodyIterator->GetUserData() == 82)	//Body Player
		{
			m_PlayerBody.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			m_PlayerBody.setRotation(m_Body->GetAngle() * 180 / b2_pi);

			Arm_Angle = m_PlayerBody.getRotation();
			if (m_PlayerBody.getRotation() >= 0 && m_PlayerBody.getRotation() < 180)
			{
				m_PlayerBody.setTexture(manage->GetTexture(O_BODY_L));
				m_PlayerBody.setOrigin(manage->GetTexture(O_BODY_L).getSize().x / 2, manage->GetTexture(O_BODY_L).getSize().y / 2);
			}
			else if (m_PlayerBody.getRotation() >= 180 && m_PlayerBody.getRotation() < 360)
			{
				m_PlayerBody.setTexture(manage->GetTexture(O_BODY_R));
				m_PlayerBody.setOrigin(manage->GetTexture(O_BODY_R).getSize().x / 2, manage->GetTexture(O_BODY_R).getSize().y / 2);
			}

			m_PlayerBody.setRotation(0);
		}

		if ((int)BodyIterator->GetUserData() == 6)
		{


			m_PlayerArm.setPosition(m_PlayerBody.getPosition().x, m_PlayerBody.getPosition().y);
			m_PlayerArm.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);

			if (Arm_Angle >= 0 && Arm_Angle < 180)
			{
				m_PlayerArm.setScale(1, -1);

			}
			if (Arm_Angle >= 180 && Arm_Angle < 360)
			{
				m_PlayerArm.setScale(1, 1);
			}

		}

		if ((int)BodyIterator->GetUserData() == 25)
		{
			sf::Sprite Bullet;
			Bullet.setTexture(manage->GetTexture(O_BULLET));
			if ((int)BodyIterator->GetFixtureList()->GetUserData() == 67)
			{
				Bullet.setColor(sf::Color::Red);
				Bullet.scale(1.2, 1.2);
			}

			Bullet.scale(0.25, 0.25);

			Bullet.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);



			window.draw(Bullet);	
		}

		if ((int)BodyIterator->GetUserData() == 645)
		{

			BulletsScheduledForRemoval.insert(BodyIterator);

		}

		window.draw(m_PlayerLegs);
		window.draw(m_PlayerHead);
		window.draw(m_PlayerBody);
		window.draw(m_PlayerArm);
	}

	std::set<b2Body*>::iterator it = BulletsScheduledForRemoval.begin();
	std::set<b2Body*>::iterator end = BulletsScheduledForRemoval.end();

	for (; it != end; ++it)
	{
		b2Body* dyingbullet = *it;

		//physics body is destroyed here
		dyingbullet->GetWorld()->DestroyBody(dyingbullet);

	}

	//clear this list for next time
	BulletsScheduledForRemoval.clear();

}

bool Player::isStand()
{
	return m_stand;
}

sf::Sprite& Player::getPlayerBodySprite()
{
	return m_PlayerBody;
}

sf::Sprite& Player::getPlayerLegsSprite()
{
	return m_PlayerLegs;
}

sf::Sprite& Player::getPlayerArmSprite()
{
	return m_PlayerArm;
}

sf::Sprite& Player::getPlayerHeadSprite()
{
	return m_PlayerHead;
}


Player::~Player()
{
}
