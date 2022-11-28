//==============================================================================
// SDL Lab 6
//==============================================================================

#ifndef _CAPP_H_
#define _CAPP_H_

#define TICK_INTERVAL    10

#define NUM_LOG0        4   //Num of Log0
#define NUM_LOG1        4   //Num of Log1
#define NUM_LOG2        5   //Num of log2
#define NUM_CARS0to2    3   //Num of Car0 to 2
#define NUM_CARS3       1   //Num of Car3
#define NUM_CARS4       2   //Num of Car4
#define NUM_TURTLE0     4   //Num of Turtle0
#define NUM_TURTLE1     4   //Num of Turtle1

#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <time.h>

#include "SDL.h"
#include "SDL_ttf.h"        //for fonts
#include "SDL_mixer.h"      //for sound and music

#include "mywindow.h"
#include "CPlayer.h"        //Class for Snowflakes
#include "CScroll_Player.h" //Class for Scrolling background 
#include "CSpriteSheet.h"   //Class for Sprite sheet
#include "CButton.h"        //Class for Cbutton
#include "Frogger.h"        //Class for frogger (Player)
#include "Background.h"     //Class for background
#include "Log.h"            //Class for Log
#include "Car.h"            //Class for Car
#include "AudioBtn.h"          //Class for Audio btn
#include "OptionBtn.h"      //Class for Option btn
#include "SoundEffectBtn.h"    //Class for SoundEffect btn
#include "MethodBtn.h"      //Class for Method btn
#include "RiverScroll.h"    //Class for Scrolling river
#include "MethodScroll.h"   //Class for Scrolling method

//==============================================================================

class CApp
{

//In C++, there are three access specifiers :

//public	- members are accessible from outside the class
//private	- members cannot be accessed(or viewed) from outside the class
//protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes.

// Default value - private

private:
    bool Running;
    bool Start;         // check start or not
    bool Restart;       // check restart or not
    bool BGMOff;        // check BGM off
    bool SEOff;         // check sound effect off

    // Font types
    TTF_Font* font;     // font object will use for the gamestats
    TTF_Font* font1;    // font object will use for the gameover
    TTF_Font* font2;    // font object will use for the gamestart
    // Font colors
    SDL_Color color;    // Text color
    SDL_Color color1;   // Text color
    SDL_Color color2;   // Text color

    char message[100];  // Message String

    SDL_Surface* messageSurface;    //Surface that stores the message
    SDL_Texture* messageTexture;    //Surface is converted to a texture
    SDL_Rect messageRect;           //location of the message

    //The music that will be played
    Mix_Music* gMusic = NULL;

    //Sound effects that will be used
    Mix_Chunk* gStart = NULL;
    Mix_Chunk* gSquash = NULL;
    Mix_Chunk* gPlunk = NULL;
    Mix_Chunk* gJump = NULL;
    Mix_Chunk* gGoal = NULL;
    Mix_Chunk* gGameOver = NULL;

    Uint32 next_time;
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Background images
    Background bg;          //background
    RiverScroll river;      //river (Scroll part)
    MethodScroll method;    //method (Scroll part)
    Frogger frogger;        //frogger (Player)
    Frogger goal_frog[5];   //goal frogger
    
    //Logs
    Log Log0[NUM_LOG0];
    Log Log1[NUM_LOG1];
    Log Log2[NUM_LOG2];
    int sumLogs = NUM_LOG0 + NUM_LOG1 + NUM_LOG2;
    
    //Cars
    Car Car0[NUM_CARS0to2];
    Car Car1[NUM_CARS0to2];
    Car Car2[NUM_CARS0to2];
    Car Car3[NUM_CARS3];
    Car Car4[NUM_CARS4];
    
    //Turtles
    CSpriteSheet Turtle0[NUM_TURTLE0];
    CSpriteSheet Turtle1[NUM_TURTLE1];
    SDL_Rect TurtleSpot0[NUM_TURTLE0];
    SDL_Rect TurtleSpot1[NUM_TURTLE1];

    //Buttons
    AudioBtn audio;
    OptionBtn option;
    SoundEffectBtn soundEffect;
    MethodBtn methodbtn;
    CButton pause;
    
    int coordV[15];                 //vertical coordinate
    bool isCoordV[15] = { false };  //Check is frogger passed this coordinate
    int numberOfLivesLeft;
    int score;
    bool isGoal[5] = { false };     //Check is all in goal

public:
    CApp();
    Uint32 time_left(void);
    int OnExecute();

    // Joy stick
    //SDL_Joystick* joy = NULL;

public:
    bool OnInit();

    void Revival();     // set frogger to start point
    void MoveLogs();    // move all the logs
    void MoveCars();    // move all the cars
    void MoveTurtles(); // move all the turtles
    bool check_collision(SDL_Rect A, SDL_Rect B);   // Basic check collision (Car) 
    bool check_intoWater(SDL_Rect A);               // basic code for check where the frogger is
    void check_intoWater(SDL_Rect A[], int size);   // basic code for check frogger is on tuttles
    void check_intoWater(Log A[], int size);        // basic code for check frogger is on logs
    void check_intoWater();                         // check frogger is plunk
    void check_goal();  // check the goal
    void GameStart();   // GameStart Scene
    void GameOption();  // GameOption Scene
    void GameMethod();  // GameOption Scene
    void GamePlay();    // GamePlay Scene
    void GameOver();    // GameOver Scene
    
    bool loadMedia();   // Load music

    void displayGameStart(int x, int y, const char* formattedString, SDL_Color color);
    void displayGameStats(int x, int y, const char* formattedString, int number);
    void displayGameOver(int x, int y, const char* formattedString);

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();
    int LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect);
    
    void OnCleanup();
};
#endif  // CAPP_H
//==============================================================================
