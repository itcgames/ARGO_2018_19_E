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

	//Remove old tiles
	int tileVectorSize = m_tiles.size();
	for (int i = 0; i < tileVectorSize; i++)
	{
		if (!m_tiles.empty())
		{
			m_tiles.pop_back();
		}
	}

	//Remove old waypoints
	int walkPointVectorSize = m_walkPointVector.size();
	for (int i = 0; i < walkPointVectorSize; i++)
	{
		if (!m_walkPointVector.empty())
		{
			m_walkPointVector.pop_back();
		}
	}

	int jumpPointVectorSize = m_jumpPointVector.size();
	for (int i = 0; i < jumpPointVectorSize; i++)
	{
		if (!m_jumpPointVector.empty())
		{
			m_jumpPointVector.pop_back();
		}
	}

	int spawnPointVectorSize = m_spawnPointVector.size();
	{
		for (int i = 0; i < spawnPointVectorSize; i++)
		{
			if (!m_spawnPointVector.empty())
			{
				m_spawnPointVector.pop_back();
			}
		}
	}

	auto& map_layers = m_map.getLayers();
	for (auto& layer : map_layers)
	{

		//points
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			auto & objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();

		
			for (auto & object : objects) {

				if (layer->getName() == "JumpPoints")
				{
					c2v position = c2v{ object.getPosition().x, object.getPosition().y };
					std::string name = object.getName();
					m_jumpPointVector.push_back(std::make_pair(position, name));
				}

				if (layer->getName() == "WalkPoints")
				{
					c2v position = c2v{ object.getPosition().x, object.getPosition().y };
					std::string name = object.getName();
					m_walkPointVector.push_back(std::make_pair(position, name));
				}

				//Allocate spawn points for players, the boolean in the pair signifies whether or not a player has
				//taken that spawn or not.
				if (layer->getName() == "PlayerSpawnPoints")
				{
					c2v position = c2v{ object.getPosition().x, object.getPosition().y };
					m_spawnPointVector.push_back(new std::pair<bool, c2v>(false, position));
				}
				
			}
		}
	
		//std::cout << m_pointVector.size();

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

				auto tileSetWidth = 0;
				auto tileSetHeight = 0;

				//SDL_QueryTexture(m_sprite->getTexture(), NULL, NULL, &tileSetWidth, &tileSetHeight);

				std::shared_ptr<Tile> temp = std::make_shared<Tile>();

				temp->sRect.w = m_tileWidth;
				temp->sRect.h = m_tileHeight;
				temp->sRect.x = (currentGID % m_map.getTilesets().at(0).getColumnCount() - 1) * m_tileWidth;
				temp->sRect.y = (currentGID / m_map.getTilesets().at(0).getColumnCount()) * m_tileHeight;

				temp->dead = false;
				temp->health = 10;

				temp->dRect.w = m_tileWidth;
				temp->dRect.h = m_tileHeight;
				temp->dRect.x = i * m_tileWidth;
				temp->dRect.y = j * m_tileHeight;

				float x = temp->dRect.x;
				float y = temp->dRect.y;
				float w = temp->dRect.w;
				float h = temp->dRect.h;

				temp->collider = c2AABB{ c2v{x, y}, c2v{x + w, y + h} };

				m_tiles.push_back(temp);

			}
		}
	}
}


void MapLoader::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		SDL_RenderCopy(renderer, m_sprite->getTexture(), &m_tiles.at(i)->sRect, &m_tiles.at(i)->dRect);
		if (m_tiles.at(i)->dead == true)
		{
			m_tiles.erase(m_tiles.begin() + i);
		}
	}
}

int MapLoader::getWidth()
{
	return m_cols * m_tileWidth;
}

int MapLoader::getHeight()
{
	return m_rows * m_tileHeight;
}
	
