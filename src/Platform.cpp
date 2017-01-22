#include "Platform.h"

float const Platform::BASE_FALL_SPEED = 1.7f;
float Platform::FALL_SPEED_MULT = 1.0f;
float Platform::m_fallSpeed = 1.7f;

Platform::Platform(sf::Texture texture):
	m_texture(texture)
{
	m_offset = rand() % 10 +1;
	m_randX = rand() % 500 + 100;
	m_position = sf::Vector2f(m_randX, -10.0f);

	initSprite(m_position);
}


Platform::Platform(sf::Texture texture, float x, float y, float width, float height)
	: m_position(x, y)
	, m_texture(texture)
{
	m_offset = 0.0f;
	m_randX = 0.0f;
	m_sprite.setPosition(m_position);
	m_sprite.setTexture(m_texture);
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
	if (time > PLATFORM_PROGRESSION_TIME)
	{
		m_fallSpeed += 0.2;
		//m_previousFallSpeed = m_fallSpeed;
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

sf::Vector2f Platform::getPosition() const
{
	return m_position;
}

void Platform::initSprite(sf::Vector2f & pos)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_sprite.setScale(1.0f + (m_offset / 10), 1);
}
sf::FloatRect Platform::getBounds() const
{
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	rect.left = m_position.x;
	rect.top = m_position.y;
	return rect;
}




