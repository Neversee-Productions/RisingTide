#pragma once
#include "SFML\Graphics.hpp"
#include <time.h>

class Platform
{
public:
	Platform();
	Platform(float, float, float, float);

	~Platform();

	void draw(sf::RenderWindow& window);
	void update(const sf::Time& dt);

	float m_fallSpeed = 1.7f; /*speed of platforms*/

	sf::FloatRect getBounds() const;

private:
	sf::Vector2f m_position; /*Position of the rectangle*/
	sf::RectangleShape m_rectangle;
	const float SIZE = 150.0f; /*Block will alsways be 20 and expand*/

	float m_offset; /*change size of Platform*/
	float m_randX;  /*random spawingin on x axis*/

	sf::Time time;
	const sf::Time PLATFORM_SPAWN_TIME = sf::seconds(1.7f);

};

