#ifndef _MAP_H
#define _MAP_H
#include "engine/Zigine.h"
#include "engine/Entity.h"
#include "Board.h"

class Map : public Entity
{
	DECLARE_CLASS(Map, Entity)
public:
	void Spawn();
	void Draw();

	Tile& GetTile(const uint32_t id);
	bool GetTile(const vector2& position, Tile& outTile);

	inline Board& GetBoard() { return m_Board; }
private:
	Board m_Board;
};

#endif // !_MAP_H
