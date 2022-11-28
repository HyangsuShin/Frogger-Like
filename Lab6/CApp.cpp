//==============================================================================
#include "CApp.h"
//==============================================================================

CApp::CApp()
{
    Running = true;
}

//==============================================================================

Uint32 CApp::time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

//==============================================================================

int CApp::LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
        return (-1);
    }

    prect->w = temp->w;
    prect->h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    *psprite = SDL_CreateTextureFromSurface(renderer, temp);
    if (!*psprite)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }

    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

//==============================================================================

int CApp::OnExecute()
{
    //Initialize SDL_mixer
    if (loadMedia() == false)
    {
        return -1;
    }

    Mix_PlayMusic(gMusic, -1);
    
    do {    
        Restart = false;        //For checking player want to restart
        
        if (OnInit() == false)
        {
            return -1;
        }


        Running = true;         //For restart the game
        SDL_Event Event;
        next_time = SDL_GetTicks() + TICK_INTERVAL;
        while (Running)
        {
            while (SDL_PollEvent(&Event))
            {
                OnEvent(&Event);
            }

            OnLoop();
            OnRender();
        }
    } while (Restart);          //Game will restart if player press "P"

    OnCleanup();

    return 0;
}

//==============================================================================

bool CApp::loadMedia()
{
    //Loading Running flag
    bool Running = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        Running = false;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    gMusic = Mix_LoadMUS("musics\\background.wav");
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

    gStart = Mix_LoadWAV("musics\\start.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    gSquash = Mix_LoadWAV("musics\\squash.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    gPlunk = Mix_LoadWAV("musics\\plunk.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    gJump = Mix_LoadWAV("musics\\jump.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }
    Mix_VolumeChunk(gJump, MIX_MAX_VOLUME / 10);

    gGoal = Mix_LoadWAV("musics\\goal.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    gGameOver = Mix_LoadWAV("musics\\gameover.wav");
    if (gMusic == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        Running = false;
    }

    return Running;
}

//==============================================================================

int main(int argc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
// Display GameStart Text
//==============================================================================

void CApp::displayGameStart(int x, int y, const char* formattedString, SDL_Color color)
{
    SDL_DestroyTexture(messageTexture);     //release the texture and sufaces resources we created
    SDL_FreeSurface(messageSurface);

    sprintf_s(message, formattedString);                                //Convert number to string
    messageSurface = TTF_RenderText_Solid(font2, message, color);              //Make text an image (an SDL_Surface)
    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);    //Convert SDL_Surface to SDL_Texture

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);		            //get width & height of texture
    messageRect = { x - (messageSurface->w / 2), y, texW, texH };				    //create a SDL_Rect for the message, position center of text to x coordinate
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);               //copy it to screen
}

//==============================================================================
// Display Game stats Text
//==============================================================================

void CApp::displayGameStats(int x, int y, const char* formattedString, int number)
{
    SDL_DestroyTexture(messageTexture);     //release the texture and sufaces resources we created
    SDL_FreeSurface(messageSurface);

    sprintf_s(message, formattedString, number);                                //Convert number to string
    messageSurface = TTF_RenderText_Solid(font, message, color);                //Make text an image (an SDL_Surface)
    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);    //Convert SDL_Surface to SDL_Texture

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);		            //get width & height of texture
    messageRect = { x, y, texW, texH };				                            //create a SDL_Rect for the message
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);               //copy it to screen
}

//==============================================================================
// Display GameOver Text
//==============================================================================

void CApp::displayGameOver(int x, int y, const char* formattedString)
{
    SDL_DestroyTexture(messageTexture);     //release the texture and sufaces resources we created
    SDL_FreeSurface(messageSurface);

    sprintf_s(message, formattedString);                                //Convert number to string
    messageSurface = TTF_RenderText_Solid(font1, message, color1);              //Make text an image (an SDL_Surface)
    messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);    //Convert SDL_Surface to SDL_Texture

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);		            //get width & height of texture
    messageRect = { x-(messageSurface->w / 2), y, texW, texH };				    //create a SDL_Rect for the message, position center of text to x coordinate
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);               //copy it to screen
}

//==============================================================================