#include "Game.h"

/// Default constructor
Game::Game()
	: m_window(sf::VideoMode(800u, 600u, 32u), "Rising Tide", sf::Style::Default)
	, m_clock()
	, m_elapsed()
	, m_player(START_POS)
{
	srand(time(NULL));

	std::unique_ptr<Platform> platform;
	platform.reset(new Platform(m_platformTexture));
	m_platforms.push_back(std::move(platform));

	if (!m_player.loadTexture(".\\resources\\player\\player.png"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\player\\player.png";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
	loadTexture(m_platformTexture, ".\\resources\\platform\\platform.png");
	loadTexture(m_floorTexture, ".\\resources\\platform\\floor.png");
	
	m_floor.reset(new Platform(m_floorTexture, FLOOR_POS.x, FLOOR_POS.y, FLOOR_SIZE.x, FLOOR_SIZE.y));

	if (!m_music.openFromFile(".\\resources\\sounds\\the tide rises.wav"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\sounds\\the tide rises.wav";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
	m_music.play();
	m_music.setLoop(true);
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
	if (!m_music.Playing)
	{
		m_music.play();
	}
	spawnNextPlatfrom();
	removePlatfrom();
	for (std::unique_ptr<Platform>& plat : m_platforms)
	{
		plat->update(dt);
	}

	m_player.update(dt.asSeconds());

	m_floor->update(dt);

	checkcollision();

	/*TESTING GAMEFLOW*/
	if (m_player.m_position.y <= 0)
	{
		m_player.m_position.y = 0;
		for (auto& plat : m_platforms)
		{
			plat->m_fallSpeed = 12.0f;
		}
	}
	else
	{
		for (auto& plat : m_platforms)
		{
			plat->m_fallSpeed = 1.7f;
		}
	}
}

/// Main rendering loop
void Game::render()
{
	m_window.clear();
	for (std::unique_ptr<Platform>& plat : m_platforms)
	{
		plat->draw(m_window);
	}
  
	m_player.draw(m_window);

	m_floor->draw(m_window);

	m_window.display();
}

/// Spawn a platform after a set amount of time
bool Game::spawnNextPlatfrom()
{
	std::unique_ptr<Platform> platform;
	platform.reset(new Platform(m_platformTexture));

	if (m_platforms.back()->getPosition().y > 150)
	{
		m_platforms.push_back(std::move(platform));
	}
	
	return false;
}

/// Remove a platfrom when it reaches the end of the screen
void Game::removePlatfrom()
{
	if(m_platforms.front()->getOffScreen(m_window))
	{
		m_platforms.erase(m_platforms.begin());
	}
}

void Game::loadTexture(sf::Texture& texture, std::string file)
{
	if (!texture.loadFromFile(file))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
}


/// <summary>
/// Check collisions between all game elements
/// </summary>
void Game::checkcollision()
{
	for (auto & platform : m_platforms)
	{
		checkcollision(m_player, *platform);
	}
	checkcollision(m_player, *m_floor);
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
