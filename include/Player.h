#ifndef PLAYER
#define PLAYER

// player includes
#include "SFML\Graphics.hpp"
#include <math.h>

class Player
{
public:
	Player();
	Player(sf::Vector2f const &);

	
	sf::Vector2f getUnitVector(sf::Vector2f);

	float m_coefficientOfFriction;
	float m_force;
	float m_maxForce;
	float m_forceIncrement;

	~Player();

	void update(const double &);
	void draw(sf::RenderWindow &);

	bool loadTexture(const sf::String &);

	static float const GRAVITY;

	enum class PlayerState
	{
		Ground, Jump, Fall
	};

	enum class AnimState
	{
		Idle, Run, JumpStart, JumpLoop, FallStart, FallLoop
	};
	PlayerState getPlayerState() const;
	sf::FloatRect getBounds() const;

	void land(const float &, const double &);

private:
	void processInput();
	void trackAnimStates();
	void lateralMovement(float num);
	// movement CONSTANTS
	sf::Vector2f const JUMP_FORCE = sf::Vector2f(0.0f, -8.0f);

	// size
	sf::Vector2f const SIZE = sf::Vector2f(21.0f, 64.0f);

	// pixel to Unit conversion
	const float PIXEL_TO_UNIT = 100.0f;

	// movement vectors
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
private:
	sf::Vector2f m_acceleration;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	PlayerState m_playerState;
	AnimState m_animState;
	// gravity in units
	float m_gravity;
};

#endif // !PLAYER

