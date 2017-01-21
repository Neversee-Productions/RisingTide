#ifndef KEY_HANDLER
#define KEY_HANDLER

#include <map>
#include <SFML/Window/Keyboard.hpp>

/// <summary>
/// @brief class to manage simultaneous key input in SFML.
/// 
/// </summary>
class KeyHandler
{
public:

	/// <summary>
	/// @brief default constructor.
	/// 
	/// create an empty mapping of keypresses to bool
	/// </summary>
	KeyHandler();

	/// <summary>
	/// @brief updates key pressed status.
	/// 
	/// Assigns a value of true or false to the specified key. 
	/// </summary>
	/// <param name="key">An SFML key</param>
	/// <param name="isPressed">true if key pressed (false otherwise)</param>
	void updateKey(sf::Keyboard::Key key, bool isPressed);

	/// <summary>
	/// @brief checks if a specific key was pressed.
	/// 
	/// Searches the map to check if the specified key was pressed. 
	/// </summary>
	/// <param name="key">An SFML key</param>
	/// <returns>true if specified key was pressed, false otherwise</returns>
	bool isPressed(sf::Keyboard::Key key) const;

	bool isPreviouslyPressed(sf::Keyboard::Key key) const;

private:

	// KeyMap is an alias for a std::map of sf::Keyboard::Key to bool
	typedef std::map<sf::Keyboard::Key, bool> KeyMap;
	KeyMap m_keyMap;
	KeyMap m_previousKeyMap;
};

#endif // !KEY_HANDLER