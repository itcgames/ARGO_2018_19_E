#include "MapLoader.h"

MapLoader::MapLoader()
{
	m_rows = 0;
	m_cols = 0;
	m_tileWidth = 0;
	m_tileHeight = 0;
}

void MapLoader::load(const std::string& path, SDL_Renderer* renderer)
{
	m_map.load(path);
	auto map_dimensions = m_map.getTileCount();
	m_rows = map_dimensions.y;
	m_cols = map_dimensions.x;


	auto tileSize = m_map.getTileSize();
	m_tileWidth = tileSize.x;
	m_tileHeight = tileSize.y;

	//Set the sprite's bounds to be the same as the 
	m_sprite = new SpriteComponent(0, 0, m_cols * m_tileWidth, m_rows * m_tileHeight);

	m_sprite->loadFromFile(m_map.getTilesets().at(0).getImagePath(), renderer);

	//Set up tile vector.
	m_tileVector.reserve(m_cols);
	m_tileVector.resize(m_cols);

	for (int i = 0; i < m_cols; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			m_tileVector[i].push_back(new Tile);
		}
	}

	auto& map_layers = m_map.getLayers();
	for (auto& layer : map_layers)
	{

		// We're only looking to render the tiles on the map, so if
		// this layer isn't a tile layer, we'll move on.
		if (layer->getType() != tmx::Layer::Type::Tile)
		{
			continue;
		}

		auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get());

		// Grab all of this layer's tiles.
		auto& layer_tiles = tile_layer->getTiles();

		for (int i = 0; i < m_cols; i++)
		{
			for (int j = 0; j < m_rows; j++)
			{
				//Get tileIndex and GID of the tile at that index
				auto tileIndex = i + (j * m_cols);
				auto currentGID = layer_tiles[tileIndex].ID;

				//Ignore empty tiles
				if (currentGID == 0)
				{
					continue;
				}

				std::cout << currentGID << std::endl;

				auto tileSetWidth = 0;
				auto tileSetHeight = 0;

				SDL_QueryTexture(m_sprite->getTexture(), NULL, NULL, &tileSetWidth, &tileSetHeight);

				m_tileVector[i].at(j)->sRect.w = m_tileWidth;
				m_tileVector[i].at(j)->sRect.h = m_tileHeight;
				m_tileVector[i].at(j)->sRect.x = (currentGID % m_map.getTilesets().at(0).getColumnCount() - 1) * m_tileWidth;
				m_tileVector[i].at(j)->sRect.y = (currentGID / m_map.getTilesets().at(0).getColumnCount()) * m_tileHeight;


				m_tileVector[i].at(j)->dRect.w = m_tileWidth;
				m_tileVector[i].at(j)->dRect.h = m_tileHeight;
				m_tileVector[i].at(j)->dRect.x = i * m_tileWidth;
				m_tileVector[i].at(j)->dRect.y = j * m_tileHeight;
			}
		}
	}
}


void MapLoader::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_cols; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			SDL_RenderCopy(renderer, m_sprite->getTexture(), &m_tileVector[i].at(j)->sRect, &m_tileVector[i].at(j)->dRect);
		}
	}
}
	
