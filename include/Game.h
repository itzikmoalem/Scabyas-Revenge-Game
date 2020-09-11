#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <AssetManager.h>
#include <Globals.h>
#include <Board.h>
#include <Helicopters.h>
#include <StandardHeli.h>
#include <BombHeli.h>
#include <SFML/Audio.hpp>
#include <HUD.h>


class Game
{
public:
	Game();
	~Game();

	void Run(sf::RenderWindow &window,  sf::Sprite& screen, bool& SoundFx, std::string &name);

	

private:
	bool IsStageCompleted(const HUD& hud);
	Board board;
	AssetManager* m_manage = m_manage->getInstance();

	int m_HeliKilled = 0;
};

