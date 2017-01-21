#include "Player.h"


/// <summary>
/// Gets unit vector using the formula (the vector divided by its length)
/// x = x / sqrt(x*x + y*y)
/// y = y / sqrt(x*x + y*y)
/// </summary>
/// <param name=""></param>
/// <returns></returns>
sf::Vector2f Player::getUnitVector(sf::Vector2f vector)
{
	float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (magnitude != 0)
	{
		return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
	}
	else
	{
		return sf::Vector2f(0, 0);
	}
}

float const Player::GRAVITY = (9.81f);

/// <summary>
/// Default constructor
/// </summary>
Player::Player()
	: m_rectangle(sf::Vector2f(30.0f, 30.0f))
	, m_coefficientOfFriction(0.3f)
	, m_force(0)
	, m_maxForce(300)
	, m_forceIncrement(8)
	, m_position(0.0f, 0.0f)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
	, m_playerState(PlayerState::Ground)
	, m_gravity(GRAVITY * PIXEL_TO_UNIT)
{
		m_rectangle.setPosition(sf::Vector2f(400.0f, 300.0f));
}


Player::Player(sf::Vector2f const & pos)
	: m_rectangle(sf::Vector2f(30.0f, 30.0f))
	, m_coefficientOfFriction(0.3f)
	, m_force(0)
	, m_maxForce(300)
	, m_forceIncrement(8)
	, m_position(pos)
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
	/* SEB */
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_force < m_maxForce && m_force < 0)
		{
			m_force += (m_forceIncrement * 2);
		}
		else if (m_force < m_maxForce)
		{
			m_force += m_forceIncrement;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_force > -m_maxForce && m_force > 0)
		{
			m_force -= (m_forceIncrement * 2);
		}
		else
		{
			if (m_force > -m_maxForce)
			{
				m_force -= m_forceIncrement;
			}
		}
	}
	else
	{
		if (m_force > 0)
		{
			m_force -= m_forceIncrement;
		}
		else if (m_force < 0)
		{
			m_force += m_forceIncrement;
		}
	}
	m_velocity = (sf::Vector2f(m_force * 1.5, m_velocity.y));
	//acceleration = -coeffFriction*g*unitVelocity
	m_acceleration = -m_coefficientOfFriction * GRAVITY * getUnitVector(m_velocity).x;
	//Velocity = Velocity + acceleration* time
	m_velocity.x += m_acceleration * dt;
	//Position = Position + Velocity* time + 0.5*acceleration*(time)2
	m_rectangle.setPosition(m_position.x += m_velocity.x * dt + (0.5 * m_acceleration * (dt * dt)), m_rectangle.getPosition().y);
	
	/*-------------------------------------------------------------*/
	
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
