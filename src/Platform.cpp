#include "Platform.h"


Platform::Platform() 
{
	m_offset = rand() % 100 - 50;
	m_randX = rand() % 500 + 100;
	m_position = sf::Vector2f(m_randX, -100);
	m_rectangle.setPosition(sf::Vector2f(m_position));
	

	m_rectangle.setSize(sf::Vector2f(SIZE + m_offset, 30));

	sf::FloatRect rect = m_rectangle.getGlobalBounds();

}


Platform::Platform(float x, float y, float width, float height)
	: m_position(x, y)
{
	m_offset = 0.0f;
	m_randX = 0.0f;
	m_rectangle.setSize(sf::Vector2f(width, height));
	m_rectangle.setPosition(m_position);
}


Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
}

void Platform::update(const sf::Time& dt)
{
	time += dt;
	if (time > PLATFORM_SPAWN_TIME)
	{

	}
	m_rectangle.setPosition(m_position);
	m_position.y+=m_fallSpeed;
}

sf::FloatRect Platform::getBounds() const
{
	sf::FloatRect rect = m_rectangle.getGlobalBounds();
	rect.left = m_position.x;
	rect.top = m_position.y;
	return rect;
}




