#pragma once
#include "engine/Entity.h"

// Const velocity
#define BIRD_GRAVITY_SPEED 0.06f

class KeyBrd
{
public:
	bool isKeyTapped(sf::Keyboard::Key key) {
		if (!sf::Keyboard::isKeyPressed(key)) {
			return false;
		}

		if (_tappedKeys.count(key) == 0) { 
			_tappedKeys.emplace(key, Time::getCurrentTime());
			return true;
		}
		else if ((Time::getCurrentTime() - _tappedKeys[key]) > 0.2f) {
			_tappedKeys[key] = Time::getCurrentTime();
			return true;
		}
		return false;
	}

	std::map<sf::Keyboard::Key, double> _tappedKeys;
};

class CBird : public CBaseEntity
{
public:
	virtual void spawn();
	virtual void update();
	virtual void draw();
private:
	sf::Vector2f _velocity;
	std::shared_ptr<KeyBrd> keyboard = std::make_shared<KeyBrd>();
};