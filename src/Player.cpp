#include "Player.h"

/// <summary>
/// Default constructor
/// </summary>
Player::Player()
	: m_position(0.0f, 0.0f)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
{
}


Player::Player(sf::Vector2f const & pos)
	: m_position(pos)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
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

}

/// <summary>
/// main player draw
/// </summary>
/// <param name="window"> target draw window </param>
void Player::draw(sf::RenderWindow & window)
{

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
	return loaded;
}


