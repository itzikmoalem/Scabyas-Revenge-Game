#pragma once


enum Object_t
{
	O_BODY_L, O_BODY_R, O_LEGS_L1, O_LEGS_L2, O_LEGS_L3, O_LEGS_L4, O_LEGS_R1, O_LEGS_R2, O_LEGS_R3, O_LEGS_R4,
	O_LEGS_STAND, O_HEAD_L, O_HEAD_R,  O_AMMO_GIFT, O_WEAPON_GIFT,
    O_ARM_PISTOL, O_World, O_World2, O_box, O_ground, O_TOPLEFT, O_TOPRIGHT, O_TOPLEFT2, O_TOPRIGHT2,
	O_MIDDLE, O_MIDDLE2,O_MIDDLE3 , O_TOPMIDDLE, O_TREETOP, O_TREE, O_STANDARD_HELI_BODY_R, O_STANDARD_HELI_GUN,
	O_STANDARD_HELI_DOWN_R, O_STANDARD_HELI_BODY_L, O_STANDARD_HELI_DOWN_L, O_AIM,O_PROPELLER1, O_PROPELLER2,
	O_HOSTAGE1, O_HOSTAGE2, O_HOSTAGE3, O_BULLET,
	O_PLAYER_NormalHead, O_ENEMY_BODY1_R,O_ENEMY_BODY1_L, O_ENEMY_AK_R, O_ENEMY_AK_L,
						 O_ENEMY_BODY2_R,O_ENEMY_BODY2_L, O_ENEMY_RPG_R, O_ENEMY_RPG_L
	,O_PISTOL_BULLET, O_BOMB_HELI_BODY_L,
	O_BOMB_HELI_BODY_R, O_BOMB_HELI_DOWN_L, O_BOMB_HELI_DOWN_R, O_BOMB_HELI_GUN, O_BODY_JUMP_LEFT, O_BODY_JUMP_RIGHT,
	O_ARM_PISTOL_LEFT, O_PISTOL, O_HELI_FULL_HEALTH, O_HELI_EMPTY_HEALTH, O_EXPLOSION1, end
};

enum Menu_t
{
	M_Exit = end, M_ExitPressed, M_Play, M_PlayPressed, M_Settings, M_SettingsPressed, M_HighScore,
	M_HighScorePressed, M_Trophie, M_SCORE_REC, M_Back, M_BackPressed, M_TopScore, M_RecScore, M_SettingsTitle,
	M_RecSettings, M_HUD,M_UpperHUD, M_LIFE_INDICATOR, M_EMPTY_LIFE_INDICATOR, M_FONT, M_LOGO
};

enum Char_t
{
	C_EMPTY = '#', C_SOLDIER = '!', C_RPGSOLDIER = '^',
	C_MIDDLE2 = 'D', C_TOPRIGHT2 = 'E', C_TOPLEFT = 'L', C_MIDDLE = 'M', C_TOPRIGHT = 'R',
	C_TOPLEFT2 = 'S', C_TOPMIDDLE = 'T', C_TREETOP = 'V', C_TREE = 'I', C_HOSTAGE = '$', C_GIFTBOX = 'G', C_MIDDLE3 = 'C',
	C_STANDARDSPAWN = 'a', C_BOMBSPAWN = 'b', C_ROCKETSPAWN = 'c', C_JUSTBOX = 'X'
};

enum Sound_t
{
	S_HELICOPTER, S_BACKGROUND_MUSIC, S_PISTOL_SHOT, S_OK_LETS_GO, S_MOUSE_CLICK, S_HOSTAGES_RESCUED, S_AK_SHOT, S_BUTTONS_SOUND, S_ENEMY_DOWN
};

enum _entityCategory {
	BOUNDARY = 0x0001,
	HOSTAGE = 0x0002,
	ENEMY_HELI = 0x0004,
	ENEMY_SOLDIER = 0x0008,
	FRIENDLY_SOLDIER = 0x0010,
	PLATFORM = 0x0020,
	BOX = 0x0030,
	BULLET = 0x0040,
};


//-----------------Load Files-----------------//

//Sounds
const std::string HELICOPTER_SOUND = "HelicopterSoundEffects.ogg";
const std::string BACKGROUND_MUSIC = "background_music.ogg";
const std::string PISTOL_SOUND = "pistol_shot.ogg";
const std::string OK_LETS_GO = "Ok_Lets_Go.ogg";
const std::string MOUSE_CLICK = "Mouse_Click.ogg";
const std::string HOSTAGES_RESCUED = "Hostages_Has_Been_Rescued.ogg";
const std::string AK_SHOT = "AK_sound.ogg";
const std::string BUTTONS_SOUND = "Buttons_Sound.ogg";
const std::string ENEMY_DOWN = "Enemy_Down.ogg";


//GIFTS
const std::string AMMO_GIFT = "ammo_gift.png";
const std::string WEAPON_GIFT = "weapon_gift.png";
const std::string BULLETS = "bullet.png";

//HELIS
const std::string HELI_FULL_HEALTH = "HEliHealth_full.png";
const std::string HELI_EMPTY_HEALTH = "HEliHealth_empty.png";


const std::string HELI_PROPELLER1 = "heli_propeller1.png";
const std::string HELI_PROPELLER2 = "heli_propeller2.png";

const std::string STANDARD_HELI_GUN = "heli_standard_gun.png";
const std::string STANDARD_HELI_BODY_R = "heli_standard_r.png";
const std::string STANDARD_HELI_DOWN_R = "heli_standard_down_r.png";
const std::string STANDARD_HELI_BODY_L = "heli_standard_l.png";
const std::string STANDARD_HELI_DOWN_L = "heli_standard_down_l.png";


const std::string BOMB_HELI_BODY_R = "heli_bomb_r.png";
const std::string BOMB_HELI_BODY_L = "heli_bomb_l.png";
const std::string BOMB_HELI_DOWN_R = "bomb_heli_down_r.png";
const std::string BOMB_HELI_DOWN_L = "bomb_heli_down_l.png";
const std::string BOMB_HELI_GUN = "heli_bomb_gun.png";
// Player textures

const std::string BODY_JUMP_LEFT = "legs_jump_l.png";
const std::string BODY_JUMP_RIGHT = "legs_jump_r.png";

const std::string PISTOL = "pistol.png";
const std::string ARM_PISTOL = "pistol_r.png";
const std::string ARM_PISTOL_LEFT = "pistol_l.png";


const std::string LEGS_RIGHT_POS_1= "legs_r1.png";
const std::string LEGS_RIGHT_POS_2 = "legs_r2.png";
const std::string LEGS_RIGHT_POS_3 = "legs_r3.png";
const std::string LEGS_RIGHT_POS_4 = "legs_r4.png";

const std::string LEGS_LEFT_POS_1 = "legs_l1.png";
const std::string LEGS_LEFT_POS_2 = "legs_l2.png";
const std::string LEGS_LEFT_POS_3 = "legs_l3.png";
const std::string LEGS_LEFT_POS_4 = "legs_l4.png";

const std::string LEGS_STAND = "leg_stand.png";


const std::string BODY_RIGHT = "body_r.png";
const std::string BODY_LEFT = "body_l.png";

const std::string HEAD_RIGHT_POS_1 = "head_r.png";
const std::string HEAD_LEFT_POS_1 = "head_l.png";

// Explosions
const std::string EXPOLSION1 = "MidAirExplo__000.png";  


// New player (pink) textures
const std::string PLAYER_NORMAL_HEAD = "Player_HeadNormal.png";

//hostages
const std::string HOSTAGE1 = "hostage1.png";
const std::string HOSTAGE2 = "hostage2.png";
const std::string HOSTAGE3 = "hostage3.png";
//enemies
const std::string SOLDIER_BODY1_R = "Enemy_body1_r.png";
const std::string SOLDIER_BODY1_L = "Enemy_body1_l.png";
const std::string SOLDIER_AK_R = "Enemy_AK_r.png";
const std::string SOLDIER_AK_L = "Enemy_AK_l.png";

const std::string SOLDIER_BODY2_R = "Enemy_body2_r.png";
const std::string SOLDIER_BODY2_L = "Enemy_body2_l.png";
const std::string SOLDIER_RPG_R = "Enemy_RPG_r.png";
const std::string SOLDIER_RPG_L = "Enemy_RPG_l.png";

//Menu textures
const std::string EXIT_GAME = "exit.png";
const std::string EXIT_GAME_PRESSED = "exitpressed.png";
const std::string PLAY_GAME = "play.png";
const std::string PLAY_GAME_PRESSED = "playpressed.png";
const std::string SETTINGS_GAME = "settings.png";
const std::string SETTINGS_GAME_PRESSED = "settingspressed.png";
const std::string HIGH_SCORE = "highscores.png";
const std::string HIGH_SCORE_PRESSED = "highscorespressed.png";
const std::string TROPHIE = "Trophie.png";
const std::string BACK = "back_button.png";
const std::string BACK_PRESSED = "back_button_pressed.png";
const std::string TOP_SCORE_TITLE = "TopScore.png";
const std::string REC_SCORE = "RecScore.png";
const std::string SETTINGS_TITLE = "SettingsTitle.png";
const std::string REC_SETTINGS = "RecSettings.png";
const std::string LOGO = "logo.png";

const std::string WORLD_PNG_FILEPATH2 = "World2.png";
const std::string WORLD_PNG_FILEPATH = "World.png";
const std::string BOX_PNG_FILEPATH = "box.png";
const std::string AIM = "aim.png";

const std::string MIDDLE2_PNG_FILEPATH = "D.png";
const std::string MIDDLE3_PNG_FILEPATH = "C.png";
const std::string TOPRIGHT2_PNG_FILEPATH = "E.png";
const std::string TOPLEFT_PNG_FILEPATH = "L.png";
const std::string MIDDLE_PNG_FILEPATH = "M.png";
const std::string TOPRIGHT_PNG_FILEPATH = "R.png";
const std::string TOPLEFT2_PNG_FILEPATH = "S.png";
const std::string TOPMIDDLE_PNG_FILEPATH = "T.png";
const std::string TREETOP_PNG_FILEPATH = "V.png";
const std::string TREE_PNG_FILEPATH = "I.png";
const std::string GROUND_PNG_FILEPATH = "ground.png";

// HUD Textures
const std::string HUD_BAR = "HUD.png";
const std::string UPPER_HUD = "UpperHUD.png";
const std::string HEALTH_BAR = "HealthBar_full.png";
const std::string EMPTY_HEALTH_BAR = "HealthBar_empty.png";
const std::string PISTOL_BULLET = "PistolBullet.png";

//Another
const std::string LEVELS_TXT_FILEPATH = "Levels.txt";
const std::string ARIAL = "arial.ttf";

//-----------------Menu Settings-----------------//

const sf::Vector2f SETTING = {620,220};
const sf::Vector2f HELIPOINT = { 0, 250 };

const int BUTTON_WIDTH = 400;
const int BUTTON_LENGTH = 89;
const int BUTTON_SPACE = 25;

const sf::Vector2f PLAY_BUTTON = { 100,450 };
const sf::Vector2f HIGHSCORE_BUTTON = { 100,PLAY_BUTTON.y + BUTTON_LENGTH + BUTTON_SPACE };
const sf::Vector2f SETTINGS_BUTTON = { 100,HIGHSCORE_BUTTON.y + BUTTON_LENGTH + BUTTON_SPACE };
const sf::Vector2f EXIT_BUTTON = { 100,SETTINGS_BUTTON.y + BUTTON_LENGTH + BUTTON_SPACE };

//-----------------Game Settings-----------------//

//Player:
const int SCALE = 30;
const int SPEED_PLAYER = 7;

//Helicopters:
const float SPEED_STANDARD_HELI = 8;
const float SPEED_BOMB_HELI = 18;
const int R_SCREEN = 3550;		//to flip the heli
const int L_SCREEN = 40;

// Soldiers settings
const int AK_Range = 330;
const int RPG_RANGE = 400;

//-------------------HUD Settings-----------------//

const int TEXT_POS_Y = 938;


//-----------------World List Data---------------//

//Soldiers
const int SOLDIERS_BODY_DATA = 900;
const int SOLDIERS_ARM_DATA = 950;

const int HOSTGAES_DATA = 70;