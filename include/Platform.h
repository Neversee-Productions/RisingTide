#pragma once
#include "SFML\Graphics.hpp"
#include <time.h>

class Platform
{
public:
	Platform(sf::Texture texture);
	Platform();
	Platform(float, float, float, float);

	~Platform();

	void draw(sf::RenderWindow& window);
	void update(const sf::Time& dt);

	float m_fallSpeed = 1.7f; /*speed of platforms*/
	bool getOffScreen(sf::RenderWindow& window);
	bool getNextPlatform();
	sf::FloatRect getBounds() const;
private: 

	void initSprite(sf::Vector2f& pos);
	sf::Vector2f m_position; /*Position of the rectangle*/
	
private:
	sf::Vector2f m_position; /*Position of the rectangle*/

	float m_offset; /*change size of Platform*/
	float m_randX;  /*random spawingin on x axis*/

	sf::Time time;
	const sf::Time PLATFORM_SPAWN_TIME = sf::seconds(1.7f);

	bool m_nextPlatform = false;
	bool m_offScreen = false;


	sf::Sprite m_sprite;
	sf::Texture m_texture;

};

