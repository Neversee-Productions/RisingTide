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
#include "SplashScreen.h"
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
	void checkcollision(Player & player);
	void checkcollision(Player & player, std::shared_ptr<Platform> & platform);
	void checkcollision(Player & player, sf::Sprite & wall);

	void loadAnimTextures();
	void addAnimRects(int, int, int, int);

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
	// hit wall offset
	float const HIT_WALL_OFFSET = 35.0f;

	// death line
	float const DEATH_HEIGHT = 500.0f;

	// Main Game window
	sf::RenderWindow m_window;

	// internal update/render clock
	sf::Clock m_clock;

	// tracks time between frames
	sf::Time m_elapsed;


	float m_accumulatedTime = 0;

	// platform instance
	std::vector<std::shared_ptr<Platform>> m_platforms;

	// Loading texture from file
	void loadTexture(sf::Texture&, std::string);

	//
	sf::Texture m_platformTexture;
	sf::Texture m_floorTexture;
	sf::Texture m_splashScreenTexture;
  
	Player m_player;

	std::vector<std::unique_ptr<thor::Animator<sf::Sprite, int>>> m_animators;
	
	std::unique_ptr<Player::TextureCollection> m_animTextures;

	std::vector<std::unique_ptr<thor::FrameAnimation>> m_animations;
	
	thor::Animator<sf::Sprite,int> m_waveAnimator;
	thor::FrameAnimation m_waveAnimation;

	// length of wave animation
	sf::Time const WAVE_DUR = sf::seconds(1.8f);

	sf::Sprite m_waveSprite;
	sf::Texture m_waveTexture;
	sf::Sprite m_cliffRightSprite;
	sf::Sprite m_cliffLeftSprite;
	sf::Texture m_cliffTexture;
	sf::Texture m_skyTexture;
	sf::Sprite m_skySprite;

	// floor
	std::shared_ptr<Platform> m_floor;

	/*------GAME MUSIC--------*/
	sf::SoundBuffer m_musicBuffer;
	sf::Music m_music;
  
	enum class GameState {Splash, Gameplay};
	GameState m_gameState = GameState::Splash;
	std::unique_ptr<SplashScreen> m_splashScreen;
};

#endif // !GAME