#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{

}

SpriteComponent::SpriteComponent(int x, int y, int textureWidth, int textureHeight) : m_width(textureWidth), m_height(textureHeight)
{
	//Set default values.
	m_texture = NULL;
	m_sRect = new SDL_Rect;
	m_dRect = new SDL_Rect;
	m_scale = v2(1.0f, 1.0f);
	m_position = v2(0.0f, 0.0f);
	m_rotationAngle = 0.0f;
	m_scaledWidth = 0;
	m_scaledHeight = 0;

	//Set up source rectangle for the image
	m_sRect->x = x;
	m_sRect->y = y;
	m_sRect->w = textureWidth;
	m_sRect->h = textureHeight;
}

SpriteComponent::~SpriteComponent()
{
	freeTexture();
}

bool SpriteComponent::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	//Free our texture first
	freeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_width = loadedSurface->w;
			m_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_texture = newTexture;
	return m_texture != NULL;
}

void SpriteComponent::render(SDL_Renderer* gRenderer)
{
	//Sort out rectangles.
	m_scaledWidth = m_width * m_scale.x;
	m_scaledHeight = m_height * m_scale.y;
	
	m_dRect->w = m_scaledWidth;
	m_dRect->h = m_scaledHeight;

	SDL_RenderCopyEx(gRenderer, m_texture, m_sRect, m_dRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
}

void SpriteComponent::freeTexture()
{
	//Free texture if it exists
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}

void SpriteComponent::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void SpriteComponent::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(m_texture, blending);
}

void SpriteComponent::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_texture, alpha);
}

void SpriteComponent::setPosition(v2 position)
{
	m_dRect->x = position.x;
	m_dRect->y = position.y;
}

void SpriteComponent::move(v2 offset)
{
	m_dRect->x += offset.x;
	m_dRect->y += offset.y;
}

void SpriteComponent::setScale(v2 scalar)
{
	m_scale = scalar;
}

void SpriteComponent::setRotation(int angle)
{
	m_rotationAngle = angle;
}

void SpriteComponent::rotate(int rotationAmount)
{
	m_rotationAngle += rotationAmount;
}

v2 SpriteComponent::getPosition()
{
	return m_position;
}

v2 SpriteComponent::getScale()
{
	return m_scale;
}

int SpriteComponent::getRotation()
{
	return m_rotationAngle;
}

int SpriteComponent::getWidth()
{
	return m_scaledWidth;
}

int SpriteComponent::getHeight()
{
	return m_scaledHeight;
}