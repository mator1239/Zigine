#include "Input.h"

Input* Input::m_Instance = nullptr;

void Input::Init()
{
	if (m_Instance)
		delete m_Instance;

	m_Instance = new Input;
}

void Input::Release()
{
	delete m_Instance;
	m_Instance = nullptr;
}

void Input::Update(sf::Event& event)
{
	m_Instance->m_PrevMouseStates = m_Instance->m_MouseStates;

	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Left:
			m_Instance->m_MouseStates[sf::Mouse::Left] = true;
			break;
		case sf::Mouse::Right:
			m_Instance->m_MouseStates[sf::Mouse::Right] = true;

			break;
		case sf::Mouse::Middle:
			m_Instance->m_MouseStates[sf::Mouse::Middle] = true;
			break;
		}
		break;
	case sf::Event::MouseButtonReleased:
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Left:
			m_Instance->m_MouseStates[sf::Mouse::Left] = false;
			break;
		case sf::Mouse::Right:
			m_Instance->m_MouseStates[sf::Mouse::Right] = false;
			break;
		case sf::Mouse::Middle:
			m_Instance->m_MouseStates[sf::Mouse::Middle] = false;
			break;
		}
		break;
	}
}
