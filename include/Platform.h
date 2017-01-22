#pragma once
#include "SFML\Graphics.hpp"
#include <time.h>


class Platform
{
public:
	Platform(sf::Texture texture);
	Platform(sf::Texture, float, float, float, float);

	~Platform();

	void draw(sf::RenderWindow& window);
	void update(const sf::Time& dt);

	
	float m_previousFallSpeed = 1.7f;
	bool getOffScreen(sf::RenderWindow& window);
	bool getNextPlatform();
	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float BASE_FALL_SPEED;
	static float FALL_SPEED_MULT;
	static float m_fallSpeed; /*speed of platforms*/


private: 

	void initSprite(sf::Vector2f& pos);
	sf::Vector2f m_position; /*Position of the rectangle*/

	float m_offset; /*change size of Platform*/
	float m_randX;  /*random spawingin on x axis*/

	sf::Time time;

	bool m_nextPlatform = false;
	bool m_offScreen = false;
	const sf::Time PLATFORM_PROGRESSION_TIME = sf::seconds(3.0f);


	sf::Sprite m_sprite;
	sf::Texture m_texture;

};

