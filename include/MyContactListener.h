#pragma once
#include <box2d/box2d.h>

class MyContactListener : public b2ContactListener
{

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

public:
    int numFootContacts;
    bool BulletHitHeli;
    bool BulletHitSoldier;
	bool EnemyBulletHitHero;
};