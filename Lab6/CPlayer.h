//==============================================================================
#ifndef CPLAYER_H
#define CPLAYER_H

#include <string>
#include <cstdio>

#include "mywindow.h"
#include "SDL.h"

using namespace std;
//==============================================================================

/* Implement a sprite as a player.... */
class CPlayer
{
    public:
            bool loaded;
            char imagename[255];

            SDL_Rect position;
            SDL_Rect velocity;

            CPlayer(const char image[]="",int x=0, int y=0, int vx=0, int vy=0)
            {
                strncpy_s(imagename,image,255);
                position.x = x;
                position.y = y;
                velocity.x = vx;
                velocity.y = vy;
                loaded = false;
            }

            int loadPlayer(SDL_Renderer *prenderer);
            
            void display(SDL_Renderer *prenderer);
    
    protected:
            SDL_Texture *texture;

};
#endif  // CPLAYER_H
//==============================================================================
