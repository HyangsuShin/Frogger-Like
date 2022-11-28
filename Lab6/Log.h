//==============================================================================
#ifndef LOG_H
#define LOG_H

#include "CPlayer.h"
#include "CApp.h"
//==============================================================================
class Log : public CPlayer {
public:
    Log(const char image[] = "", int x = 0, int y = 0, int vx = 0, int vy = 0)
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
            p->x = 0-(p->w);
        }
    }

    void stop() {
        SDL_Rect* v;

        v = &velocity;

        v->x = 0;
    }
};
#endif  // LOG_H
//==============================================================================