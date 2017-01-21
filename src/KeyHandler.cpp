#include "KeyHandler.h"

KeyHandler::KeyHandler()
: m_keyMap()
, m_previousKeyMap()
{
}

void KeyHandler::updateKey(sf::Keyboard::Key key, bool isPressed)
{
	KeyMap::const_iterator it = m_keyMap.find(key);
	if ( it != m_keyMap.end() )
	{
		m_previousKeyMap[key] = m_keyMap[key];
	}
	else
	{
		m_previousKeyMap[key] = !isPressed;
	}
	m_keyMap[key] = isPressed;
}

bool KeyHandler::isPressed(sf::Keyboard::Key key) const
{
   KeyMap::const_iterator it = m_keyMap.find(key);

   if (it != m_keyMap.end())
   {
      return it->second;
   }

   return false;
}

bool KeyHandler::isPreviouslyPressed(sf::Keyboard::Key key) const
{
	KeyMap::const_iterator it = m_previousKeyMap.find(key);

	if (it != m_previousKeyMap.end())
	{
		return it->second;
	}

	return false;
}
