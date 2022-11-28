//==============================================================================
#ifndef CAR_H
#define CAR_H

#include "CPlayer.h"
#include <algorithm>
//==============================================================================
class Car : public CPlayer {
public:
    Car(const char image[] = "", int x = 0, int y = 0, int vx = 0, int vy = 0)
    {
        strncpy_s(imagename, image, 255);
        position.x = x;
        position.y = y;
        velocity.x = vx;
        velocity.y = vy;
        loaded = false;
    }
    void move() {

        SDL_Rect* p;
        SDL_Rect* v;

        p = &position;
        v = &velocity;

        p->x += v->x;

        if (p->x >= window_w + p->w)
        {
            p->x = 0 - p->w;
        }
        if (p->x < 0 - p->w && v->x < 0)
        {
            p->x = window_w;
        }
    }

    void stop() {
        SDL_Rect* v;

        v = &velocity;

        v->x = 0;
    }
};
#endif  // CAR_H
//==============================================================================