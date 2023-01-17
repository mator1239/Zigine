#include "Entity.h"

CBaseEntity::CBaseEntity()
	: _entityIndex(NULL)
{
}

CBaseEntity::~CBaseEntity()
{
}

void CBaseEntity::setPostion(sf::Vector2f pos)
{
	_pos = pos;
}

void CBaseEntity::setTexture(const std::string &name)
{
	_texture.loadFromFile("materials/" + name);

	_sprite.setPosition(_pos.x, _pos.y);
	_sprite.setTexture(_texture);
}

void CBaseEntity::setEntityIndex(int entityIndex)
{
	_entityIndex = entityIndex;
}

void CBaseEntity::setRenderer(std::shared_ptr<Renderer> render)
{
	_render = std::move(render);
}
