#ifndef _INPUT_H
#define _INPUT_H
#include "engine/Zigine.h"
#include "engine/Renderer.h"
#include <unordered_map>

class Input
{
public:
	static void Init();
	static void Release();

	static void Update(sf::Event& event);

	static bool IsMouseButtonDown(sf::Mouse::Button button)
	{
		return (m_Instance->m_MouseStates[button] &&
			m_Instance->m_MouseStates[button] != m_Instance->m_PrevMouseStates[button]);
	}

	static bool isMouseButtonUp(sf::Mouse::Button button)
	{
		return (!m_Instance->m_MouseStates[button] &&
			m_Instance->m_MouseStates[button] == m_Instance->m_PrevMouseStates[button]);
	}

	static vector2i GetPosition() 
	{ 
		vector2i mousePosition = sf::Mouse::getPosition(*Renderer::GetWindow());
		vector2 worldPosition = Renderer::MapPixelToCoords(mousePosition);
		return { static_cast<int>(worldPosition.x), 
			static_cast<int>(worldPosition.y) };
	}
private:
	static Input* m_Instance;

	std::unordered_map<sf::Mouse::Button, bool> m_MouseStates;
	std::unordered_map<sf::Mouse::Button, bool> m_PrevMouseStates;
};

#endif // !_INPUT_H
