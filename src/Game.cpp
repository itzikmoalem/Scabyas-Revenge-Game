#include "Game.h"
#include "Player.h"

Game::Game()
{
}

void Game::Run(sf::RenderWindow& window,  sf::Sprite &screen, bool &SoundFx,std::string& name)
{	
	
	board.ReadLevel(window);
	board.CreateLimits();

	HUD stats(m_manage, name, board.getNumOfHostages(), board.getNumOfHelis());

	sf::View view1(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
	const float LeftBoundary = -20;
	const float RightBoundary = 550;

	b2Vec2 InitPos = { 100.f, 800.f };

	Player player(board.GetWorld(), InitPos);
	
	sf::Sound sound;
	sound.setBuffer(m_manage->GetSound(S_HELICOPTER));
	sound.setVolume(20);

	
	bool heli_spawned = false;

	while (window.isOpen() || stats.GetLifeCount() >= 0)
	{
		sf::Clock Timer;
		Timer.restart().asSeconds();
		sf::Clock time;
		time.restart().asSeconds();
		sf::Clock HeliTime;
		HeliTime.restart().asSeconds();
		//int numOfhostage = board.getNumOfHostages(); // Intilaize num of hostages

		while (!IsStageCompleted(stats))
		{
			window.clear();

			window.setView(view1);
			window.draw(screen);

			board.SpawnHeli(stats.GetHelisSpawned(), window);
			board.CheckProx(player, window,time,SoundFx);	//check range of the soldiers
			
			board.MovingHeli(stats.GetHelisSpawned(), stats);
			board.ShootHeli(stats.GetHelisSpawned(), window, HeliTime, player.getPlayerBodySprite().getPosition());

			board.Draw(window);

			stats.DrawHUD(window, screen.getPosition().x);

			if (!player.isStand())
				player.ChangeView(window, view1, screen);

			player.SpawnPlayer(window, Timer, SoundFx);

			if (board.hostageFree(player))	//player touched a hostage
			{
				stats.setHostegs(1);
				stats.setScore(35);
			}

			if (board.playerMeetGiftBox(player, stats))
			{
				if (board.getBoxCode() == 'a')
					stats.setAmmo(35);
			}

			board.UpdateStats(stats);

			//player.printGunsVector();

			window.display();
			
		}
	}
}

bool Game::IsStageCompleted(const HUD &hud)
{

	if (m_HeliKilled != board.getNumOfHelis())
		return false;

	return true;
}

Game::~Game()
{
}

