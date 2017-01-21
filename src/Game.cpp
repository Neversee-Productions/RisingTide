#include "Game.h"

/// Default constructor
Game::Game()
	: m_window(sf::VideoMode(800u, 600u, 32u), "Rising Tide", sf::Style::Default)
	, m_clock()
	, m_elapsed()
	, m_player(START_POS)
{
	srand(time(NULL));

	platform.push_back(Platform());

	if (!m_player.loadTexture(".\\resources\\player\\player.png"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\player\\player.png";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
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
			update(TIME_PER_UPDATE);
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
	while (spawnNextPlatfrom())
	{
		platform.push_back(Platform());
	}
	for (auto& plat : platform)
	{
		plat.update(dt);
	}
  
	m_player.update(dt.asSeconds());
}

/// Main rendering loop
void Game::render()
{
	m_window.clear();
	for (Platform& plat : platform)
	{
		plat.draw(m_window);
	}
  m_player.draw(m_window);
  
	m_window.display();
}

bool Game::spawnNextPlatfrom()
{
	m_platformElapsedTime = m_platformElapsedClock.restart();
	m_accumulatedTime += m_platformElapsedTime.asSeconds();
	if (m_accumulatedTime > 1.5)
	{
		m_accumulatedTime = 0;
		return true;
	}
	
	return false;
}

void Game::removePlatfrom()
{
	
}
