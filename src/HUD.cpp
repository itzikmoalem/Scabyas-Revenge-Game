#include "HUD.h"



HUD::HUD()
{
}

//HUD's constarctor, build the stats of the level by the board
HUD::HUD(AssetManager*& manage,const std::string &name, const int h, const int helis)
{
	//Define HUD Textures
	m_life.setTexture(manage->GetTexture(O_PLAYER_NormalHead));
	m_life.setScale(0.15,0.15);
	m_life.setPosition(10, 950);
	

	m_gun.setTexture(manage->GetTexture(O_PISTOL));
	m_gun.setPosition(680, 945);
	m_gun.scale(0.3,0.3);

	m_bullet.setTexture(manage->GetTexture(O_PISTOL_BULLET));
	m_bullet.setPosition(980, 953);
	m_bullet.scale(0.85, 0.85);

	m_barStats.setTexture(manage->GetTexture(M_HUD));
	m_barStats.setPosition(0, 930);

	m_UpBarStats.setTexture(manage->GetTexture(M_UpperHUD));
	m_UpBarStats.setScale(0.6, 0.6);
	m_UpBarStats.setPosition(1700, 0);

	//define Player name text
	t_playerName.setFont(manage->GetFont(M_FONT));
	t_playerName.setPosition(464 , TEXT_POS_Y);
	t_playerName.setString(name);

	//define Player name text
	t_HP.setFont(manage->GetFont(M_FONT));
	t_HP.setPosition(500 , 943);
	t_HP.setCharacterSize(30);
	t_HP.setString("HP: " + std::to_string(m_PlayerHP));
	
	//define Gun name text
	t_gunName.setFont(manage->GetFont(M_FONT));
	t_gunName.setPosition(750, TEXT_POS_Y);
	t_gunName.setString(m_gunName);

	//define bullet text
	t_bullet.setFont(manage->GetFont(M_FONT));
	t_bullet.setPosition(1080, TEXT_POS_Y);
	std::stringstream bullets;
	bullets << -1;
	t_bullet.setString(bullets.str());
	
	//Define score text
	t_score.setFont(manage->GetFont(M_FONT));
	t_score.setPosition(1310, TEXT_POS_Y);
	t_score.setString("0");

	//define Level text
	t_level.setFont(manage->GetFont(M_FONT));
	t_level.setPosition(1820, 0);
	int level = 1;
	t_level.setCharacterSize(20);
	t_level.setString("Level: " + std::to_string(level));

	//define Time text
	t_time.setFont(manage->GetFont(M_FONT));
	t_time.setCharacterSize(20);
	t_time.setPosition(1710, 0);

	//define Hostages left text
	t_hostageLeft.setFont(manage->GetFont(M_FONT));
	t_hostageLeft.setPosition(1763, TEXT_POS_Y);
	m_hostages = h;
	int tempHostage = 0;
	t_hostageLeft.setString(std::to_string(tempHostage)+ "/"+ std::to_string(m_hostages));

	//define Helicopter left text
	t_helicopersLeft.setFont(manage->GetFont(M_FONT));
	t_helicopersLeft.setPosition(1550, TEXT_POS_Y);
	m_helisLeft = helis;
	int tempHelicopters = 0;
	t_helicopersLeft.setString(std::to_string(tempHelicopters)+ "/" + std::to_string(m_helisLeft));

	//define All saved text
	t_allsaved.setColor(sf::Color::Green);
	t_allsaved.setFont(manage->GetFont(M_FONT));
	t_allsaved.setCharacterSize(16);
	t_allsaved.setPosition(t_hostageLeft.getPosition().x + 50, TEXT_POS_Y + 10);
	t_allsaved.setString("All Saved!");

	//define sounds
	s_HostagesSound.setBuffer(manage->GetSound(S_HOSTAGES_RESCUED));
	s_HostagesSound.setVolume(50);

	s_OkLetsGo.setBuffer(manage->GetSound(S_OK_LETS_GO));
	s_OkLetsGo.setVolume(70);

	//s_SectorClear.setBuffer(manage->GetSound(S_SECTOR_CLEAR));
	//s_SectorClear.setVolume(60);
}

void HUD::setHostegs(const int& v)
{
	m_hostagesSaved += v;
}


void HUD::DrawHUD(sf::RenderWindow& window, const float pos)//, const sf::View view)
{
	//window.setView(sf::VideoMode==screen);

	int temp = clock.getElapsedTime().asSeconds();

	//Updatting stats
	t_time.setString("Time: " + std::to_string(temp));
	t_hostageLeft.setString(std::to_string(m_hostagesSaved) + "/" + std::to_string(m_hostages));
	t_score.setString(std::to_string(m_score));
	t_bullet.setString(std::to_string(m_bullets));
	t_gunName.setString(m_gunName);
	t_HP.setString("HP: " + std::to_string(m_PlayerHP));
	t_helicopersLeft.setString(std::to_string(m_helisDown)+ "/" + std::to_string(m_helisLeft));

	//Change view according to screen
	ChangeViewMyself(pos);

	//Draw HUD
	window.draw(m_barStats);
	window.draw(m_UpBarStats);

	for (int i = 1; i <= m_lifeCounter; i++)	//Print life
	{
		window.draw(m_life);
		m_life.setPosition(7 + pos + (40*i), 940);
	}
	window.draw(t_HP);
	window.draw(t_playerName);
	window.draw(m_gun);
	window.draw(t_gunName);
	window.draw(m_bullet);
	window.draw(t_bullet);
	window.draw(t_score);
	window.draw(t_level);
	window.draw(t_helicopersLeft);
	window.draw(t_hostageLeft);
	window.draw(t_time);

	if (m_PlayerHP <= 0)
	{
		m_lifeCounter--;

		if(m_lifeCounter > 0)
		m_PlayerHP = 100;
	}

	if (HostagesSavedAll())
	{
		if (!b_HostageSoundPlayed)
		{
			s_HostagesSound.play();
			b_HostageSoundPlayed = true;
			b_OkLetsGoPlayed = false;
		}

		if (AllHelisDown())
			s_SectorClear.play();

		window.draw(t_allsaved);
	}

	if (!b_OkLetsGoPlayed)
	{
		s_OkLetsGo.play();
		b_OkLetsGoPlayed = true;
	}
}

void HUD::setHeliDown(const int m)
{
	m_helisDown = m;
}

void HUD::decreaseHP(const int h)
{
	m_PlayerHP -= h;
}

int HUD::GetPlayerHP() const
{
	return m_PlayerHP;
}

void HUD::setScore(const int s)
{
	m_score += s;
}

void HUD::setLife(const int l)
{
	m_lifeCounter += 1;
}

void HUD::setAmmo(const int a)
{ 
	m_bullets += a;
}


//Get time 
int HUD::getTime()
{
	return clock.getElapsedTime().asMilliseconds();
}

int HUD::GetHelisSpawned() const
{
	return m_helis_index_spawn;
}

void HUD::IncrementHelisSpawned()
{
	m_helis_index_spawn++;
	m_helisDown++;
}

std::string HUD::getGunName() const
{
	return m_gunName;
}

HUD::~HUD()
{
}

//Hostages saved all method, print "all saved"


bool HUD::HostagesSavedAll()
{
	if (m_hostages == m_hostagesSaved)
	{
		t_hostageLeft.setColor(sf::Color::Green);
		return true;
	}
	return false;
}

bool HUD::AllHelisDown()
{
	if (m_helisDown == m_helisLeft)
		return true;

	return false;
}

int HUD::GetLifeCount()
{
	return m_lifeCounter;
}

void HUD::ChangeViewMyself(const float pos)
{
	m_barStats.setPosition(pos, m_barStats.getPosition().y);
	m_UpBarStats.setPosition(1630 + pos, m_UpBarStats.getPosition().y);
	m_life.setPosition(5 + pos, m_life.getPosition().y);

	t_HP.setPosition(143 + pos, t_HP.getPosition().y);
	m_bullet.setPosition(1038 + pos, m_bullet.getPosition().y);
	m_gun.setPosition(718 + pos, m_gun.getPosition().y);

	t_playerName.setPosition(442 + pos, t_playerName.getPosition().y);
	t_gunName.setPosition(808 + pos, t_gunName.getPosition().y);
	t_bullet.setPosition(1138 + pos, t_bullet.getPosition().y);
	t_score.setPosition(1315 + pos, t_score.getPosition().y);
	t_level.setPosition(1798 + pos, t_level.getPosition().y);
	t_hostageLeft.setPosition(1760 + pos, t_hostageLeft.getPosition().y);
	t_helicopersLeft.setPosition(1528 + pos, t_helicopersLeft.getPosition().y);
	t_time.setPosition(1688 + pos, t_time.getPosition().y);
	t_allsaved.setPosition(1820 + pos, t_allsaved.getPosition().y);
}
