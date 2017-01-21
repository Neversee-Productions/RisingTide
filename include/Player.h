#ifndef PLAYER
#define PLAYER

// player includes
#include "SFML\Graphics.hpp"

class Player
{
public:
	Player();
	Player(sf::Vector2f const &);

	~Player();

	void update(const double &);
	void draw(sf::RenderWindow &);

	bool loadTexture(const sf::String &);

	static float const GRAVITY;

	enum class PlayerState
	{
		Ground, Jump, Fall
	};


private:
	void processInput();

	// movement CONSTANTS
	sf::Vector2f const JUMP_FORCE = sf::Vector2f(0.0f, -8.0f);

	// size
	sf::Vector2f const SIZE = sf::Vector2f(21.0f, 64.0f);

	// pixel to Unit conversion
	const float PIXEL_TO_UNIT = 30.0f;

	// movement vectors
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	PlayerState m_playerState;

	// gravity in units
	float m_gravity;
};

#endif // !PLAYER