#ifndef GAME
#define GAME

// SFML Libraries
#include "SFML\Graphics.hpp"
// Thor Libraries
#include "Thor\Animations.hpp"

// Game libraries
#include <string>
#include "Player.h"
#include "Platform.h"
#include <memory>

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

	void checkcollision();
	void checkcollision(Player & player, Platform & platform);

	//---------CONSTANTS---------///**/
	
	// Frames-per-second
	sf::Time const TIME_PER_UPDATE = sf::seconds(1 / 60.0f);

	// Player Start pos
	sf::Vector2f const START_POS = sf::Vector2f(400.0f, 100.0f);

	// floor start pos
	sf::Vector2f const FLOOR_POS = sf::Vector2f(-50.0f, 110.0f);
	// floor size
	sf::Vector2f const FLOOR_SIZE = sf::Vector2f(800.0f, 200.0f);

	// landing offset
	float const LANDING_OFFSET = -10.0f;

	// Main Game window
	sf::RenderWindow m_window;

	// internal update/render clock
	sf::Clock m_clock;

	// tracks time between frames
	sf::Time m_elapsed;


	float m_accumulatedTime = 0;

	// platform instance
	std::vector<std::unique_ptr<Platform>> m_platforms;

	// Loading texture from file
	void loadTexture(sf::Texture&, std::string);

	//
	sf::Texture m_platformTexture;
	sf::Texture m_floorTexture;
  
	Player m_player;

	std::vector<std::unique_ptr<thor::Animator<sf::Sprite, int>>> m_animators;
	
	std::vector<std::unique_ptr<thor::FrameAnimation>> m_animations;
	
	// floor
	std::unique_ptr<Platform> m_floor;

};

#endif // !GAME