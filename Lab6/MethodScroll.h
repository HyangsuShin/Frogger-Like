//==============================================================================
#ifndef METHOD_H
#define METHOD_H

#include "CScroll_Player.h"
//==============================================================================

class MethodScroll : public CScroll_Player
{
public:
    int loadPlayer(SDL_Renderer* prenderer)
    {
        int retval;

        retval = CPlayer::loadPlayer(prenderer);

        destscr.x = 0;
        destscr.y = 0;
        destscr.w = window_w;
        destscr.h = window_h;

        velocity.x = 0;
        velocity.y = 1; //velocity to scrolls image left to right

        return (retval);
    }

    void move()
    {
        src.y += velocity.y;

        if (src.y >= position.h - window_h)   // Assumes that image is greater than window width..
        {
            src.y = 0;
        }

    }
};

#endif // METHOD_H
//==============================================================================