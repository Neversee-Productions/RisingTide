#pragma once
#include "SFML\Graphics.hpp"
class SplashScreen
{
public:
	SplashScreen();
	SplashScreen(sf::Texture texture);
	void draw(sf::RenderWindow& window);
	void update(const sf::Time& dt);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

