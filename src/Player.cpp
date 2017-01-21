#include "Player.h"


float const Player::GRAVITY = 9.81f;
Player::Player() :
	m_rectangle(sf::Vector2f(30.0f, 30.0f)),
	m_coefficientOfFriction(0.3f),
	m_force(0),
	m_maxForce(300),
	m_forceIncrement(8)
{
	m_rectangle.setPosition(sf::Vector2f(400.0f, 300.0f));
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
}

void Player::update(double dt)
{
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
}
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


Player::~Player()
{
}

