#include "Platform.h"


Platform::Platform() 
{
	m_offset = rand() % 100 - 50;
	m_randX = rand() % 500 + 100;
	m_position = sf::Vector2f(m_randX, -100);
	m_rectangle.setPosition(sf::Vector2f(m_position));
	

	m_rectangle.setSize(sf::Vector2f(SIZE + m_offset, 30));

	sf::FloatRect rect = m_rectangle.getGlobalBounds();
	m_rectangle.setOrigin(rect.width / 2.0f, rect.height / 2.0f);

}


Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
}

void Platform::update()
{
	m_rectangle.setPosition(m_position);
	m_position.y+=m_fallSpeed;
}




