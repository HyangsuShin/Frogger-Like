//==============================================================================
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "CPlayer.h"
//==============================================================================

class Background : public CPlayer
{
public:
    Background(const char image[] = "", int x = 0, int y = 0)
    {
        strncpy_s(imagename, image, 255);
        position.x = x;
        position.y = y;
        loaded = false;
    }
};

#endif // BACKGROUND_H
//==============================================================================
