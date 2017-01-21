#include "Platform.h"


Platform::Platform(sf::Texture texture):
	m_texture(texture)
{
	m_offset = rand() % 10 +1;
	m_randX = rand() % 500 + 100;
	m_position = sf::Vector2f(m_randX,0);

	initSprite(m_position);
}


Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Platform::update(const sf::Time& dt)
{
	time += dt;
	if (time > PLATFORM_SPAWN_TIME)
	{
		m_nextPlatform = true;
	}
	m_sprite.setPosition(m_position);
	m_position.y+=m_fallSpeed;
}

/// Check if platform is off screen
bool Platform::getOffScreen(sf::RenderWindow& window)
{
	if (m_position.y > window.getSize().y + 50)
	{
		return true;
	}
	return m_offScreen;
}

///returns a bool representing if you can spawn the next platform.
bool Platform::getNextPlatform()
{
	return m_nextPlatform;
}

void Platform::initSprite(sf::Vector2f & pos)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_sprite.setScale(1.0f + (m_offset / 10), 1);
}




