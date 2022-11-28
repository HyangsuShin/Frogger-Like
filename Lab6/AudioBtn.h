//==============================================================================
#ifndef AUDIO_H
#define AUDIO_H

#include "CButton.h"
#include <SDL_mixer.h>
//==============================================================================

class AudioBtn : public CButton
{
public:
	AudioBtn(const char image[] = "", int x = 0, int y = 0, int w = 0, int h = 0)
	{
		strncpy_s(imagename, image, 255);
		position.x = x;
		position.y = y;
		position.w = w;
		position.h = h;
		loaded = false;
	}

	void handleEvent(SDL_Event* e)
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
			else if (x > position.x + position.w/2)
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
					//If the music is paused
					if (Mix_PausedMusic() == 1)
					{
						//Resume the music
						Mix_ResumeMusic();
					}
					//If the music is playing
					else
					{
						//Pause the music
						Mix_PauseMusic();
					}
					break;
				}
			}
		}
	}

};
#endif // AUDIO_H
//==============================================================================