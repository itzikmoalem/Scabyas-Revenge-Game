#include "StandardHeli.h"


StandardHeli::StandardHeli() : m_MyWorld(m_MyWorld)
{
}

StandardHeli::StandardHeli(b2World& MyWorld, b2Vec2 location, AssetManager*& manage) : m_MyWorld(MyWorld)
{
	sf::Sprite tempBody;
	b2Body* tempb2Body;

	tempBody.setTexture(manage->GetTexture(O_STANDARD_HELI_BODY_R));
	tempBody.setPosition(200, 200);
	tempBody.setOrigin(manage->GetTexture(O_STANDARD_HELI_BODY_R).getSize().x / 2, manage->GetTexture(O_STANDARD_HELI_BODY_R).getSize().y / 2);
	tempBody.setRotation(20);
	tempBody.setScale(1.5, 1.5);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(0 / SCALE, 200 / SCALE);

	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	tempb2Body = MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((tempBody.getGlobalBounds().width / 2) / SCALE, (tempBody.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;
	FixtureDef.filter.categoryBits = ENEMY_HELI;
	FixtureDef.userData = (void*)69;

	tempb2Body->CreateFixture(&FixtureDef);
	tempb2Body->SetGravityScale(0);
	tempb2Body->SetUserData((void*)9);

	FixtureDef.isSensor = true;

	SetHeliBody(tempBody);
	Setb2Body(tempb2Body);

	m_MyWorld = MyWorld;

	//CreatePropeller();
	CreateGun();
	//CreateJoint();
}

void StandardHeli::Shooter(sf::RenderWindow& window, sf::Clock& time, sf::Vector2f& pos)
{
	b2Vec2 PlayerPos = { pos.x / SCALE, pos.y / SCALE };
	if (time.getElapsedTime().asSeconds() >= 1.5)
	{
		time.restart().asSeconds();
		Bullet NewBullet;
		NewBullet.CreateBullets(m_MyWorld, this->getb2Body()->GetPosition(), PlayerPos, false, 0.1);
	}

}

void StandardHeli::CreatePropeller()
{
	sf::Sprite tempPropeller;

	tempPropeller.setTexture(manage->GetTexture(O_PROPELLER1));
	tempPropeller.setPosition(GetHeliBody().getPosition().x, GetHeliBody().getPosition().y + 50);
	tempPropeller.setRotation(20);
	tempPropeller.setOrigin(manage->GetTexture(O_PROPELLER1).getSize().x / 2, manage->GetTexture(O_PROPELLER1).getSize().y / 2);

	SetHeliPropeller(tempPropeller);
}

void StandardHeli::CreateGun()
{
	sf::Sprite tempGun;
	b2Body* tempb2Gun;

	tempGun.setTexture(manage->GetTexture(O_STANDARD_HELI_GUN));
	tempGun.setPosition(GetHeliBody().getPosition().x - 50, GetHeliBody().getPosition().y);
	tempGun.setOrigin(manage->GetTexture(O_STANDARD_HELI_GUN).getSize().x / 2, manage->GetTexture(O_STANDARD_HELI_GUN).getSize().y / 2);
	tempGun.setRotation(80);
	tempGun.scale(1.5, 1.5);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(0 / SCALE, 200 / SCALE);

	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	tempb2Gun = m_MyWorld.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((tempGun.getGlobalBounds().width / 2) / SCALE, (tempGun.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.5;
	FixtureDef.shape = &Shape;

	tempb2Gun->CreateFixture(&FixtureDef);
	tempb2Gun->SetGravityScale(0);
	tempb2Gun->SetUserData((void*)29);

	FixtureDef.isSensor = true;

	SetHeliGun(tempGun);
	Setb2Gun(tempb2Gun);
}

void StandardHeli::CreateJoint()
{
	b2RevoluteJointDef JointDef;
	b2RevoluteJoint* joint;

	//create the joint

	JointDef.bodyA = getb2Body();
	JointDef.bodyB = getb2Gun();

	JointDef.localAnchorA.Set(0, -((GetHeliBody().getGlobalBounds().height / 2) + 10) / SCALE);
	JointDef.localAnchorB.Set(0, 0);
	JointDef.referenceAngle = 0;

	JointDef.enableLimit = true;
	JointDef.lowerAngle = 0;
	JointDef.upperAngle = 0;

	JointDef.collideConnected = false;

	joint = (b2RevoluteJoint*)m_MyWorld.CreateJoint(&JointDef);

	SetJoint(joint);
}

bool StandardHeli::getStatus()
{
	return m_Killed;
}

void StandardHeli::SpawnHeli(sf::RenderWindow& window)
{
	for (b2Body* BodyIterator = m_MyWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if ((int)BodyIterator->GetUserData() == 9) //Heli Body
		{
			SetPositionBodyHelper(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			window.draw(GetHeliBody());
		}

		window.draw(GetHeliGun());
		//window.draw(GetHeliPropeller());
	}
}

void StandardHeli::movingHeli(const int time)
{
	b2Vec2 vel = getb2Body()->GetLinearVelocity();

	sf::Sprite temp = GetHeliBody();
	sf::Sprite tempPropeller = GetHeliPropeller();

	if (temp.getPosition().x >= R_SCREEN)
	{
		speed = -SPEED_BOMB_HELI;
		temp.setTexture(manage->GetTexture(O_STANDARD_HELI_BODY_L));
		temp.setRotation(-20);
		tempPropeller.setRotation(-20);
		PosGun_X = -20;

		PosPropeller_X = -27;

	}
	if (temp.getPosition().x <= L_SCREEN)
	{
		speed = SPEED_BOMB_HELI;
		temp.setTexture(manage->GetTexture(O_STANDARD_HELI_BODY_R));
		temp.setRotation(20);
		tempPropeller.setRotation(20);
		PosGun_X = 30;

		PosPropeller_X = 27;
	}

	vel.x = speed;

	SetPositionGunHelper(temp.getPosition().x + PosGun_X, temp.getPosition().y + 60);
	//SetGunRotaion();

	if (time % 2 == 0)
		tempPropeller.setTexture(manage->GetTexture(O_PROPELLER1));
	else
		tempPropeller.setTexture(manage->GetTexture(O_PROPELLER2));

	tempPropeller.setPosition(GetHeliBody().getPosition().x + PosPropeller_X, GetHeliBody().getPosition().y - 35);

	SetHeliPropeller(tempPropeller);

	SetHeliBody(temp);
	SetLinearHelper(vel);
}

void StandardHeli::SetGunRotaion()
{
	for (b2Body* BodyIterator = m_MyWorld.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if ((int)BodyIterator->GetUserData() == 8)	//Legs Player
		{
			//b2Vec2 PlayerPos = BodyIterator->GetPosition();
			float PlayerPos_x = BodyIterator->GetPosition().x;
			float HeliPos_x = GetHeliGun().getPosition().x;
			float Distance = HeliPos_x - PlayerPos_x;

			if (HeliPos_x > PlayerPos_x)
			{
				MakeRotation((Distance / 11));
			}
			else if (HeliPos_x < PlayerPos_x)
			{
				MakeRotation((Distance / 1.5));
			}
		}
	}
	//if (GetHeliGun().getPosition().x > )
}

StandardHeli::~StandardHeli()
{
}
