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
	: m_coefficientOfFriction(0.98f)
	, m_force(0)
	, m_maxForce(300)
	, m_forceIncrement(8)
	, m_position(0.0f, 0.0f)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
	, m_playerState(PlayerState::Ground)
	, m_animState(AnimState::Idle)
	, m_gravity(GRAVITY * PIXEL_TO_UNIT)
	, m_animator(thor::Animator<sf::Sprite, AnimState>())
{
	initSound();
	initSprite();
}


Player::Player(sf::Vector2f const & pos)
	: m_coefficientOfFriction(0.98f)
	, m_force(0)
	, m_maxForce(300)
	, m_forceIncrement(8)
	, m_position(pos)
	, m_velocity(0.0f, 0.0f)
	, m_acceleration(0.0f, 0.0f)
	, m_texture()
	, m_sprite()
	, m_playerState(PlayerState::Ground)
	, m_animState(AnimState::Idle)
	, m_gravity(GRAVITY * PIXEL_TO_UNIT)
	, m_animator(thor::Animator<sf::Sprite, AnimState>())
{
	initSound();
	initSprite();
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
	m_animator.update(sf::seconds(dt));
	m_animator.animate(m_sprite);

	/* SEB */

	//acceleration = -coeffFriction*g*unitVelocity
	m_acceleration.x = -m_coefficientOfFriction * m_gravity * getUnitVector(m_velocity).x;

	
	//Velocity = Velocity + acceleration* time
	m_velocity.x += m_acceleration.x * dt;
	//Position = Position + Velocity* time + 0.5*acceleration*(time)2
	m_position.x += m_velocity.x * dt + (0.5f * m_acceleration.x * (dt * dt));
	
	/*-------------------------------------------------------------*/
	
	m_velocity.y += m_gravity * dt;
	m_position.y += m_velocity.y * dt + (0.5f * m_gravity * (dt*dt));

	processInput();
	trackAnimStates();
	switch (m_playerState)
	{
	case Player::PlayerState::Ground:
		break;
	case Player::PlayerState::Jump:
		m_velocity.y += m_gravity * dt;
		m_position.y += m_velocity.y * dt + (0.5f * m_gravity * (dt*dt));
		if (m_velocity.y >= 1.0f)
		{
			m_playerState = PlayerState::Fall;
		}
		break;
	case Player::PlayerState::Fall:

		break;
	default:
		break;
	}
	
	adjustSprite();
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

void Player::addAnimTextures(TextureCollection ptrTextureCollection)
{
	m_textureMap = TextureCollection(ptrTextureCollection);
	
	int animCount = 0;

	/** IDLE ANIMATION **/
	addAnimRects(199, 288, 5, 4);
	m_animator.addAnimation(AnimState::Idle, *(m_animations.at(animCount)), IDLE_DUR);
	animCount++;

	/** RUNNING ANIMATION **/
	addAnimRects(313, 297, 5, 4);
	m_animator.addAnimation(AnimState::Run, *(m_animations.at(animCount)), RUN_DUR);
	animCount++;

	/** JUMP START ANIMATION **/
	addAnimRects(237, 366, 5, 4);
	m_animator.addAnimation(AnimState::JumpStart, *(m_animations.at(animCount)), JUMP_START_DUR);
	animCount++;

	/** JUMP LOOP ANIMATION **/
	addAnimRects(234, 344, 5, 4);
	m_animator.addAnimation(AnimState::JumpLoop, *(m_animations.at(animCount)), JUMP_LOOP_DUR);
	animCount++;

	/** FALL START ANIMATION **/
	addAnimRects(279, 360, 5, 4);
	m_animator.addAnimation(AnimState::FallStart, *(m_animations.at(animCount)), FALL_START_DUR);
	animCount++;

	/** FALL LOOP ANIMATION **/
	addAnimRects(278, 357, 5, 4);
	m_animator.addAnimation(AnimState::FallLoop, *(m_animations.at(animCount)), FALL_LOOP_DUR);


}

void Player::addAnimRects(int width, int height, int framesWidth, int framesHeight)
{
	std::unique_ptr<thor::FrameAnimation> ptrAnimation;
	ptrAnimation.reset(new thor::FrameAnimation());
	sf::IntRect textRect(0, 0, width, height);

	for (int x = 0; x < (width * framesWidth); x += width)
	{
		for (int y = 0; y < (height * framesHeight); y += height)
		{
			textRect.left = x; textRect.top = y;
			ptrAnimation->addFrame(1.0f, textRect);
		}
	}

	m_animations.push_back(std::move(ptrAnimation));
}

/// <summary>
/// takes input based on current player state
/// </summary>
void Player::processInput()
{
	switch (m_playerState)
	{
	case Player::PlayerState::Ground:
		lateralMovement(1.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			playSound();
			m_velocity.y += JUMP_FORCE.y * PIXEL_TO_UNIT;
			m_playerState = PlayerState::Jump;
		}
		break;
	case Player::PlayerState::Jump:
		lateralMovement(0.7f);
		break;
	case Player::PlayerState::Fall:
		lateralMovement(0.7f);
		break;
	default:
		break;
	}
}

void Player::trackAnimStates()
{
	switch (m_playerState)
	{
	case Player::PlayerState::Ground:
		if (m_velocity.x != 0)
		{
			m_animState = AnimState::Run;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, true);
		}
		else
		{
			m_animState = AnimState::Idle;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, true);
		}
		break;
	case Player::PlayerState::Jump:
		
		if (m_animState == AnimState::Idle || m_animState == AnimState::Run)
		{
			m_animState = AnimState::JumpStart;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, false);
		}
		else if(m_animState == AnimState::JumpStart)
		{
			m_animState = AnimState::JumpLoop;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, true);
		}
		else if (m_velocity.y >= 0)
		{
			m_animState = AnimState::FallStart;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, false);
		}
		break;
	case Player::PlayerState::Fall:
		if (m_animState == AnimState::FallStart)
		{
			m_animState = AnimState::FallLoop;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, true);
		}
		else if (m_velocity.y == 0.0f)
		{
			m_animState = AnimState::Idle;
			if (m_animator.isPlayingAnimation())
			{
				m_animator.stopAnimation();
			}
			m_sprite.setTexture(m_textureMap[m_animState]);
			m_animator.playAnimation(m_animState, true);
		}
		break;
	default:
		break;
	}

	
	switch (m_animState)
	{
	case Player::AnimState::Idle:
		break;
	case Player::AnimState::Run:
		break;
	case Player::AnimState::JumpStart:
		break;
	case Player::AnimState::JumpLoop:
		break;
	case Player::AnimState::FallStart:
		break;
	case Player::AnimState::FallLoop:
		break;
	default:
		break;
	}
}

void Player::lateralMovement(float num)
{
	bool pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_force < m_maxForce && m_force < 0)
		{
			m_force += (m_forceIncrement * 2 * num);
		}
		else if (m_force < m_maxForce)
		{
			m_force += m_forceIncrement * num;
		}
		pressed = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_force > -m_maxForce && m_force > 0)
		{
			m_force -= (m_forceIncrement * 2 * num);
		}
		else
		{
			if (m_force > -m_maxForce)
			{
				m_force -= m_forceIncrement * num;
			}
		}
		pressed = true;
	}
	else
	{
		/*
		if (m_force > 0.0f && m_velocity.y == 0.0f)
		{
			m_force -= m_forceIncrement;
		}
		else if (m_force < 0.0f && m_velocity.y == 0.0f)
		{
			m_force += m_forceIncrement;
		}
		/**/
		m_force = 0.0f;
	}
	if (pressed)
	{
		m_velocity = (sf::Vector2f(m_force * 1.5, m_velocity.y));
	}
}

void Player::initSound()
{
	if (!m_soundbuffer[0].loadFromFile(".\\resources\\sounds\\Jump1.wav"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\sounds\\WALK.wav";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
	m_jump[0].setBuffer(m_soundbuffer[0]);

	if (!m_soundbuffer[1].loadFromFile(".\\resources\\sounds\\Jump2.wav"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\sounds\\WALK.wav";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
	m_jump[1].setBuffer(m_soundbuffer[1]);

	if (!m_soundbuffer[2].loadFromFile(".\\resources\\sounds\\Jump4.wav"))
	{
		std::string s("Error player texture (");
		s += ".\\resources\\sounds\\WALK.wav";
		s += ") was not loaded";
		throw std::exception(s.c_str());
	}
	m_jump[2].setBuffer(m_soundbuffer[2]);
}

void Player::playSound()
{
	int random = rand() % 3 + 1;

	switch (random)
	{
	case 1:
		m_jump[0].play();
		break;
	case 2:
		m_jump[1].play();
		break;
	case 3:
		m_jump[2].play();
		break;
	default:
		break;
	}
}
	
Player::PlayerState Player::getPlayerState() const
{
	return m_playerState;
}

sf::FloatRect Player::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

void Player::land(const float & landHeight, const double & dt)
{
	m_playerState = PlayerState::Ground;
	m_velocity.y = (landHeight - m_sprite.getGlobalBounds().height) * dt;
}

void Player::initSprite()
{
	m_sprite.setScale(SCALE, SCALE);
	sf::FloatRect rect = m_sprite.getGlobalBounds();
	m_offset.x = rect.width / 2.0f;
	m_offset.y = rect.height / 2.0f;
	m_sprite.setOrigin(m_offset);
}

void Player::adjustSprite()
{
	if (m_velocity.x < 0)
	{
		m_sprite.setScale(-SCALE, SCALE);
		m_offset.x = m_sprite.getGlobalBounds().width;
		m_offset.x /= 2.0f;
		m_offset.y = m_sprite.getGlobalBounds().height;
		m_offset.y /= 2.0f;
		m_sprite.setOrigin(m_offset);
		m_sprite.setPosition(m_position.x + m_offset.x, m_position.y + m_offset.y);
	}
	else
	{
		m_sprite.setScale(SCALE, SCALE);
		m_offset.x = m_sprite.getGlobalBounds().width;
		m_offset.x /= 2.0f;
		m_offset.y = m_sprite.getGlobalBounds().height;
		m_offset.y /= 2.0f;
		m_sprite.setOrigin(m_offset);
		m_sprite.setPosition(m_position.x - m_offset.x, m_position.y + m_offset.y);
	}
}
