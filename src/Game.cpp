#include "Game.h"

/// Default constructor
Game::Game()
	: m_window(sf::VideoMode(800u, 600u, 32u), "Rising Tide", sf::Style::Default)
	, m_clock()
	, m_elapsed()
	, m_player(START_POS)
	, m_floor(FLOOR_POS.x, FLOOR_POS.y, FLOOR_SIZE.x, FLOOR_SIZE.y)
{
	srand(time(NULL));

	m_platforms.push_back(Platform());

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
		m_platforms.push_back(Platform());
	}
	for (auto& plat : m_platforms)
	{
		plat.update(dt);
	}

	m_player.update(dt.asSeconds());

	m_floor.update(dt);

	checkcollision();
}

/// Main rendering loop
void Game::render()
{
	m_window.clear();
	for (Platform& plat : m_platforms)
	{
		plat.draw(m_window);
	}
	m_player.draw(m_window);

	m_floor.draw(m_window);

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

/// <summary>
/// Check collisions between all game elements
/// </summary>
void Game::checkcollision()
{
	for (auto & platform : m_platforms)
	{
		checkcollision(m_player, platform);
	}
	checkcollision(m_player, m_floor);
}

void Game::checkcollision(Player & player, Platform & platform)
{
	sf::FloatRect playerBox, platformBox;
	playerBox = player.getBounds();
	platformBox = platform.getBounds();

	if (player.m_velocity.y > 0.0f)
	{
		if (
			platformBox.top < playerBox.top + playerBox.height + LANDING_OFFSET &&
			platformBox.top + platformBox.height > playerBox.top + playerBox.height + LANDING_OFFSET &&
			platformBox.left < playerBox.left + playerBox.width &&
			platformBox.left + platformBox.width > playerBox.left
			)
		{
			player.land(platformBox.top + LANDING_OFFSET, TIME_PER_UPDATE.asSeconds());
		}
	}
}
