//==============================================================================
#include "CScroll_Player.h"
//==============================================================================

CScroll_Player::CScroll_Player()
{
    //constructor
}

CScroll_Player::~CScroll_Player()
{
    //destructor
}

//==============================================================================

void CScroll_Player::display(SDL_Renderer *prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);
}

//==============================================================================

int CScroll_Player::loadPlayer(SDL_Renderer *prenderer)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);

    destscr.x = 0;
    destscr.y = 60;
    destscr.w = window_w;
    destscr.h = 310;
    
    velocity.x = 1; //velocity to scrolls image left to right
    velocity.y = 0; 
    
    return (retval);
}

//==============================================================================

void CScroll_Player::move()
{
    src.x += velocity.x;

    if (src.x >= position.w - window_w)   // Assumes that image is greater than window width..
    {
        src.x = 0;
    }

}
//==============================================================================