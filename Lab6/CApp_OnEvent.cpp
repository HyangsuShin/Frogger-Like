//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {

    switch (Event->type) {
    case SDL_QUIT:
        Running = false;
        break;
    case SDL_KEYDOWN:
        switch (Event->key.keysym.sym)
        {
        case SDLK_ESCAPE:    // "Esc" to exit out of the game
            Running = false;
            break;
        case SDLK_p:        // "P" to restart the game
        {
            Running = false;
            Restart = true;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            window = NULL;
            renderer = NULL;
        }
        case SDLK_RETURN:   // "Enter" to start the game
        {
            Start = true;
            if (soundEffect.mCurrentSprite == soundEffect.ON)
            Mix_PlayChannel(-1, gStart, 0);
        }
        break;
        case SDLK_UP:       // frogger go forward
        {
            frogger.degree = 0;
            frogger.position.y -= 48;
            if (soundEffect.mCurrentSprite == soundEffect.ON)
                Mix_PlayChannel(-1, gJump, 0);
        }
        break;
        case SDLK_DOWN:     // frogger go backward   
        {
            frogger.position.y += 48;
            frogger.degree = 180;
            if (frogger.position.y <= coordV[7])
            {
                frogger.velocity.x = 0;
            }
            if (soundEffect.mCurrentSprite == soundEffect.ON)
                Mix_PlayChannel(-1, gJump, 0);

        }
        break;
        case SDLK_RIGHT:    // frogger go right
        {
            frogger.position.x += 48;
            frogger.degree = 90;
            if (soundEffect.mCurrentSprite == soundEffect.ON)
            Mix_PlayChannel(-1, gJump, 0);
        }
        break;
        case SDLK_LEFT:     // frogger go left
        {
            frogger.position.x -= 48;
            frogger.degree = -90;
            if (soundEffect.mCurrentSprite == soundEffect.ON)
            Mix_PlayChannel(-1, gJump, 0);
        }
        break;
        }
    }
    audio.handleEvent(Event);
    if (audio.mCurrentSprite == audio.OFF)
        BGMOff = true;
    else
        BGMOff = false;
    option.handleEvent(Event);
    soundEffect.handleEvent(Event);
    if (soundEffect.mCurrentSprite == soundEffect.OFF)
        SEOff = true;
    else
        SEOff = false;
    methodbtn.handleEvent(Event);
    pause.handleEvent(Event);
}

//==============================================================================
