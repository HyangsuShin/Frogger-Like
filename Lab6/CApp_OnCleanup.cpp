//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() {

    SDL_DestroyTexture(messageTexture); //free the texture and surfaces
    SDL_FreeSurface(messageSurface);
    TTF_CloseFont(font);		  	    //free the font resource
    TTF_Quit(); 		        	    //shut down the SDL_ttf subsystem

    // free the sound effects
    Mix_FreeChunk(gGameOver);
    gGameOver = NULL;
    Mix_FreeChunk(gGoal);
    gGoal = NULL;
    Mix_FreeChunk(gJump);
    gJump = NULL;
    Mix_FreeChunk(gPlunk);
    gPlunk = NULL;
    Mix_FreeChunk(gSquash);
    gSquash = NULL;
    Mix_FreeChunk(gStart);
    gStart = NULL;

    // free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    // Quit SDL subsystems
    Mix_Quit();
    SDL_Quit();

}

//==============================================================================
