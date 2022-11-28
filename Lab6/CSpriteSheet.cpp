//==============================================================================
#include "CSpriteSheet.h"
//==============================================================================

CSpriteSheet::CSpriteSheet()
{
    //constructor
    cur_image = 0;
}

//==============================================================================

CSpriteSheet::~CSpriteSheet()       // ~ is used for destructors
{
    //destructor
}

//==============================================================================

int CSpriteSheet::load_sheet(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(fname);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", fname, SDL_GetError());
        return (-1);
    }
    w_width = temp->w;
    w_height = temp->h;

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
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}
/*
    int num_of_images    How many images to extract from texture
     int sx,             Start image x loc in texture
      int sy,            Start image y loc in texture
       int sw,           Width of ONE image in texture
        int sh,          Height of ONE image in texture
         int wx,         How many images on ONE row
          int hy,        How many rows of images on texture
           int border    How many pixels between images

    Note: Images are not really extracted... locations are saved to allow quick display...

*/

//==============================================================================

void CSpriteSheet::config_sheet(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border)
{
    SDL_Rect *pr;
    int curx,cury;
    int working_rec = 0;        // current index of the image?
    int working_row = 1;        // current row
    int working_col = 1;        // current column

    curx = sx;                  // Start image x loc in texture
    cury = sy;                  // Start image y loc in texture

    while (working_rec < num_of_images && working_row <= hy)
    {
        pr = &images[working_rec];
        pr->x = curx;
        pr->y = cury;
        pr->w = sw;
        pr->h = sh;
        working_col++;
        working_rec++;
        curx += sw + border;

        if (working_col > wx)
        {
            working_row++;
            working_col = 1;
            cury += sh + border;
            curx = sx;
        }

    }
    max_images = num_of_images;

}

//==============================================================================


/*
    Display the Sprite (current position) to the screen
    and optionally move to next image....

*/

//==============================================================================

void CSpriteSheet::play(SDL_Renderer *r, SDL_Rect *pos, bool gotonext)
{
    SDL_RenderCopy(r,texture,&images[cur_image],pos);
    if (gotonext)
    {
        cur_image++;
        if (cur_image >= max_images)
            cur_image = 0;
    }

    pos->x = pos->x + Xvelocity;

    if (pos->x < 0 - pos->w)
    {
        pos->x = window_w;
    }
}

//==============================================================================