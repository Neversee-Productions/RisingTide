#include "Game.h"

/// Default constructor
Game::Game()
	: m_window(sf::VideoMode(800u, 600u, 32u), "Rising Tide", sf::Style::Default)
	, m_clock()
	, m_elapsed()
	, m_player(START_POS)
{
	srand(time(NULL));

	sf::Texture licenceText;
	loadTexture(licenceText, ".\\resources\\backgrounds\\licence_screen.png");
	m_licenceScreen.reset(new Licence(licenceText));

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
	m_platformTexture.setSmooth(true);
	loadTexture(m_floorTexture, ".\\resources\\platform\\floor.png");
	m_floorTexture.setSmooth(true);

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
	loadTexture(m_splashScreenTexture, ".\\resources\\backgrounds\\splash_screen.png");
	m_splashScreenTexture.setSmooth(true);
	loadTexture(m_waveTexture, ".\\resources\\waves\\wave_animated.png");
	m_waveTexture.setSmooth(true);
	loadTexture(m_cliffTexture, ".\\resources\\backgrounds\\cliff.png");
	m_cliffTexture.setSmooth(true);
	loadTexture(m_skyTexture, ".\\resources\\backgrounds\\sky.png");
	m_skyTexture.setSmooth(true);
	m_skySprite.setTexture(m_skyTexture);
	m_cliffRightSprite.setTexture(m_cliffTexture);
	m_cliffLeftSprite.setTexture(m_cliffTexture);
	m_cliffLeftSprite.setScale(-1.0f, 0.5f);
	m_cliffRightSprite.setScale(1.0f, 0.5f);
	m_cliffLeftSprite.setPosition(sf::Vector2f(m_cliffLeftSprite.getGlobalBounds().width, 0.0f));
	m_cliffRightSprite.setPosition(sf::Vector2f(m_window.getSize().x - m_cliffRightSprite.getGlobalBounds().width, 0));
	m_waveSprite.setTexture(m_waveTexture);
	m_waveSprite.setPosition(-170.0f, 400.0f);
	m_floor.reset(new Platform(m_floorTexture, FLOOR_POS.x, FLOOR_POS.y, FLOOR_SIZE.x, FLOOR_SIZE.y));
	m_splashScreen.reset(new SplashScreen(m_splashScreenTexture));
	loadAnimTextures();
	m_waveAnimator.playAnimation(0, true);

	sf::Texture gameOverText;
	loadTexture(gameOverText, ".\\resources\\backgrounds\\");
	m_gameOverScreen.reset(new GameOver(gameOverText));

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
		case sf::Event::KeyPressed:
			if (m_gameState == GameState::Splash)
			{
				m_gameState = GameState::Gameplay;
			}
			break;
		default:
			break;
		}
	}
}

/// Main Logic update loop
void Game::update(sf::Time const & dt)
{
	spawnNextPlatfrom();
	removePlatfrom();
	
	switch (m_gameState)
	{
	case Game::GameState::Licence:
		if (m_licenceScreen->update(dt))
		{
			m_gameState = GameState::Splash;
		}
		break;
	case Game::GameState::Splash:
		break;
	case Game::GameState::Gameplay:
		if (spawnNextPlatfrom());
		removePlatfrom();
		for (auto& plat : m_platforms)
		{
			plat->update(dt);
		}

		m_player.update(dt.asSeconds());

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
		m_floor->update(dt);

		m_waveAnimator.update(dt);
		m_waveAnimator.animate(m_waveSprite);

		checkcollision();
		break;
	case GameState::GameOver:
		if (m_gameOverScreen->update(dt))
		{
			m_window.close();
		}
		break;
	default:
		break;
	}
}

/// Main rendering loop
void Game::render()
{
	m_window.clear();
	switch (m_gameState)
	{
	case Game::GameState::Licence:
		m_licenceScreen->draw(m_window);
		break;
	case Game::GameState::Splash:
		m_splashScreen->draw(m_window);
		break;
	case GameState::GameOver:
	case Game::GameState::Gameplay:
		m_window.draw(m_skySprite);
		for (auto& plat : m_platforms)
		{
			plat->draw(m_window);
		}
		m_player.draw(m_window);

		m_floor->draw(m_window);
		m_window.draw(m_cliffLeftSprite);
		m_window.draw(m_cliffRightSprite);
		m_window.draw(m_waveSprite);
		if (m_gameState == GameState::GameOver)
		{
			m_gameOverScreen->draw(m_window);
		}
		break;
	default:
		break;
	}
	m_window.display();
}

/// Spawn a platform after a set amount of time
bool Game::spawnNextPlatfrom()
{
	std::shared_ptr<Platform> platform;
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
		checkcollision(m_player, platform);
	}
	checkcollision(m_player, m_floor);
	checkcollision(m_player, m_cliffLeftSprite);
	checkcollision(m_player, m_cliffRightSprite);
}

void Game::checkcollision(Player & player)
{
	sf::FloatRect boxPlayer = player.getBounds();
	if (boxPlayer.top > DEATH_HEIGHT)
	{
		// player dies

	}
}

void Game::checkcollision(Player & player, std::shared_ptr<Platform> & platform)
{
	sf::FloatRect playerBox, platformBox;
	playerBox = player.getBounds();
	platformBox = platform->getBounds();

	if (player.m_velocity.y > 0.0f)
	{
		if (
			platformBox.top < playerBox.top + playerBox.height + LANDING_OFFSET &&
			platformBox.top + platformBox.height > playerBox.top + playerBox.height + LANDING_OFFSET &&
			platformBox.left + player.LEDGE_BOX_OFFSET < playerBox.left + playerBox.width &&
			platformBox.left + platformBox.width - player.LEDGE_BOX_OFFSET > playerBox.left
			)
		{
			player.land(platform, TIME_PER_UPDATE.asSeconds());
		}
	}
	player.checkland();
}

void Game::checkcollision(Player & player, sf::Sprite & wall)
{
	sf::FloatRect boxPlayer, boxWall;
	boxPlayer = player.getBounds();
	boxWall = wall.getGlobalBounds();

	if (boxWall.left + HIT_WALL_OFFSET > boxPlayer.left + boxPlayer.width ||
		boxWall.left + boxWall.width - HIT_WALL_OFFSET < boxPlayer.left)
	{
		player.wallBounce(boxWall);
	}
}

void Game::loadAnimTextures()
{
	Player::TextureCollection m_textMap;
	sf::Texture texture;

	loadTexture(texture, ".\\resources\\player\\player_idle.png");
	m_textMap[Player::AnimState::Idle] = texture;

	loadTexture(texture, ".\\resources\\player\\player_running.png");
	m_textMap[Player::AnimState::Run] = texture;

	loadTexture(texture, ".\\resources\\player\\player_jump_start.png");
	m_textMap[Player::AnimState::JumpStart] = texture;

	loadTexture(texture, ".\\resources\\player\\player_jump_loop.png");
	m_textMap[Player::AnimState::JumpLoop] = texture;

	loadTexture(texture, ".\\resources\\player\\player_fall_start.png");
	m_textMap[Player::AnimState::FallStart] = texture;

	loadTexture(texture, ".\\resources\\player\\player_fall_loop.png");
	m_textMap[Player::AnimState::FallLoop] = texture;

	m_player.addAnimTextures(m_textMap);

	loadTexture(texture, ".\\resources\\waves\\wave_animated.png");
	// wave = 1132 * 237 (2x10)
	addAnimRects(1132, 237, 2, 10);

}

void Game::addAnimRects(int width, int height, int framesWidth, int framesHeight)
{
	std::unique_ptr<thor::FrameAnimation> ptrAnimation;
	ptrAnimation.reset(new thor::FrameAnimation());
	sf::IntRect textRect(0, 0, width, height);

	for (int x = 0; x < (width * framesWidth); x += width)
	{
		for (int y = 0; y < (height * framesHeight); y += height)
		{
			textRect.left = x; textRect.top = y;
			ptrAnimation->addFrame(1.0f, textRect);
		}
	}
	m_waveAnimator.addAnimation(0, (*ptrAnimation), WAVE_DUR);
}
