#include "Board.h"
#include "engine/utils/pugiconfig.hpp"
#include "engine/utils/pugixml.hpp"

Board::Board()
{
	m_Font.loadFromFile("game/materials/fonts/arial_bold.ttf");
}

void Board::Load(vector2 position, vector2u size)
{
	m_Position = position;
	m_Size = size;

	for (unsigned int y = 0; y < DEFAULT_PVZ_COLUMN; y++)
	{
		int tileY = (TILE_SIZE_Y * y);
		for (unsigned int x = 0; x < DEFAULT_PVZ_ROWS; x++)
		{
			int tileX = (TILE_SIZE_X * x);

			vector2 tilePosition((float)tileX + DEFAULT_TILE_START_POSITION_X,
				(float)tileY + DEFAULT_TILE_START_POSITION_Y);
			vector2u tileSize(TILE_SIZE_X, TILE_SIZE_Y);
			Tile newTile(tilePosition, tileSize);

			vector2u tileHalfSize = newTile.GetHalfSize();
			vector2 tileCenter(tilePosition.x + tileHalfSize.x, tilePosition.y + tileHalfSize.y);
			newTile.SetCenter(tileCenter);
			newTile.SetValid(true);
			newTile.SetId(m_Tiles.size());

			m_Tiles.push_back(newTile);
		}
	}

	LoadLevelFile();
}

void Board::Draw()
{
	for (unsigned int i = 0; i < m_Tiles.size(); i++)
	{
		Tile tile = m_Tiles[i];

		vector2 size(tile.GetSize().x, tile.GetSize().y);

		sf::CircleShape center(3.0f);
		center.setPosition(tile.GetCenter());
		center.setFillColor(sf::Color(255, 0, 0));

		std::string id = std::to_string(i + 1);
		sf::Text textId;
		textId.setString(id.c_str());
		textId.setPosition(center.getPosition());
		textId.setFont(m_Font);

		Renderer::DrawPrimitive(center);
		Renderer::DrawPrimitive(textId);
	}
}

bool Board::GetTile(const vector2& position, Tile& outTile)
{
	Tile closest;
	float minDistance = FLT_MAX;

	for (unsigned int i = 0; i < m_Tiles.size(); i++)
	{
		Tile tile = m_Tiles[i];
		float distance = LengthSqr((tile.GetCenter() - position));

		if (distance < minDistance)
		{
			minDistance = distance;
			closest = tile;
		}
	}

	vector2 min = closest.GetPosition();
	vector2 max = min + (vector2)closest.GetSize();

	if (position.x >= min.x && position.x <= max.x
		&& position.y >= min.y && position.y <= max.y)
	{
		outTile = closest;
		return true;
	}

	outTile = Tile();
	outTile.SetValid(false);
	return false;
}

Tile& Board::GetTile(const unsigned int position)
{
	return m_Tiles[position];
}

template <class T>
bool IsVectorEmpty(const sf::Vector2<T> vector)
{
	return (vector.x == 0 && vector.y == 0);
}

void Board::LoadLevelFile()
{
	pugi::xml_document document;
	document.load_file("game/materials/levels.xml");

	pugi::xml_node levels = document.child("levels");
	for (pugi::xml_node level = levels.first_child(); level; level = level.next_sibling())
	{
		pugi::xml_node tiles = level.child("tiles");
		vector2 globalCenterMove(level.attribute("center_x").as_float(),
			level.attribute("center_y").as_float());

		for (pugi::xml_node tile = tiles.first_child(); tile; tile = tile.next_sibling())
		{
			vector2 centerMove(tile.attribute("center_x").as_float(),
				tile.attribute("center_y").as_float());
			vector2u size(tile.attribute("size_x").as_uint(),
				tile.attribute("size_y").as_uint());
			int id = tile.attribute("id").as_int() - 1;

			Tile mapTile = m_Tiles[id];
			if (IsVectorEmpty(size)) 
				size = mapTile.GetSize();

			if (centerMove.x == 0)
				centerMove.x = globalCenterMove.x;
			if (centerMove.y == 0)
				centerMove.y = globalCenterMove.y;

			mapTile.SetPosition(mapTile.GetPosition() + centerMove);
			mapTile.SetCenter(mapTile.GetCenter() + centerMove);
			mapTile.SetSize(size);
			m_Tiles[id] = mapTile;
		}
	}
}

void Board::SetTile(const Tile& tile)
{
	m_Tiles[tile.GetId()] = tile;
}

Tile::Tile(vector2 position, vector2u size)
	: m_Position(position)
	, m_Size(size)
	, m_Plant(nullptr)
	, m_IsValid(false)
	, m_Id(0)
{
}

void Tile::SetPosition(const vector2& position)
{
	m_Position = position;
}

void Tile::SetCenter(const vector2& center)
{
	m_Center = center;
}

void Tile::SetSize(const vector2u& size)
{
	m_Size = size;
}

void Tile::SetPlant(Plant* plant)
{
	m_Plant = plant;
}

void Tile::SetValid(bool state)
{
	m_IsValid = state;
}

void Tile::SetId(const unsigned int id)
{
	m_Id = id;
}
