#include "MyContactListener.h"



void MyContactListener::BeginContact(b2Contact* contact)
{
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureUserData2 = contact->GetFixtureB()->GetUserData();
	
	//Get the fixtures that collided.
	b2Fixture *f1 = contact->GetFixtureA();
	b2Fixture* f2 = contact->GetFixtureB();

	b2Body* b1 = f1->GetBody();
	b2Body* b2 = f2->GetBody();


	//check if fixture A was the foot sensor
	if ((int)fixtureUserData == 3 && (((int)fixtureUserData2 == 1 ) || ((int)fixtureUserData2 == 123)))
		numFootContacts++;
	//check if fixture B was the foot sensor
	if ((int)fixtureUserData2 == 3 && (((int)fixtureUserData == 1) || ((int)fixtureUserData == 123)))
		numFootContacts++;

	//check if fixture A was the bullet and B was the helicopter
	if ((int)fixtureUserData == 66 && (int)fixtureUserData2 == 69)
		BulletHitHeli = true;
	//check if fixture B was the bullet and A was the helicopter
	if ((int)fixtureUserData2 == 66 && (int)fixtureUserData == 69 )
		BulletHitHeli = true;

	//check if fixture A was the bullet and B was the enemy soldier
	if ((int)fixtureUserData == 66 && (int)fixtureUserData2 == 88)
	{
		f2->SetUserData((void*)87);
		BulletHitSoldier = true;
	}
	//check if fixture B was the bullet and A was the enemy soldier
	if ((int)fixtureUserData2 == 66 && (int)fixtureUserData == 88)
	{
		f1->SetUserData((void*)87);
		BulletHitSoldier = true;

	}

	//check if fixture A was the  enemy bullet and B was the friendly soldier
	if ((int)fixtureUserData == 67 && (int)fixtureUserData2 == 90)
	{
		EnemyBulletHitHero = true;
	}
	//check if fixture A was the  enemy bullet and A was the friendly soldier
	if ((int)fixtureUserData2 == 67 && (int)fixtureUserData == 90)
	{
		EnemyBulletHitHero = true;
	}

		//Check if the bullet collided with anything in order to clear the body from the world after the timestep
	if ((int)fixtureUserData == 66 || (int)fixtureUserData2 == 66 )
	{
		if ((int)fixtureUserData == 66)
			contact->GetFixtureA()->GetBody()->SetUserData((void*)645);
		else
			contact->GetFixtureB()->GetBody()->SetUserData((void*)645);
	}

	if ((int)fixtureUserData == 67 || (int)fixtureUserData2 == 67)
	{
		if ((int)fixtureUserData == 67)
			contact->GetFixtureA()->GetBody()->SetUserData((void*)645);
		else
			contact->GetFixtureB()->GetBody()->SetUserData((void*)645);
	}


	



}

void MyContactListener::EndContact(b2Contact* contact)
{

	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	void* fixtureUserData2 = contact->GetFixtureB()->GetUserData();

	//check if fixture A was the foot sensor
	if ((int)fixtureUserData == 3 && (((int)fixtureUserData2 == 1) || ((int)fixtureUserData2 == 123)))
		numFootContacts--;
	//check if fixture B was the foot sensor
	if ((int)fixtureUserData2 == 3 && (((int)fixtureUserData == 1) || ((int)fixtureUserData == 123)))
		numFootContacts--;

}
