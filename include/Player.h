#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

class Player
{
public:
	Player();
	void draw(sf::RenderWindow&);
	void update(double);
	sf::Vector2f getUnitVector(sf::Vector2f);
	~Player();
	sf::RectangleShape m_rectangle;
	static float const GRAVITY;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_acceleration;
	float m_coefficientOfFriction;
	float m_force;
	float m_maxForce;
	float m_forceIncrement;
};

