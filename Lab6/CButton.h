//==============================================================================
#ifndef CBUTTON_H
#define CBUTTON_H

#include <iostream>
#include <string>
#include "mywindow.h"
#include "SDL.h"

using namespace std;
//==============================================================================
class CButton
{
protected:
	bool loaded;
	void render(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);
	SDL_Texture* texture;

public:
	char imagename[255];
	
	enum CButtonSprite
	{
		ON = 0,
		OFF = 1,
		BUTTON_SPRITE_TOTAL = 2
	};

	CButtonSprite mCurrentSprite = ON;
	SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];

	SDL_Rect position;

	//Initializes internal variables
	CButton(const char image[] = "", int x = 0, int y = 0, int w = 0, int h = 0)
	{
		strncpy_s(imagename, image, 255);
		position.x = x;
		position.y = y;
		position.w = w;
		position.h = h;
		loaded = false;
	}

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Loads button sprite
	int loadPlayer(SDL_Renderer* prenderer);

	//Shows button sprite
	void display(SDL_Renderer* renderer);

};
#endif  // CBOTTON_H
//==============================================================================
