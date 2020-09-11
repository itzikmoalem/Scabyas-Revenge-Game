#pragma once

#include <SFML/Graphics.hpp>
#include <AssetManager.h>
#include <Globals.h>
#include <Game.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <StandardHeli.h>
#include <cctype>
#include <Windows.h>

using namespace std;

struct playerStats
{
	std::string name;
	float score;
	unsigned int position;
};

class Menu
{
public:
	Menu();
	~Menu();

	void Run();

	void showGameSetting(sf::RenderWindow& window, sf::Sprite& background);

	void showHighScoreTable(sf::RenderWindow& window, sf::Sprite& background);//,sf::Sprite& scores);
	void scoreSorting();
	void printTable();

	void backButtonEffect(const sf::Vector2f& v, sf::Sprite& BackButton);

	void SwapColor(sf::CircleShape& circ);

private:

	void DefineButtons(sf::Sprite& n, sf::Sprite& e, sf::Sprite& h, sf::Sprite& s);	//n = NewGame, e = ExitGame
	void ButtonEffect(sf::Sprite& n, sf::Sprite& e, sf::Sprite& h, sf::Sprite& s);		//h = HighScore, s = Settings
	void ChangeName();

	//Members
	AssetManager* m_manage = m_manage->getInstance();
	fstream m_scores_file;
	sf::RenderWindow m_Window;
	std::vector<playerStats> m_top10;
	std::string m_playerName = "Player";

	sf::Text m_PlayerNameText;
	sf::Sound m_Music;
	bool m_SoundFX = true;

	sf::Sound s_Click;
};