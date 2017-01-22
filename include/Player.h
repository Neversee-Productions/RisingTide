#ifndef PLAYER
#define PLAYER

// player includes
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <memory>
#include <math.h>
#include "Thor\Animations\Animator.hpp"
#include "Thor\Animations\FrameAnimation.hpp"
#include "Platform.h"

class Player
{
public:
	Player();
	Player(sf::Vector2f const &);

	enum class AnimState
	{
		Idle, Run, JumpStart, JumpLoop, FallStart, FallLoop
	};
	
	// pointer to collection of animations
	typedef std::map<AnimState, sf::Texture> TextureCollection;

	sf::Vector2f getUnitVector(sf::Vector2f);

	float m_coefficientOfFriction;
	float m_force;
	float m_maxForce;
	float m_forceIncrement;

	~Player();

	void update(const double &);
	void draw(sf::RenderWindow &);

	bool loadTexture(const sf::String &);

	void addAnimTextures(TextureCollection);
	void addAnimRects(int, int, int, int);

	static float const GRAVITY;

	enum class PlayerState
	{
		Ground, Jump, Fall
	};

	
	PlayerState getPlayerState() const;
	sf::FloatRect getBounds() const;

	void land(std::shared_ptr<Platform> &, const double &);

	void initSprite();
	void adjustSprite();

private:
	void processInput();
	void trackAnimStates();
	void lateralMovement(float num);
  
	void initSound();
	void playSound();
  
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

	// Sounds
	sf::Sound m_jump[3];
	sf::SoundBuffer m_soundbuffer[3];
	
	// Plays stored animations
	thor::Animator<sf::Sprite, AnimState> m_animator;
	
	std::vector<std::unique_ptr<thor::FrameAnimation>> m_animations;

	TextureCollection m_textureMap;

	// ANIMATION DURATIONS //

	const sf::Time IDLE_DUR = sf::seconds(6.0f);
	const sf::Time RUN_DUR = sf::seconds(1.5f);
	const sf::Time JUMP_START_DUR = sf::seconds(2.0f);
	const sf::Time JUMP_LOOP_DUR = sf::seconds(2.0f);
	const sf::Time FALL_START_DUR = sf::seconds(2.0f);
	const sf::Time FALL_LOOP_DUR = sf::seconds(2.0f);

	// scale of the sprite
	float const SCALE = 0.2f;

	// offset to the origin
	sf::Vector2f m_offset;

	// platform that you are standing on
	std::shared_ptr<Platform> m_standPlatform;

};

#endif // !PLAYER

