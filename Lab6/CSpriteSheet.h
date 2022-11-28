//==============================================================================

#ifndef CSPRITESHEET_H
#define CSPRITESHEET_H

#define MAX_SPRITE_IMAGES 141

#include <string.h>
#include <cstdio>
#include "mywindow.h"

#include "SDL.h"

//==============================================================================

class CSpriteSheet
{
    public:
        char fname[255];
        
        int max_images;
        int cur_image;
        int w_width;    // Whole width and height of texture
        int w_height;
        
        SDL_Rect images[MAX_SPRITE_IMAGES];
        
        int Xvelocity;
   
        CSpriteSheet();
        virtual ~CSpriteSheet();
        
        void set_sheet(const char n[])
        {
            strncpy_s(fname,n,255);
        }
        
        int load_sheet(SDL_Renderer *renderer);
        
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
        void config_sheet(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border);
        void play(SDL_Renderer *r, SDL_Rect *pos, bool gotonext);
        
        void rewind()
        {
            cur_image = 0;
        }

        void stop() {
            Xvelocity = 0;
        }
        
    
    protected:
    
    private:
        SDL_Texture *texture;
        SDL_Surface *ps;
};

#endif // CSPRITESHEET_H
//==============================================================================
