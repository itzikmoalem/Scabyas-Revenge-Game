#include "Board.h"
#include <experimental/vector>

Board::Board()
{
}

void Board::CreateLimits()
{
	// add 3 walls to the game
	CreateBody({ 0,0 }, 5, 2000); // left wall
	CreateBody({ 3550,0 }, 5, 2000); // right wall
	CreateBody({ 0,-400 }, 8000, 5); // ceiling
}

void Board::CreateBody(b2Vec2 pos, float SizeX, float SizeY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(pos.x / SCALE, pos.y / SCALE);
	BodyDef.type = b2_staticBody;

	b2PolygonShape Shape;
	Shape.SetAsBox((SizeX / 2) / SCALE, (SizeY / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;

	b2Fixture* fixture = m_World->CreateBody(&BodyDef)->CreateFixture(&FixtureDef);
	fixture->SetUserData((void*)99);

}

void Board::ReadLevel(sf::RenderWindow& window)
{

	std::ifstream& file = manage->GetLevels();

	/** Prepare the world */
	b2Vec2 Gravity(0.f, 9.8f);

	m_World = std::make_unique<b2World>(Gravity);

	//b2World World(Gravity)
	//CreateGround(400.f, 1000.f);


	while (!file.eof())
	{
		int c;

		file >> c;
		m_NumOfHelis = c;

		file >> c;
		m_NumOfHostages = c;

		char k;
		// Intilazie number of each heli
		for (int i = 0; i < m_NumOfHelis; i++)
		{
			file >> k;
			if (k == 's')
			{
				setNumOfStandradHeli(1);
				m_helisChar.push_back(k);
				
			}

			else if (k == 'b')
			{
				m_helisChar.push_back(k);
				setNumOfBombHeli(1);
			}
			else
			{
				m_helisChar.push_back(k);
				setNumOfRocketHeli(1);
			}

		}

		sf::Vector2f boardLocation(0.f, 1025.f);

		int hostage_num = 0;
		int gifts_num = 0;
		bool regularbox = false;
		std::string line;
		while (std::getline(file, line))
		{
			for (auto c : line)
			{
				Char_t ch = Char_t(c);
				switch (ch)
				{
				case C_EMPTY:
				{
					boardLocation.x = boardLocation.x + 50;
					break;

				}
				case C_HOSTAGE:
				{
					Hostage hostage(*m_World, boardLocation, manage, hostage_num);
					m_Hostages.push_back(std::make_unique <Hostage>(hostage));
					boardLocation.x = boardLocation.x + 50;
					hostage_num++;
					break;
				}
				case C_SOLDIER:
				{
					std::cout << boardLocation.y << std::endl;
					AKSoldier Soldier(*m_World, boardLocation, m_NumOfSoldiers);
					m_Soldiers.push_back(std::make_unique<AKSoldier>(Soldier));
					boardLocation.x = boardLocation.x + 50;
					m_NumOfSoldiers++;
					break;
				}

				case C_MIDDLE2:
				{
					make_Brick(O_MIDDLE2, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_MIDDLE3:
				{
					make_Brick(O_MIDDLE3, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TOPRIGHT2:
				{
					make_Brick(O_TOPRIGHT2, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TOPLEFT:
				{
					make_Brick(O_TOPLEFT, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;

				}
				case C_MIDDLE:
				{
					make_Brick(O_MIDDLE, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TOPRIGHT:
				{
					make_Brick(O_TOPRIGHT, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TOPLEFT2:
				{
					make_Brick(O_TOPLEFT2, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TOPMIDDLE:
				{
					make_Brick(O_TOPMIDDLE, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TREETOP:
				{
					make_Brick(O_TREETOP, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_TREE:
				{
					make_Brick(O_TREE, boardLocation);
					boardLocation.x = boardLocation.x + 50;
					break;
				}
				case C_GIFTBOX:
				{
					regularbox = false;
					GiftBox gift(*m_World, boardLocation, manage,gifts_num,regularbox);
					m_Gifts.push_back(std::make_unique<GiftBox>(gift));
					boardLocation.x = boardLocation.x + 50;
					gifts_num++;
					break;
				}
				case C_JUSTBOX:
				{
					regularbox = true;
					GiftBox gift(*m_World, boardLocation, manage, gifts_num, regularbox);
					m_Gifts.push_back(std::make_unique<GiftBox>(gift));
					boardLocation.x = boardLocation.x + 50;
					gifts_num++;
					break;
				}
				default:
					break;
				}
			}
			boardLocation.y -= 50;
			boardLocation.x = 0;
		}
	}
}

void Board::UpdateStats(HUD& stats)
{
	if (manage->GetContactListener().BulletHitHeli)
	{
		m_Helis[m_CurrentHeli]->DecreaseHP();
		manage->GetContactListener().BulletHitHeli = false;

	}

	if (manage->GetContactListener().BulletHitSoldier)
	{
		for (int i = 0; i < m_Soldiers.size(); i++)
		{
			if ((int)m_Soldiers[i]->GetSoldierBody()->GetFixtureList()->GetUserData() == 87 || (int)m_Soldiers[i]->GetSoldierArm()->GetFixtureList()->GetUserData() == 87)
			{
				m_Soldiers[i]->DecreaseHP();
				m_Soldiers[i]->GetSoldierBody()->GetFixtureList()->SetUserData((void*)88);
				m_Soldiers[i]->GetSoldierArm()->GetFixtureList()->SetUserData((void*)88);

			}
			if (m_Soldiers[i]->GetHp() <= 0)
			{
				m_Soldiers[i]->setDead(true);

				m_Soldiers[i]->GetSoldierBody()->GetWorld()->DestroyBody(m_Soldiers[i]->GetSoldierBody());
				m_Soldiers[i]->GetSoldierArm()->GetWorld()->DestroyBody(m_Soldiers[i]->GetSoldierArm());
			}

			std::experimental::erase_if(m_Soldiers, [](auto& soldier)
				{
					return soldier->isDead();

				});

		}

		manage->GetContactListener().BulletHitHeli = false;
	}
	if (manage->GetContactListener().EnemyBulletHitHero)
	{
		stats.decreaseHP(5);
		std::cout << stats.GetPlayerHP() << std::endl;



		manage->GetContactListener().EnemyBulletHitHero = false;
	}

	if (m_Helis[m_CurrentHeli]->GetHp() <= 0)
	{
		m_Helis[m_CurrentHeli]->getb2Body()->GetWorld()->DestroyBody(m_Helis[m_CurrentHeli]->getb2Body());
		m_Helis[m_CurrentHeli].reset();
		stats.IncrementHelisSpawned();
		m_heli_spawned = false;
	}


}

void Board::setBoxCode(const char& l)
{
	box_code = l;
}

char Board::getBoxCode()
{
	return box_code;
}

//Make platfrom function
void Board::make_Brick(Object_t c, sf::Vector2f location)
{
	Brick platform;

	sf::Sprite platfromSprite;
	platfromSprite.setTexture(manage->GetTexture(c));
	platfromSprite.setPosition(location.x, location.y);
	platfromSprite.setOrigin(manage->GetTexture(c).getSize().x / 2, manage->GetTexture(c).getSize().y / 2);
	
	platform.setPlatfromSprite(platfromSprite);

	if (c != O_TREETOP && c != O_TREE)
	{
		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(location.x / SCALE, location.y / SCALE);
		BodyDef.type = b2_staticBody;

		b2PolygonShape Shape;
		Shape.SetAsBox((platfromSprite.getGlobalBounds().width / 2) / SCALE, (platfromSprite.getGlobalBounds().height / 2) / SCALE);
		b2FixtureDef FixtureDef;
		FixtureDef.density = 0.5;
		FixtureDef.shape = &Shape;
		FixtureDef.filter.categoryBits = PLATFORM;

		b2Fixture* fixture = m_World->CreateBody(&BodyDef)->CreateFixture(&FixtureDef);
		fixture->SetUserData((void*)1);
	}
	m_Bricks.emplace_back(std::make_unique<Brick>(platform));
}
void Board::ShootHeli(const int& index, sf::RenderWindow& window, sf::Clock& time, sf::Vector2f pos)
{
	m_Helis[index]->Shooter(window, time, pos);
}
void Board::SpawnHeli(const int& index,sf::RenderWindow& window)
{
	m_CurrentHeli = index;

	if (m_helisChar[index] == 's' && !m_heli_spawned) // Standard heli creation 
	{
		
		StandardHeli Heli(GetWorld(), { 200.f,200.f }, manage);
		m_Helis.push_back(std::make_unique<StandardHeli>(Heli));	
		m_Helis[index]->SetHp(280);
		m_heli_spawned = true;
	}
	else if (m_helisChar[index] == 'b' && !m_heli_spawned) // Bomb heli creation
	{
		
		m_heli_spawned = true;
		BombHeli B_Heli(GetWorld(), { 200.f,200.f }, manage);
		m_Helis.push_back(std::make_unique <BombHeli>(B_Heli));
		m_Helis[index]->SetHp(400);
	}
	else if(m_helisChar[index] == 'r' && !m_heli_spawned) // Rocket heli creation
	{
		//m_heli_spawned = true;
		//RocketHeli B_Heli(GetWorld(), { 200.f,200.f }, manage);
		//m_Helis.push_back(std::make_unique <BombHeli>(B_Heli));
	}
	m_Helis[index]->SpawnHeli(window);
}

void Board::MovingHeli(const int& index, HUD& stats)
{
	m_Helis[index]->movingHeli(stats.getTime());
}

void Board::setNumOfStandradHeli(const int& num)
{
	m_numOfStandardHeli += num;
}

void Board::setNumOfBombHeli(const int& num)
{
	m_numOfBombHeli += num;
}

void Board::setNumOfRocketHeli(const int& num)
{
	m_numOfRocketHeli += num;
}

void Board::setHeliSpawned(const bool& status)
{
	m_heli_spawned = status;
}

bool Board::getHeliSpawned()
{
	return m_heli_spawned;
}

int Board::getNumOfStandardHeli()
{
	return m_numOfStandardHeli;
}

int Board::getNumOfBombHeli()
{
	return m_numOfBombHeli;
}

int Board::getNumOfRocketHeli()
{
	return m_numOfRocketHeli;
}


//Return number of hostages
int Board::getNumOfHostages()
{
	return m_Hostages.size();
}

//This method free hostage that the player have saved (remove from vector and destroy body)
bool Board::hostageFree(Player& player)
{
	for (int j = 0; j < m_Hostages.size(); j++)
	{
		if (m_Hostages[j] != NULL)
		{
			if (player.getPlayerBodySprite().getGlobalBounds().intersects(m_Hostages[j]->getHostageSprite().getGlobalBounds())
				|| player.getPlayerLegsSprite().getGlobalBounds().intersects(m_Hostages[j]->getHostageSprite().getGlobalBounds())
				|| player.getPlayerArmSprite().getGlobalBounds().intersects(m_Hostages[j]->getHostageSprite().getGlobalBounds()))
			{
				m_Hostages[j]->hukusPukus();
				m_Hostages[j].reset();

				return true;
			}
		}
	}
	return false;
}

//This method check if the player met gift.
bool Board::playerMeetGiftBox(Player& player,HUD &stats)
{
	for (int j = 0; j < m_Gifts.size(); j++)
	{
		if (m_Gifts[j] != NULL)
		{
			if (player.getPlayerBodySprite().getGlobalBounds().intersects(m_Gifts[j]->getGiftBoxSprite().getGlobalBounds())
				|| player.getPlayerLegsSprite().getGlobalBounds().intersects(m_Gifts[j]->getGiftBoxSprite().getGlobalBounds())
				|| player.getPlayerArmSprite().getGlobalBounds().intersects(m_Gifts[j]->getGiftBoxSprite().getGlobalBounds()))
			{
				if(m_Gifts[j]->getCodeName() == 'a')
					m_Gifts[j]->AmmoGift(player, stats);
				
				if (m_Gifts[j]->getCodeName() == 's')
					m_Gifts[j]->ScoreGift(player, stats);

				if (m_Gifts[j]->getCodeName() == 'b')
					return true;

				m_Gifts[j]->HukusPukus();
				m_Gifts[j].reset();
				return true;
			}
		}
	}
	return false;

}

//AK soldiers check if the player is in there range
void Board::CheckProx(Player& player ,sf::RenderWindow& window,sf::Clock& time,const bool sound)
{
	for (int i = 0; i < m_Soldiers.size(); i++)
	{
		if (!m_Soldiers[i]->isDead())
		{
			m_Soldiers[i]->CheckProximity(player.getPlayerBodySprite().getPosition(), window, time,sound);
		}
	}
}

//Draw function
void Board::Draw(sf::RenderWindow& window)
{

	sf::View OriginalView;
	OriginalView = window.getView();
	m_World->Step(1 / 60.f, 8, 3);

	sf::View view1(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

	// Bricks Drawing loop
	for (auto i = 0; i < m_Bricks.size(); i++)
	{
		if (m_Bricks[i]->getPlatfromSprite().getTexture() == &manage->GetTexture(O_TREE) || m_Bricks[i]->getPlatfromSprite().getTexture() == &manage->GetTexture(O_TREETOP))
		{
			window.setView(OriginalView);
			//window.setView(view1);
		}
		else
		{
			window.setView(OriginalView);	

		}
		window.draw(m_Bricks[i]->getPlatfromSprite());
	}	
	
	int k = 0;

	for (b2Body* BodyIterator = m_World->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		//Soldiers Draw
		if ((int)BodyIterator->GetUserData() == SOLDIERS_BODY_DATA)
		{
			for (int num = 0; num < m_Soldiers.size(); num++)
			{
				if (m_Soldiers[num] != NULL)
				{
					m_Soldiers[num]->getSoldierSprite().setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y + 23);
					m_Soldiers[num]->SpawnSoldier(window);
				}

				BodyIterator = BodyIterator->GetNext();
			}
		}	
/*
		if ((int)BodyIterator->GetUserData() == HOSTGAES_DATA)
		{
			for (int x = 0; x < m_Hostages.size(); x++)		//Hostages Draw
			{
				if (m_Hostages[x] != NULL)
				{
					m_Hostages[x]->getHostageSprite().setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					m_Hostages[x]->SpawnHostage(window);
				}

				BodyIterator = BodyIterator->GetNext();
			}
		}*/

		for (int x = 0; x < m_Hostages.size(); x++)		//Hostages Draw
		{
			if ((int)BodyIterator->GetUserData() == 70 + x)	
			{
				if (m_Hostages[x] != NULL)
				{
					m_Hostages[x]->getHostageSprite().setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					m_Hostages[x]->SpawnHostage(window);
				}
			}
		}
		for (int z = 0; z < m_Gifts.size(); z++)
		{
			if ((int)BodyIterator->GetUserData() == 400 + z || (int)BodyIterator->GetUserData() == 420 + z||
				(int)BodyIterator->GetUserData() == 440 + z || (int)BodyIterator->GetUserData() == 460 + z)
			{
				if (m_Gifts[z] != NULL)
				{
					m_Gifts[z]->getGiftBoxSprite().setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					window.draw(m_Gifts[z]->getGiftBoxSprite());
				}

			}
		}
	
	}
}



void Board::CreateBox(int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	//b2Body* Body = m_World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	//Body->CreateFixture(&FixtureDef);

	b2Fixture* fixture = m_World->CreateBody(&BodyDef)->CreateFixture(&FixtureDef);
	//fixture->SetUserData((void*)2);
}

int Board::getNumOfHelis()
{
	return m_NumOfHelis;
}

b2World& Board::GetWorld()
{
	return *m_World.get();
}

Board::~Board()
{
}