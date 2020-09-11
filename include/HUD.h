#pragma once

#include <AssetManager.h>
#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <sstream>


class HUD 
{
public:

	HUD();
	HUD(AssetManager*& manage,const std::string& name, const int h, const int helis);

	void setHostegs(const int& v);
	void DrawHUD(sf::RenderWindow& window, const float pos);
	void setHeliDown(const int m);

	void decreaseHP(const int h);
	void setScore(const int s);
	void setLife(const int l);
	void setAmmo(const int a);
	int getTime();
	int GetHelisSpawned() const;
	void IncrementHelisSpawned();
	std::string getGunName() const;
	int GetPlayerHP() const;
	int GetLifeCount();
	~HUD();

private:
	sf::Sprite m_UpBarStats;
	sf::Sprite m_barStats; // The rectangle of the bar
	sf::Sprite m_life; // Holding the life number
	sf::Sprite m_lifeIndicator; // Holding the life indicator
	sf::Sprite m_emptyLifeIndicator;
	sf::Sprite m_bullet; // sprite of bullet
	sf::Sprite m_gun;

	std::string m_gunName = "Pistol";

	int m_bullets = -1;
	unsigned int m_level = 1;
	unsigned int m_score = 0;
	unsigned int m_lifeCounter = 3;
	unsigned int m_PlayerHP = 100;
	unsigned int m_helisLeft = 0;
	unsigned int m_hostagesSaved = 0;
	unsigned int m_hostages = 0;
	int m_helisDown = 0;
	sf::Text t_HP;
	sf::Text t_playerName;
	sf::Text t_gunName;
	sf::Text t_bullet;
	sf::Text t_score;
	sf::Text t_level;
	sf::Text t_hostageLeft;
	sf::Text t_helicopersLeft;
	sf::Text t_time;
	sf::Text t_allsaved;
	
	sf::Clock clock;


	sf::Sound s_HostagesSound;
	bool b_HostageSoundPlayed = false;

	sf::Sound s_OkLetsGo;
	bool b_OkLetsGoPlayed = false;

	sf::Sound s_SectorClear;

	// score?
	// level?

	bool HostagesSavedAll();
	bool AllHelisDown();


	void ChangeViewMyself(const float pos);

	int m_helis_index_spawn = 0;
};
