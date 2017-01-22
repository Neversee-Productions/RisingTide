#include "..\include\GameOver.h"


GameOver::GameOver()
{
}

GameOver::GameOver(sf::Texture texture)
	: m_texture(texture)
{
	m_sprite.setTexture(m_texture);
	m_spriteColour = sf::Color::White;
	m_spriteColour.a = 0u;
	m_sprite.setColor(m_spriteColour);
	m_sprite.setScale(0.5f, 0.5f);
	m_elapsed = sf::Time::Zero;
	leave = false;
}

void GameOver::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

bool GameOver::update(const sf::Time & dt)
{
	m_elapsed += dt;

	if (m_elapsed.asSeconds() > 3.0f)
	{
		leave = true;
	}

	if (m_spriteColour.a != 255u)
	{
		m_spriteColour.a += 1u;
		m_sprite.setColor(m_spriteColour);
	}

	return leave;
}


GameOver::~GameOver()
{
}
