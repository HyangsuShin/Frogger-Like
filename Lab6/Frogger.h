//==============================================================================
#ifndef FROGGER_H
#define FROGGER_H

#include "CPlayer.h"
//==============================================================================
class Frogger : public CPlayer {
public:
    double degree;

    Frogger(const char image[] = "", int x = 0, int y = 0, int vx = 0, int vy = 0)
    {
        strncpy_s(imagename, image, 255);
        position.x = x;
        position.y = y;
        velocity.x = vx;
        velocity.y = vy;
        loaded = false;
        degree = 0;
    }

	void move(/*SDL_Joystick* joy*/) {
        SDL_Rect* p;
        SDL_Rect* v;

        p = &position;
        v = &velocity;

        p->x += v->x;

        if (p->y > window_h - 96)
        {
            p->y = window_h - 96;
        }

        /*if (Event->type == SDL_QUIT) {
            Running = false;
        }*/
	}

    void display(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center)
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { position.x, position.y, position.w, position.h};

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        //Render to screen
        SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, SDL_FLIP_NONE);
    }

};
#endif  // FROGGER_H
//==============================================================================