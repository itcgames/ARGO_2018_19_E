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
};

class MapLoader
{
public:
	MapLoader();
	void load(const std::string& path, SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);

	std::vector<std::vector<Tile*>> getTiles() { return m_tileVector; }

private:

	

	tmx::Map m_map;
	int m_rows;
	int m_cols;
	int m_tileWidth;
	int m_tileHeight;
	
	std::vector<std::vector<Tile*>> m_tileVector;

	SpriteComponent* m_sprite;

};

#endif // ! LEVEL_H

