//==============================================================================
#ifndef RIVER_H
#define RIVER_H

#include "CScroll_Player.h"
//==============================================================================

class RiverScroll : public CScroll_Player
{
public:
    void move()
    {
        src.x += velocity.x;

        if (src.x >= position.w - window_w)   // Assumes that image is greater than window width..
        {
            src.x = 0;
        }

    }
};

#endif // RIVER_H
//==============================================================================