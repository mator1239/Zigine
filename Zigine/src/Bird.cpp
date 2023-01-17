#include "Bird.h"

void CBird::spawn()
{
	setTexture("bird.png");
}

void CBird::update()
{
}

void CBird::draw()
{
	_render->drawSprite(_sprite);
}
