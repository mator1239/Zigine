#include "Bird.h"

void CBird::spawn()
{
	setTexture("bird.png");
}

void CBird::update()
{
	_velocity.y += BIRD_GRAVITY_SPEED;
	_pos.y += _velocity.y;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		_velocity.y = -2.0f;

	if (keyboard->isKeyTapped(sf::Keyboard::Space))
		std::cout << "tapped\n";
}

void CBird::draw()
{
	_sprite.setPosition(_pos);
	_render->drawSprite(_sprite);
}
