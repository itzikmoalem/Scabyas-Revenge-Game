#pragma once
#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "MyContactListener.h"

class AssetManager
{
private:
	static AssetManager* instance;

	// Private constructor so that no objects can be created.
	AssetManager();
	std::map<int, sf::Texture> m_textures; // map to texture load and extraction
	std::map<int, sf::Font> m_fonts; // map to font load and extraction
	std::map<int, sf::SoundBuffer> m_sounds; // map to sound load and extraction
	sf::Context context; // to use openGL functions without an active window
	std::ifstream m_Levels;
	MyContactListener m_myContactListenerInstance;

public:
	static AssetManager* getInstance();

	void OpenFile(const std::string name);
	std::ifstream& GetLevels();

	void LoadTexture(const int name, const std::string FileName);
	sf::Texture& GetTexture(const int name);

	void LoadFont(const int name, const std::string FileName);
	sf::Font& GetFont(const int name);

	void LoadSound(const int name, const std::string FileName);
	sf::SoundBuffer& GetSound(const int name);

	void LoadAssets();

	MyContactListener& GetContactListener();

};

