
#include "AssetManager.h"
#include "Globals.h"

AssetManager* AssetManager::instance = 0;

AssetManager::AssetManager() {
	m_myContactListenerInstance.numFootContacts = 0;
	m_myContactListenerInstance.BulletHitHeli = false;
	m_myContactListenerInstance.BulletHitSoldier = false;
	m_myContactListenerInstance.EnemyBulletHitHero = false;
};

AssetManager* AssetManager::getInstance()
{
	if (!instance)
	{
		instance = new AssetManager;

	}
	return instance;
}

void AssetManager::OpenFile(const std::string name)
{
	m_Levels.open(name, std::ifstream::in);
}

std::ifstream& AssetManager::GetLevels()
{
	return m_Levels;
}

void AssetManager::LoadTexture(const int name, const std::string FileName)
{
	sf::Texture tex;
	
	if (tex.loadFromFile(FileName))
	{
		this->m_textures[name] = tex;
	}
}


sf::Texture& AssetManager::GetTexture(const int name)
{
	return this->m_textures.at(name);
}

void AssetManager::LoadFont(const int name, const std::string FileName)
{
	sf::Font font;

	if (font.loadFromFile(FileName))
	{
		this->m_fonts[name] = font;
	}
}

sf::Font& AssetManager::GetFont(const int name)
{
	return this->m_fonts.at(name);
}

void AssetManager::LoadSound(const int name, const std::string FileName)
{
	sf::SoundBuffer sound;

	if (sound.loadFromFile(FileName))
	{
		this->m_sounds[name] = sound;
	}
}



sf::SoundBuffer& AssetManager::GetSound(const int name)
{
	return this->m_sounds.at(name);
}

void AssetManager::LoadAssets()
{
	//Menu Textures
	this->LoadTexture(M_Play, PLAY_GAME);
	this->LoadTexture(M_PlayPressed, PLAY_GAME_PRESSED);
	this->LoadTexture(M_Exit, EXIT_GAME);
	this->LoadTexture(M_ExitPressed, EXIT_GAME_PRESSED);
	this->LoadTexture(M_Settings, SETTINGS_GAME);
	this->LoadTexture(M_SettingsPressed, SETTINGS_GAME_PRESSED);
	this->LoadTexture(M_HighScore, HIGH_SCORE);
	this->LoadTexture(M_HighScorePressed, HIGH_SCORE_PRESSED);
	this->LoadTexture(M_Trophie, TROPHIE);
	this->LoadTexture(M_Back, BACK);
	this->LoadTexture(M_BackPressed, BACK_PRESSED);
	this->LoadTexture(M_TopScore, TOP_SCORE_TITLE);
	this->LoadTexture(M_RecScore, REC_SCORE);
	this->LoadTexture(M_SettingsTitle, SETTINGS_TITLE);
	this->LoadTexture(M_RecSettings, REC_SETTINGS);
	this->LoadTexture(M_HUD, HUD_BAR);
	this->LoadTexture(M_UpperHUD, UPPER_HUD);
	this->LoadTexture(M_LIFE_INDICATOR, HEALTH_BAR);
	this->LoadTexture(M_EMPTY_LIFE_INDICATOR, EMPTY_HEALTH_BAR);
	this->LoadTexture(M_LOGO, LOGO);

	//Game Textures
	this->LoadTexture(O_box, BOX_PNG_FILEPATH);
	this->LoadTexture(O_AMMO_GIFT, AMMO_GIFT);
	this->LoadTexture(O_WEAPON_GIFT, WEAPON_GIFT);
	this->LoadTexture(O_World, WORLD_PNG_FILEPATH);
	this->LoadTexture(O_World2, WORLD_PNG_FILEPATH2);
	this->LoadTexture(O_AIM, AIM);
	this->LoadTexture(O_BULLET, BULLETS);

	//Blocks Textures
	this->LoadTexture(O_TOPLEFT, TOPLEFT_PNG_FILEPATH);
	this->LoadTexture(O_TOPLEFT2, TOPLEFT2_PNG_FILEPATH);
	this->LoadTexture(O_TOPRIGHT, TOPRIGHT_PNG_FILEPATH);
	this->LoadTexture(O_TOPRIGHT2, TOPRIGHT2_PNG_FILEPATH);
	this->LoadTexture(O_MIDDLE, MIDDLE_PNG_FILEPATH);
	this->LoadTexture(O_MIDDLE2, MIDDLE2_PNG_FILEPATH);
	this->LoadTexture(O_MIDDLE3, MIDDLE3_PNG_FILEPATH);
	this->LoadTexture(O_TOPMIDDLE, TOPMIDDLE_PNG_FILEPATH);
	this->LoadTexture(O_TREE, TREE_PNG_FILEPATH);
	this->LoadTexture(O_TREETOP, TREETOP_PNG_FILEPATH);

	//Player Textures
	this->LoadTexture(O_BODY_L, BODY_LEFT);
	this->LoadTexture(O_BODY_R, BODY_RIGHT);
	
	this->LoadTexture(O_LEGS_L1, LEGS_LEFT_POS_1);
	this->LoadTexture(O_LEGS_L2, LEGS_LEFT_POS_2);
	this->LoadTexture(O_LEGS_L3, LEGS_LEFT_POS_3);
	this->LoadTexture(O_LEGS_L4, LEGS_LEFT_POS_4);


	this->LoadTexture(O_LEGS_R1, LEGS_RIGHT_POS_1);
	this->LoadTexture(O_LEGS_R2, LEGS_RIGHT_POS_2);
	this->LoadTexture(O_LEGS_R3, LEGS_RIGHT_POS_3);
	this->LoadTexture(O_LEGS_R4, LEGS_RIGHT_POS_4);
	this->LoadTexture(O_LEGS_STAND, LEGS_STAND);

	this->LoadTexture(O_HEAD_L, HEAD_LEFT_POS_1);
	this->LoadTexture(O_HEAD_R, HEAD_RIGHT_POS_1);

	this->LoadTexture(O_BODY_JUMP_LEFT, BODY_JUMP_LEFT);
	this->LoadTexture(O_BODY_JUMP_RIGHT, BODY_JUMP_RIGHT);


	this->LoadTexture(O_ARM_PISTOL_LEFT, ARM_PISTOL_LEFT);
	this->LoadTexture(O_ARM_PISTOL, ARM_PISTOL);
	this->LoadTexture(O_PISTOL, PISTOL);

	//Helicopter standard Textures
	this->LoadTexture(O_PROPELLER1, HELI_PROPELLER1);
	this->LoadTexture(O_PROPELLER2, HELI_PROPELLER2);

	this->LoadTexture(O_HELI_EMPTY_HEALTH, HELI_EMPTY_HEALTH);
	this->LoadTexture(O_HELI_FULL_HEALTH, HELI_FULL_HEALTH);

	this->LoadTexture(O_STANDARD_HELI_GUN, STANDARD_HELI_GUN);
	this->LoadTexture(O_STANDARD_HELI_BODY_R, STANDARD_HELI_BODY_R);
	this->LoadTexture(O_STANDARD_HELI_DOWN_R, STANDARD_HELI_DOWN_R);
	this->LoadTexture(O_STANDARD_HELI_BODY_L, STANDARD_HELI_BODY_L);
	this->LoadTexture(O_STANDARD_HELI_DOWN_L, STANDARD_HELI_DOWN_L);


	//Helicopter bomb Textures
	this->LoadTexture(O_BOMB_HELI_GUN, BOMB_HELI_GUN);
	this->LoadTexture(O_BOMB_HELI_BODY_R, BOMB_HELI_BODY_R);
	this->LoadTexture(O_BOMB_HELI_BODY_L, BOMB_HELI_BODY_L);
	this->LoadTexture(O_BOMB_HELI_DOWN_L, BOMB_HELI_DOWN_L);
	this->LoadTexture(O_BOMB_HELI_DOWN_R, BOMB_HELI_DOWN_R);

	//Soldier Textures
	this->LoadTexture(O_ENEMY_AK_L, SOLDIER_AK_L);
	this->LoadTexture(O_ENEMY_AK_R, SOLDIER_AK_R);
	this->LoadTexture(O_ENEMY_BODY1_R, SOLDIER_BODY1_R);
	this->LoadTexture(O_ENEMY_BODY1_L, SOLDIER_BODY1_L);

	this->LoadTexture(O_ENEMY_RPG_L, SOLDIER_RPG_L);
	this->LoadTexture(O_ENEMY_RPG_R, SOLDIER_RPG_R);
	this->LoadTexture(O_ENEMY_BODY2_R, SOLDIER_BODY2_R);
	this->LoadTexture(O_ENEMY_BODY2_L, SOLDIER_BODY2_L);

	//Explosion
	this->LoadTexture(O_EXPLOSION1, EXPOLSION1);

	//Guns Textures
	this->LoadTexture(O_PISTOL_BULLET, PISTOL_BULLET);

	//Hostage Textures
	this->LoadTexture(O_HOSTAGE1, HOSTAGE1);
	this->LoadTexture(O_HOSTAGE2, HOSTAGE2);
	this->LoadTexture(O_HOSTAGE3, HOSTAGE3);


	//Levels input 
	this->OpenFile(LEVELS_TXT_FILEPATH);

	//Sounds
	this->LoadSound(S_HELICOPTER, HELICOPTER_SOUND);
	this->LoadSound(S_BACKGROUND_MUSIC, BACKGROUND_MUSIC);
	this->LoadSound(S_PISTOL_SHOT, PISTOL_SOUND);
	this->LoadSound(S_AK_SHOT, AK_SHOT);
	this->LoadSound(S_BUTTONS_SOUND, BUTTONS_SOUND);
	this->LoadSound(S_HOSTAGES_RESCUED, HOSTAGES_RESCUED);
	this->LoadSound(S_OK_LETS_GO, OK_LETS_GO);
	this->LoadSound(S_MOUSE_CLICK, MOUSE_CLICK);
	this->LoadSound(S_ENEMY_DOWN, ENEMY_DOWN);

	//New player load texture (Pink)
	this->LoadTexture(O_PLAYER_NormalHead, PLAYER_NORMAL_HEAD);

	this->LoadFont(M_FONT, ARIAL);

}

MyContactListener& AssetManager::GetContactListener()
{
	return m_myContactListenerInstance;
}

