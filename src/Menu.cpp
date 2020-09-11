#include "Menu.h"
#include <conio.h>

Menu::Menu()
{
	m_manage->LoadAssets();
}

Menu::~Menu()
{
}

void Menu::Run()
{
	Game game;

	//Create a window
	m_Window.create(sf::VideoMode(1920, 1080, 32), "Game");
	m_Window.setFramerateLimit(60);

	//Create a sprite for background
	sf::Sprite BackGround;
	BackGround.setTexture(m_manage->GetTexture(O_World2));

	//Create buttons sprites
	sf::Sprite PlayGame, ExitGame, HighScores, Settings;

	DefineButtons(PlayGame, ExitGame, HighScores, Settings);

	sf::Sprite logo;
	logo.setTexture(m_manage->GetTexture(M_LOGO));
	logo.setPosition(1000, 400);

	//Create m_Music
	m_Music.setBuffer(m_manage->GetSound(S_BACKGROUND_MUSIC));
	m_Music.setLoop(1);
	m_Music.setVolume(50);

	s_Click.setBuffer(m_manage->GetSound(S_MOUSE_CLICK));
	s_Click.setVolume(50);

	m_Music.play();

	while (m_Window.isOpen())
	{
		m_Window.clear();

		m_Window.draw(BackGround);

		ButtonEffect(PlayGame, ExitGame, HighScores, Settings);

		m_Window.draw(PlayGame);
		m_Window.draw(HighScores);
		m_Window.draw(Settings);
		m_Window.draw(ExitGame);
		m_Window.draw(logo);

		m_Window.display();

		//get events from the user mouse
		if (auto event = sf::Event{}; m_Window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_Window.close();
				break;

			case sf::Event::MouseButtonPressed:
				s_Click.play();

			case sf::Event::MouseButtonReleased:
			{

				sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

				if (PlayGame.getGlobalBounds().contains(pos))
					game.Run(m_Window, BackGround, m_SoundFX, m_playerName);

				if (HighScores.getGlobalBounds().contains(pos))
					showHighScoreTable(m_Window, BackGround);

				if (Settings.getGlobalBounds().contains(pos))
					showGameSetting(m_Window, BackGround);

				if (ExitGame.getGlobalBounds().contains(pos))
					m_Window.close();
			}
			break;
			}
		}
	}
}

void Menu::showGameSetting(sf::RenderWindow& window, sf::Sprite& background)
{
	// settings rectangle texure load & define
	sf::Sprite Rec;
	Rec.setTexture(m_manage->GetTexture(M_RecSettings));
	Rec.setPosition(PLAY_BUTTON.x + 450, PLAY_BUTTON.y - 240);

	//High score button
	sf::Sprite settings;
	settings.setTexture(m_manage->GetTexture(M_SettingsTitle));
	settings.setPosition(PLAY_BUTTON.x + 650, PLAY_BUTTON.y - 330);

	//define player cube texture
	sf::Sprite playerCube;
	playerCube.setTexture(m_manage->GetTexture(O_PLAYER_NormalHead));
	playerCube.setPosition(SETTING.x + 20, SETTING.y + 30);
	playerCube.setScale(0.3, 0.3);

	// define player rectangle name 
	sf::RectangleShape playerNameRec(sf::Vector2f(310, 60));
	playerNameRec.setOutlineThickness(2.f);
	playerNameRec.setOutlineColor(sf::Color::Black);
	playerNameRec.setPosition(SETTING.x + 330, SETTING.y + 50);
	playerNameRec.setFillColor(sf::Color::White);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	// define text to the Name player
	sf::Text NameText;
	NameText.setFont(font);
	NameText.setFillColor(sf::Color::Black);
	NameText.setStyle(sf::Text::Bold);
	NameText.setCharacterSize(45);
	NameText.setString("Name : ");
	NameText.setPosition(SETTING.x + 150, SETTING.y + 50);

	// define player name cube 
	//sf::Text playerName;
	m_PlayerNameText.setFont(font);
	m_PlayerNameText.setFillColor(sf::Color::Black);
	m_PlayerNameText.setCharacterSize(40);
	m_PlayerNameText.setPosition(SETTING.x + 340, SETTING.y + 50);

	m_PlayerNameText.setString(m_playerName);


	// define text to the Music
	sf::Text MusicText;
	MusicText.setFont(font);
	MusicText.setFillColor(sf::Color::Black);
	MusicText.setCharacterSize(45);
	MusicText.setStyle(sf::Text::Bold);
	MusicText.setString("Music : ");
	MusicText.setPosition(SETTING.x + 20, SETTING.y + 180);

	sf::CircleShape MusicCirc;
	MusicCirc.setFillColor(sf::Color::Green);
	MusicCirc.setRadius(20);
	MusicCirc.setOutlineColor(sf::Color::Black);
	MusicCirc.setOutlineThickness(3);
	MusicCirc.setOrigin({ 0,0 });
	MusicCirc.setPosition(SETTING.x + 180, SETTING.y + 190);

	// define text to the Sound
	sf::Text SoundText;
	SoundText.setFont(font);
	SoundText.setStyle(sf::Text::Bold);
	SoundText.setFillColor(sf::Color::Black);
	SoundText.setCharacterSize(45);
	SoundText.setString("SoundFX : ");
	SoundText.setPosition(SETTING.x + 350, SETTING.y + 180);

	sf::CircleShape SoundCirc;
	SoundCirc.setFillColor(sf::Color::Green);
	SoundCirc.setOutlineColor(sf::Color::Black);
	SoundCirc.setOutlineThickness(3);
	SoundCirc.setOrigin({ 0,0 });
	SoundCirc.setRadius(20);
	SoundCirc.setPosition(SETTING.x + 600, SETTING.y + 190);

	// define text to the Map
	sf::Text MapText;
	MapText.setFont(font);
	MapText.setStyle(sf::Text::Bold);
	MapText.setFillColor(sf::Color::Black);
	MapText.setCharacterSize(45);
	MapText.setString("Map : ");
	MapText.setPosition(SETTING.x + 30, SETTING.y + 325);

	sf::Sprite world;
	world.setTexture(m_manage->GetTexture(O_World));
	world.setScale(0.1, 0.1);
	world.setPosition(SETTING.x + 400, SETTING.y + 310);

	sf::Sprite world2;
	world2.setTexture(m_manage->GetTexture(O_World2));
	world2.setScale(0.1, 0.1);
	world2.setPosition(SETTING.x + 180, SETTING.y + 310);

	// Score rectangle texure load & define
	sf::Sprite BackButton;
	BackButton.setPosition({ 835, 750 });

	while (m_Window.isOpen())
	{
		sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

		m_Window.clear();

		m_Window.draw(background);

		m_Window.draw(Rec);
		m_Window.draw(settings);
		m_Window.draw(playerCube);
		m_Window.draw(playerNameRec);
		m_Window.draw(NameText);
		m_Window.draw(m_PlayerNameText);

		m_Window.draw(MusicText);
		m_Window.draw(MusicCirc);
		m_Window.draw(SoundText);
		m_Window.draw(SoundCirc);

		m_Window.draw(MapText);
		m_Window.draw(world);
		m_Window.draw(world2);

		backButtonEffect(pos, BackButton);

		m_Window.draw(BackButton);


		if (auto event = sf::Event{}; m_Window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_Window.close();
				break;

			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

				if (BackButton.getGlobalBounds().contains(pos))
					return;

				if (MusicCirc.getGlobalBounds().contains(pos))
				{
					SwapColor(MusicCirc);
					if (MusicCirc.getFillColor() == sf::Color::Green)
						m_Music.play();
					else
						m_Music.pause();
				}

				if (SoundCirc.getGlobalBounds().contains(pos))
				{
					m_SoundFX = false;
					SwapColor(SoundCirc);
				}

				if (world.getGlobalBounds().contains(pos))		//Chose map number one
					background.setTexture(m_manage->GetTexture(O_World));

				if (world2.getGlobalBounds().contains(pos))		//Chose map number two
					background.setTexture(m_manage->GetTexture(O_World2));

				if (playerNameRec.getGlobalBounds().contains(pos))	//Chose Change name
					ChangeName();
			}
			break;

			case sf::Event::MouseButtonPressed:
				s_Click.play();
			}
		}

		m_Window.draw(m_PlayerNameText);
		m_Window.display();
	}
}
void Menu::showHighScoreTable(sf::RenderWindow& window, sf::Sprite& background)//,sf::Sprite &scores)
{
	//High score button
	sf::Sprite score;
	score.setTexture(m_manage->GetTexture(M_TopScore));
	score.setPosition(PLAY_BUTTON.x + 620, PLAY_BUTTON.y - 320);

	// Trophie texture load & define
	sf::Sprite trophie;
	trophie.setTexture(m_manage->GetTexture(M_Trophie));
	trophie.setPosition(PLAY_BUTTON.x + 1050, PLAY_BUTTON.y - 320);

	// Score rectangle texure load & define
	sf::Sprite scoreRec;
	scoreRec.setTexture(m_manage->GetTexture(M_RecScore));
	scoreRec.setPosition(PLAY_BUTTON.x + 450, PLAY_BUTTON.y - 200);

	// Score rectangle texure load & define
	sf::Sprite BackButton;
	BackButton.setPosition({ 835, 750 });

	// Open scores file
	m_scores_file.open("Scores.txt");

	while (m_Window.isOpen())
	{
		sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

		m_Window.clear();

		m_Window.draw(background);
		m_Window.draw(score);
		m_Window.draw(trophie);
		m_Window.draw(scoreRec);

		backButtonEffect(pos, BackButton);
		m_Window.draw(BackButton);

		scoreSorting();
		printTable();

		if (auto event = sf::Event{}; m_Window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_Window.close();
				break;

			case sf::Event::MouseButtonPressed:
				s_Click.play();

			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

				if (BackButton.getGlobalBounds().contains(pos))
					return;
			}
			break;
			}
		}

		m_Window.display();
	}

	m_scores_file.close();
}

void Menu::scoreSorting()
{
	std::string topName;
	unsigned int temp_score = 0, highscore = 0;

	playerStats temp;
	std::vector <playerStats> Keep;
	std::vector <int> points;

	while (!m_scores_file.eof())
	{
		m_scores_file >> temp.name;
		m_scores_file >> temp.score;
		points.push_back(temp.score);
		Keep.push_back(temp);
	}

	std::sort(points.begin(), points.end());

	for (int i = points.size() - 1; i >= 0; i--)
	{
		for (int n = 0; n < Keep.size(); n++)
		{
			if (points[i] == Keep[n].score)
			{
				m_top10.push_back(Keep[n]);
				break;
			}
		}
	}
	for (int y = 0; y < m_top10.size(); y++)
		m_top10[y].position = y;
}

void Menu::printTable()
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(25);

	sf::Vector2f pos = { 600.f,260.f };
	string line;

	text.setStyle(sf::Text::Bold);

	text.setString("Place:");	//Head Table
	text.setPosition(pos);
	m_Window.draw(text);

	text.setString("Name:");
	text.setPosition(pos.x += 300, pos.y);
	m_Window.draw(text);

	text.setString("Score:");
	text.setPosition(pos.x += 280, pos.y);
	m_Window.draw(text);

	text.setStyle(sf::Text::Regular);
	pos.y += 60;
	pos.x = 620;

	for (int i = 0; i < 10; i++)
	{
		std::stringstream rank;
		std::stringstream score;

		// Position draw
		rank << m_top10[i].position + 1; // Staring from zero, than +1 intiliaze from 1.
		text.setString(rank.str());
		text.setPosition(pos);
		m_Window.draw(text);

		// Name draw
		line = m_top10[i].name;
		text.setString(line);
		text.setPosition(pos.x += 285, pos.y);
		m_Window.draw(text);

		// Score draw
		score << m_top10[i].score;
		text.setString(score.str());
		text.setPosition(pos.x += 285, pos.y);
		m_Window.draw(text);

		pos.y += 40;
		pos.x = 620;
	}
}

void Menu::backButtonEffect(const sf::Vector2f& v, sf::Sprite& BackButton)
{
	if (BackButton.getGlobalBounds().contains(v))
	{
		//s_Button.play();
		BackButton.setTexture(m_manage->GetTexture(M_BackPressed));
	}
	else
		BackButton.setTexture(m_manage->GetTexture(M_Back));
}

void Menu::SwapColor(sf::CircleShape& circ)
{
	if (circ.getFillColor() == sf::Color::Green)
		circ.setFillColor(sf::Color::Red);
	else if (circ.getFillColor() == sf::Color::Red)
		circ.setFillColor(sf::Color::Green);
}

void Menu::DefineButtons(sf::Sprite& n, sf::Sprite& e, sf::Sprite& h, sf::Sprite& s)
{
	n.setPosition(PLAY_BUTTON);
	h.setPosition(HIGHSCORE_BUTTON);
	s.setPosition(SETTINGS_BUTTON);
	e.setPosition(EXIT_BUTTON);
}

void Menu::ButtonEffect(sf::Sprite& n, sf::Sprite& e, sf::Sprite& h, sf::Sprite& s)
{
	sf::Vector2f pos(sf::Mouse::getPosition(m_Window).x, sf::Mouse::getPosition(m_Window).y);

	//"NewGame" button check
	if (n.getGlobalBounds().contains(pos))
		n.setTexture(m_manage->GetTexture(M_PlayPressed));
	else
		n.setTexture(m_manage->GetTexture(M_Play));

	//"Settings" button check
	if (s.getGlobalBounds().contains(pos))
		s.setTexture(m_manage->GetTexture(M_SettingsPressed));
	else
		s.setTexture(m_manage->GetTexture(M_Settings));

	//"HighScore" button check
	if (h.getGlobalBounds().contains(pos))
		h.setTexture(m_manage->GetTexture(M_HighScorePressed));
	else
		h.setTexture(m_manage->GetTexture(M_HighScore));

	//"ExitGame" button check
	if (e.getGlobalBounds().contains(pos))
		e.setTexture(m_manage->GetTexture(M_ExitPressed));
	else
		e.setTexture(m_manage->GetTexture(M_Exit));
}

void Menu::ChangeName()
{
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);



	cin >> m_playerName;

	try {

		int BigLetters = 2;

		if (m_playerName.size() > 10)
			throw std::runtime_error::runtime_error("10 Letters only! .\n");

		for (int i = 0; i < m_playerName.size(); i++)
		{
			char c;
			c = m_playerName[i];


			if (isdigit(c))
				throw std::runtime_error::runtime_error("Please don't use Digits.\n");

			if (isupper(c))
				BigLetters--;
		}

		if (BigLetters < 0)
			throw std::runtime_error::runtime_error("Two capital letter please.\n");

	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		ChangeName();
	}

	m_playerName = m_playerName;
	m_PlayerNameText.setString(m_playerName);

	ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
}
