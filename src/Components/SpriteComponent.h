#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include <SDL_image.h>
#include "../../cute_c2.h"
#include "../../cute_math2d.h"
#include <iostream>



class SpriteComponent : public Component
{
public:
	//Constructor
	//@param x: x point on the SOURCE asset
	//@param y: y point on the SOURCE asset
	//@param w: width of the SOURCE asset
	//@param h: height of the SOURCE asset
	SpriteComponent();
	SpriteComponent(int x, int y, int w, int h);
	~SpriteComponent();

	std::string m_tag = "SPRITE";

	std::string getType() { return m_tag; }
	
	//Optimized texture loading function
	//@param path: path to the asset
	//@param gRenderer: reference to the global renderer
	bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

	//Render method for the sprite
	//@param gRenderer: pointer to the global renderer
	void render(SDL_Renderer* gRenderer);

	//Resource freeing method for textures
	void freeTexture();

	//Color setting function
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	//Scale setting function
	//@param scalar: cute_v2
	void setScale(v2 scalar);

	//Position setting function
	//@param position: cute_v2 new position to be set
	void setPosition(v2 position);

	//Texture blending function
	//@param blending: SDL_BlendMode of the blend type you want to apply
	void setBlendMode(SDL_BlendMode blending);

	//Function to set the alpha of the sprite
	//@param alpha: Uint8 alpha value between 0 and 255;
	void setAlpha(Uint8 alpha);

	//Persistent move method
	//@param offset: cute_v2 of the amount in each axis to move by on method call
	void move(v2 offset);

	//Rotation set method
	//@param angle: angle in degrees
	void setRotation(int angle);

	//Persistent rotation method
	//@param rotationAmount: amount to add to the rotation angle each time the function is called.
	void rotate(int rotationAmount);

	//Functions for getting properties of a sprite after transformations have been applied
	v2 getPosition();
	v2 getScale();
	int getRotation();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* m_texture;
	SDL_Rect* m_sRect;
	SDL_Rect* m_dRect;

	v2 m_scale;
	v2 m_position;

	std::string m_path;
	
	int m_rotationAngle;
	int m_width;
	int m_height;

	int m_scaledWidth;
	int m_scaledHeight;


};
#endif // !SPRITECOMPONENT_H
