#pragma once
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>
#include <SDL.h>
#include <iostream>

#include "tmxlite/Map.hpp"
#include "tmxlite/Layer.hpp"
#include "tmxlite/TileLayer.hpp"
#include "Components/SpriteComponent.h"
#include "cute_c2.h"

struct Tile
{
	SDL_Texture* texture;
	SDL_Rect sRect;
	SDL_Rect dRect;
	c2AABB collider;
	int health;
	bool dead;
};

class MapLoader
{
public:
	MapLoader();
	void load(const std::string& path, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);

	std::vector<std::shared_ptr<Tile>> getTiles() { return m_tiles; }

	std::vector<std::pair<c2v, std::string>> getWalkPoints() { return m_walkPointVector; }
	std::vector<std::pair<c2v, std::string>> getJumpPoints() { return m_jumpPointVector; }
	std::vector <std::pair<bool, c2v>*> getSpawnPoints() { return m_spawnPointVector; }

	int getWidth();
	int getHeight();

private:

	

	tmx::Map m_map;
	int m_rows;
	int m_cols;
	int m_tileWidth;
	int m_tileHeight;

	std::vector<std::pair<c2v, std::string>> m_jumpPointVector;
	std::vector<std::pair<c2v, std::string>>  m_walkPointVector;
	//Vector of spawn point pairs
	//.first is a bool to check if the spawn point has been occupied
	//.second is a c2v of x and y points
	std::vector<std::pair<bool, c2v>*> m_spawnPointVector;

	std::vector<std::shared_ptr<Tile>> m_tiles;
	
	SpriteComponent* m_sprite;

};

#endif // ! LEVEL_H

