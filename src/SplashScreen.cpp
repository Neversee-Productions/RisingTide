#include "SplashScreen.h"



SplashScreen::SplashScreen()
{
}

SplashScreen::SplashScreen(sf::Texture texture) :
	m_texture(texture)
{
	m_sprite.setTexture(m_texture);
}

void SplashScreen::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void SplashScreen::update(const sf::Time & dt)
{
	
}
