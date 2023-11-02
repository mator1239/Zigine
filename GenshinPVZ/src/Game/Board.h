#ifndef _BOARD_H
#define _BOARD_H
#include "engine/Zigine.h"
#include "engine/Renderer.h"
#include "Game/entities/Plant.h"

#define DEFAULT_PVZ_ROWS 9
#define DEFAULT_PVZ_COLUMN 5

#define TILE_SIZE_X 82
#define TILE_SIZE_Y 95

#define DEFAULT_TILE_START_POSITION_X 250
#define DEFAULT_TILE_START_POSITION_Y 80

class Tile
{
public:
	Tile(vector2 position = vector2(0.0f, 0.0f), vector2u size = vector2u(0, 0));

	void SetPosition(const vector2& position);
	void SetCenter(const vector2& center);
	void SetSize(const vector2u& size);
	void SetPlant(Plant* plant);
	void SetValid(bool state);
	void SetId(const unsigned int id);

	inline bool IsValid() const { return m_IsValid; }
	inline int GetId() const { return m_Id; }
	inline vector2u GetSize() const { return m_Size; }
	inline vector2 GetPosition() const { return m_Position; }
	inline vector2u GetHalfSize() const { return vector2u(m_Size.x / 2, m_Size.y / 2); }
	inline vector2 GetCenter() const { return m_Center; }
	inline Plant* GetPlant() const { return m_Plant; }
private:
	unsigned int m_Id;
	bool m_IsValid;
	vector2u m_Size;
	vector2 m_Position;
	vector2 m_Center;
	Plant* m_Plant;
};

class Board
{
public:
	Board();

	void Load(vector2 position = vector2(0.0f, 0.0f), vector2u size = vector2u(0, 0));
	void Draw();

	void SetTile(const Tile& tile);

	bool GetTile(const vector2& position, Tile& outTile);
	Tile& GetTile(const unsigned int position);

	inline vector2u GetSize() const { return m_Size; }
	inline vector2 GetPosition() const { return m_Position; }
private:
	void LoadLevelFile();
	
	sf::Font m_Font;
	vector2u m_Size;
	vector2 m_Position;
	std::vector<Tile> m_Tiles;
};

#endif // _BOARD_H
