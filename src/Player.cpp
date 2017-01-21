#include "Player.h"

float const Player::GRAVITY = (9.81f);

/// <summary>
/// Default constructor
/// </summary>
Player::Player()
	: m_position(0.0f, 0.0f)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
	, m_playerState(PlayerState::Ground)
	, m_gravity(GRAVITY * PIXEL_TO_UNIT)
{
}


Player::Player(sf::Vector2f const & pos)
	: m_position(pos)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
	, m_playerState(PlayerState::Ground)
	, m_gravity(GRAVITY * PIXEL_TO_UNIT)
{
}

/// <summary>
/// Default destructor
/// </summary>
Player::~Player()
{
}

/// <summary>
/// main player update loop
/// </summary>
/// <param name="dt"> delta time, time since last update </param>
void Player::update(const double & dt)
{
	processInput();
	switch (m_playerState)
	{
	case Player::PlayerState::Ground:
		break;
	case Player::PlayerState::Jump:
		m_velocity.y += m_gravity * dt;
		m_position.y += m_velocity.y * dt + (0.5f * m_gravity * (dt*dt));

		if (m_velocity.y <= -1.0f * dt)
		{
			m_playerState = PlayerState::Fall;
		}
		break;
	case Player::PlayerState::Fall:
		m_velocity.y += m_gravity * dt;
		m_position.y += m_velocity.y * dt + (0.5f * m_gravity * (dt*dt));

		break;
	default:
		break;
	}
	m_sprite.setPosition(m_position);
}

/// <summary>
/// main player draw
/// </summary>
/// <param name="window"> target draw window </param>
void Player::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

/// <summary>
/// Loads texture from passed file path
/// </summary>
/// <param name="filePath"> file path and file name </param>
/// <returns> returns true if loaded successfully, else false </returns>
bool Player::loadTexture(const sf::String & filePath)
{
	bool loaded = m_texture.loadFromFile(filePath);

	m_sprite.setTexture(m_texture);
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	m_sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	if ( SIZE.x > static_cast<float>(m_texture.getSize().x))
	{
		m_sprite.setScale(SIZE.x, m_sprite.getScale().y);
	}
	if (SIZE.y > static_cast<float>(m_texture.getSize().y))
	{
		m_sprite.setScale(m_sprite.getScale().x, SIZE.y);
	}
	
	return loaded;
}

/// <summary>
/// takes input based on current player state
/// </summary>
void Player::processInput()
{
	switch (m_playerState)
	{
	case Player::PlayerState::Ground:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_velocity.y += JUMP_FORCE.y * PIXEL_TO_UNIT;
			m_playerState = PlayerState::Jump;
		}
		break;
	case Player::PlayerState::Jump:
		break;
	case Player::PlayerState::Fall:
		break;
	default:
		break;
	}
}


