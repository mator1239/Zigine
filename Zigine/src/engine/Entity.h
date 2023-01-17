#pragma once
#include "SFML/Graphics.hpp"
#include "Zigine.h"
#include "Renderer.h"

class CBaseEntity
{
public:
	CBaseEntity();
	virtual ~CBaseEntity();

	void setPostion(sf::Vector2f pos);
	void setTexture(const std::string& name);
	void setEntityIndex(int entityIndex);

	inline sf::Texture getTexture() { return _texture; }
	inline sf::Vector2f getPosition() { return _pos; }
	inline int getEntityIndex() { return _entityIndex; }

	virtual void spawn() {}
	virtual void update() {};
	virtual void draw() {}

	void setRenderer(std::shared_ptr<Renderer> render);
protected:
	sf::Vector2f _pos;
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::shared_ptr<Renderer> _render;

	int _entityIndex = 0;
};