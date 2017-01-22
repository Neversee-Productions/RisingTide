#pragma once
#include "SFML\Graphics.hpp"

class Licence
{
public:
	Licence();
	Licence(sf::Texture texture);
	void draw(sf::RenderWindow& window);
	bool update(const sf::Time& dt);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Color m_spriteColour;
	sf::Time m_elapsed;
	bool leave;
};

