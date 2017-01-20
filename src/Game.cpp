#include "Game.h"

/// Default constructor
Game::Game()
	: m_window(sf::VideoMode(800u, 600u, 32u), "Rising Tide", sf::Style::Default)
	, m_clock()
	, m_elapsed()
{
}

/// Default destructor
Game::~Game()
{
}

/// Main Entry point for Game Loop
void Game::run()
{
	m_clock.restart();
	while (m_window.isOpen())
	{
		proccessEvents();
		m_elapsed += m_clock.restart();
		while (m_elapsed > TIME_PER_UPDATE)
		{
			m_elapsed -= TIME_PER_UPDATE;
			update(m_elapsed);
		}
		render();

	}
}

/// Will process window events
void Game::proccessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}
	}
	
}

/// Main Logic update loop
void Game::update(sf::Time const & dt)
{

}

/// Main rendering loop
void Game::render()
{
	m_window.clear();

	sf::CircleShape circle(10.0f, 30u);

	circle.setPosition(sf::Vector2f(10.0f, 10.0f));
	m_window.draw(circle);

	m_window.display();
}
