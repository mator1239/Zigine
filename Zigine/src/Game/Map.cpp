#include "engine/Renderer.h"

#include "Map.h"
#include <assert.h>

#define MAP_BACKGROUND_ROAD_PIXELS 370

void Map::Spawn()
{
    LoadTexture("background", "materials/background.png", true);

    vector2 boardPosition(260.0f, 85.0f);
    vector2u boardSize(740, 490);

    m_Board.Load(boardPosition, boardSize);
}

void Map::Draw()
{
    BaseClass::Draw();
#if _DEBUG
    m_Board.Draw();
#endif // _DEBUG
}

Tile& Map::GetTile(const uint32_t id)
{
    return m_Board.GetTile(id);
}

bool Map::GetTile(const vector2& position, Tile& outTile)
{
    return m_Board.GetTile(position, outTile);
}
