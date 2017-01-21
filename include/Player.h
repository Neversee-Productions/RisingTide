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

private:
	// movement vectors
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

};

#endif // !PLAYER