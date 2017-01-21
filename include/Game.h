#ifndef GAME
#define GAME

// SFML Libraries
#include "SFML\Graphics.hpp"
// Thor Libraries
#include "Thor\Animations.hpp"

#include "Platform.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void proccessEvents();
	void update(sf::Time const &);
	void render();

	bool spawnNextPlatfrom();
	void removePlatfrom();

	// Frames-per-second
	sf::Time const TIME_PER_UPDATE = sf::seconds(1 / 60.0f);

	// Main Game window
	sf::RenderWindow m_window;

	// internal update/render clock
	sf::Clock m_clock;

	// tracks time between frames
	sf::Time m_elapsed;

	float m_accumulatedTime = 0;

	thor::Animator<sf::Sprite, int> m_animator;

	// platform instance
	std::vector<Platform> platform;
	sf::Time m_platformElapsedTime;
	sf::Clock m_platformElapsedClock;
};

#endif // !GAME