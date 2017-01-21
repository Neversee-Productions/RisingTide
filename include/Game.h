#ifndef GAME
#define GAME

// SFML Libraries
#include "SFML\Graphics.hpp"
// Thor Libraries
#include "Thor\Animations.hpp"
#include "Player.h"

// Game libraries
#include <string>

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

	//---------CONSTANTS---------///**/
	
	// Frames-per-second
	sf::Time const TIME_PER_UPDATE = sf::seconds(1 / 60.0f);

	// Player Start pos
	sf::Vector2f const START_POS = sf::Vector2f(400.0f, 300.0f);

	// Main Game window
	sf::RenderWindow m_window;

	// internal update/render clock
	sf::Clock m_clock;

	// tracks time between frames
	sf::Time m_elapsed;


	float m_accumulatedTime = 0;

	// platform instance
	std::vector<Platform> platform;
	sf::Time m_platformElapsedTime;
	sf::Clock m_platformElapsedClock;
  
	Player m_player;
  
	thor::Animator<sf::Sprite, int> m_animator;
	
};

#endif // !GAME