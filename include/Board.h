#pragma once
#include <fstream>
#include <iostream>
#include <AssetManager.h>
#include <Globals.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <Brick.h>
#include <Infantry.h>
#include <Hostage.h>
#include <Player.h>
#include <GiftBox.h>
#include <AKSoldier.h>
#include <RPGSoldier.h>
#include <Helicopters.h>
#include <StandardHeli.h>
#include <BombHeli.h>
#include <HUD.h>

class Board
{
public:
	Board();
	void CreateLimits();
	void CreateBody(b2Vec2 pos, float SizeX, float SizeY);
	void ReadLevel(sf::RenderWindow & window);

	void UpdateStats(HUD& stats);

	// Make objects functions
	//void make_Hostage(Object_t c, sf::Vector2f location);
	void setBoxCode(const char& l);
	char getBoxCode();
	void make_Brick(Object_t c,sf::Vector2f location);
	void SpawnHeli(const int& index, sf::RenderWindow& window);
	void MovingHeli(const int& index, HUD& stats);
	void ShootHeli(const int& index, sf::RenderWindow& window, sf::Clock& time, sf::Vector2f pos);

	//Set functions
	void setNumOfStandradHeli(const int& num);
	void setNumOfBombHeli(const int& num);
	void setNumOfRocketHeli(const int& num);
	void setHeliSpawned(const bool& status);

	// Get functions
	bool getHeliSpawned();
	int getNumOfStandardHeli();
	int getNumOfBombHeli();
	int getNumOfRocketHeli();
	int getNumOfHostages();
	int getNumOfHelis();
	b2World& GetWorld();


	bool hostageFree(Player &player);
	bool playerMeetGiftBox(Player& player, HUD& stats);
	void CheckProx(Player& player, sf::RenderWindow& window, sf::Clock& time,const bool sound);

	void Draw(sf::RenderWindow& window);
	void CreateBox(int MouseX, int MouseY);
	~Board();

private:
	//levels file (txt)
	std::ifstream m_Levels;

	//make a world on box2d
	std::unique_ptr<b2World> m_World;

	//window
	sf::RenderWindow m_Window;

	//soldiers members
	int m_NumOfSoldiers = 0;

	//helis members
	int m_NumOfHelis = 0;
	bool m_heli_spawned = false;
	int m_numOfStandardHeli = 0;
	int m_numOfBombHeli = 0;
	int m_numOfRocketHeli = 0;
	int m_CurrentHeli;

	//hostages  members
	int m_NumOfHostages = 0;

	//singleton assetmanager
	AssetManager* manage = manage->getInstance();

	//boxes
	char box_code;

	//Vectors:
	std::vector<std::unique_ptr<Hostage>> m_Hostages;
	std::vector<std::unique_ptr<Infantry>> m_Soldiers;
	std::vector<std::unique_ptr<Brick>> m_Bricks;
	std::vector<std::unique_ptr<GiftBox>> m_Gifts;
	std::vector<std::unique_ptr<Helicopters>> m_Helis; //Helis vector
	std::vector<char> m_helisChar;
};
