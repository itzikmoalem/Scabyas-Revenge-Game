#include "GiftBox.h"

GiftBox::GiftBox(b2World& MyWorld,const sf::Vector2f& vec, AssetManager*& manage,int& giftsNum,const bool box) : m_MyWorld(MyWorld)
{
	sf::Sprite giftSprite;

	if (box)
	{
		giftSprite.setTexture(manage->GetTexture(O_box));
		giftSprite.setPosition(vec.x, vec.y);
		giftSprite.setOrigin(manage->GetTexture(O_box).getSize().x / 2, manage->GetTexture(O_box).getSize().y / 2);
		setCodeName('b'); // just box
	}
	else
	{
		if (giftsNum % 2 == 0) // ammo box case
		{
			giftSprite.setTexture(manage->GetTexture(O_AMMO_GIFT));
			giftSprite.setPosition(vec.x, vec.y);
			giftSprite.setOrigin(manage->GetTexture(O_AMMO_GIFT).getSize().x / 2, manage->GetTexture(O_AMMO_GIFT).getSize().y / 2);
			setCodeName('a'); // ammo
		}
		else//if  (giftsNum % 3 == 0)
		{
			giftSprite.setTexture(manage->GetTexture(O_WEAPON_GIFT));
			giftSprite.setPosition(vec.x, vec.y);
			giftSprite.setOrigin(manage->GetTexture(O_WEAPON_GIFT).getSize().x / 2, manage->GetTexture(O_WEAPON_GIFT).getSize().y / 2);
			setCodeName('g'); // gun
		}
		//else if (giftsNum % 2 != 0)
		//{
		//	giftSprite.setTexture(manage->GetTexture(O_box));
		//	giftSprite.setPosition(vec.x, vec.y);
		//	giftSprite.setOrigin(manage->GetTexture(O_box).getSize().x / 2, manage->GetTexture(O_box).getSize().y / 2);
		//	setCodeName('s'); // score
		//}
	}

	setGiftSprite(giftSprite);

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(vec.x / SCALE, vec.y / SCALE);
	BodyDef.type = b2_dynamicBody;
	m_body = m_MyWorld.CreateBody(&BodyDef);
	

	b2PolygonShape Shape;
	Shape.SetAsBox((giftSprite.getGlobalBounds().width / 2) / SCALE, (giftSprite.getGlobalBounds().height / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.filter.categoryBits = BOX;
	FixtureDef.userData = (void*)123;
	FixtureDef.shape = &Shape;

	m_body->CreateFixture(&FixtureDef);

	if (getCodeName() == 'a')
		m_body->SetUserData((void*)(400 + giftsNum));
	if (getCodeName() == 's')
		m_body->SetUserData((void*)(420 + giftsNum));
	if (getCodeName() == 'g')
		m_body->SetUserData((void*)(440 + giftsNum));
	if (getCodeName() == 'b')
		m_body->SetUserData((void*)(460 + giftsNum));

}

GiftBox::GiftBox() : m_MyWorld(m_MyWorld)
{

}

void GiftBox::setGiftSprite(sf::Sprite& sprite)
{
	m_sprite = sprite;
}
sf::Sprite& GiftBox::getGiftBoxSprite()
{
	return m_sprite;
}

void GiftBox::setCodeName(const char& c)
{
	code = c;
}

char GiftBox::getCodeName()
{
	return code;
}

void GiftBox::AmmoGift(Player& player,HUD& stats)
{
	if (stats.getGunName() == "Pistol")
		stats.setAmmo(15);

}

void GiftBox::ScoreGift(Player& player, HUD& stats)
{
	stats.setScore(50);
}



void GiftBox::HukusPukus()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

GiftBox::~GiftBox()
{
}
