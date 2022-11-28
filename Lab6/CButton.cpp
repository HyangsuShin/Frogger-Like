//==============================================================================
#include "CButton.h"
//==============================================================================

void CButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < position.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > position.x + position.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < position.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > position.y + position.h)
		{
			inside = false;
		}

		//Mouse is inside button
		if (inside)
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (mCurrentSprite == ON)
				{
					mCurrentSprite = OFF;
				}
				else if (mCurrentSprite == OFF)
				{
					mCurrentSprite = ON;
				}
				break;
			}
		}
	}
}

//==============================================================================

int CButton::loadPlayer(SDL_Renderer* renderer)
{
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(imagename);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", imagename, SDL_GetError());
        return (-1);
    }
	else
	{
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = i*position.w;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = position.w;
			gSpriteClips[i].h = position.h;
		}
	}

    position.w = temp->w;
    position.h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8*)temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint16*)temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16*)temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint32*)temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32*)temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

//==============================================================================

void CButton::render(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center)
{	
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { position.x,position.y, position.w, position.h };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, SDL_FLIP_NONE);
}

//==============================================================================

void CButton::display(SDL_Renderer* renderer)
{
	//Show current button sprite
	render(renderer, &gSpriteClips[mCurrentSprite]);
}