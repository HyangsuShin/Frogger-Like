//==============================================================================
#include "CApp.h"
#include <iostream>
#include <numeric>
#include <array>

using namespace std;

//==============================================================================
//  frogger revival (set frogger to start point, reduce the life)
//==============================================================================
void CApp::Revival()
{
    if (soundEffect.mCurrentSprite == soundEffect.ON)
    {
        if (numberOfLivesLeft > 0)
        {
            if (frogger.position.y <= coordV[7])
            {
                Mix_PlayChannel(-1, gPlunk, 0);
            }
            else
            {
                Mix_PlayChannel(-1, gSquash, 0);
            }
        }
        else
        {
            Mix_PlayChannel(-1, gGameOver, 0);
        }
    }
    frogger.velocity.x = 0;
    frogger.position.x = window_w / 2 - 24;
    frogger.position.y = coordV[13];
    numberOfLivesLeft--;    // Decrease life by 1
    frogger.degree = 0;
}
//==============================================================================
//  Logs movement
//==============================================================================
void CApp::MoveLogs()
{
    int i;
    
    for (i = 0; i < NUM_LOG0; ++i)
    {
        Log0[i].move();
        Log0[i].display(renderer);
    }
    for (i = 0; i < NUM_LOG1; ++i)
    {
        Log1[i].move();
        Log1[i].display(renderer);
    }
    for (i = 0; i < NUM_LOG2; ++i)
    {
        Log2[i].move();
        Log2[i].display(renderer);
    }
}
//==============================================================================
//  Turtles movement
//==============================================================================
void CApp::MoveTurtles()
{
    static Uint32 cnt = 0;
    for (int i = 0; i < NUM_TURTLE0; i++)
    {
        if (cnt % 50)
            Turtle0[i].play(renderer, &TurtleSpot0[i], false);
        else {
            Turtle0[i].play(renderer, &TurtleSpot0[i], true);
        }
    }

    for (int i = 0; i < NUM_TURTLE1; i++)
    {
        if (cnt % 50)
            Turtle1[i].play(renderer, &TurtleSpot1[i], false);
        else {
            Turtle1[i].play(renderer, &TurtleSpot1[i], true);
        }
    }
    cnt++;
}
//==============================================================================
//  Cars movement
//==============================================================================
void CApp::MoveCars()
{
    int i;

    for (i = 0; i < NUM_CARS0to2; ++i)
    {
        Car0[i].move();
        Car0[i].display(renderer);

        if (check_collision(Car0[i].position, frogger.position) == true)
        {
            Revival();
        }
    }
    for (i = 0; i < NUM_CARS0to2; ++i)
    {
        Car1[i].move();
        Car1[i].display(renderer);
        if (check_collision(Car1[i].position, frogger.position) == true)
        {
            Revival();
        }
    }
    for (i = 0; i < NUM_CARS0to2; ++i)
    {
        Car2[i].move();
        Car2[i].display(renderer);
        if (check_collision(Car2[i].position, frogger.position) == true)
        {
            Revival();
        }
    }
    for (i = 0; i < NUM_CARS3; ++i)
    {
        Car3[i].move();
        Car3[i].display(renderer);
        if (check_collision(Car3[i].position, frogger.position) == true)
        {
            Revival();
        }
    }
    for (i = 0; i < NUM_CARS4; ++i)
    {
        Car4[i].move();
        Car4[i].display(renderer);
        if (check_collision(Car4[i].position, frogger.position) == true)
        {
            Revival();
        }
    }
}
//==============================================================================
//  Check if frogger collite with car
//==============================================================================
bool CApp::check_collision(SDL_Rect A, SDL_Rect B)
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of Rect A (snowflakes)
    leftA = A.x;            // 
    rightA = A.x + A.w;     // 
    topA = A.y;             // 
    bottomA = A.y + A.h;    // 

    // Calculate the sides of Rect B (Player)
    leftB = B.x+10;            // 
    rightB = B.x + B.w-10;     // 
    topB = B.y+10;             // 
    bottomB = B.y + B.h-10;    // 

    //////////////////////////////////////////////////////////////////////////
    // if any of these sides from A(snowflakes) are outside of B(Player)
    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    ///////////////////////////////////////////////////////////////////////////


    // if none of the sides from A are outside B
    return true;
}
//==============================================================================
//  Check if frogger plunk into the water
//==============================================================================
bool CApp::check_intoWater(SDL_Rect A)
{
    if (frogger.position.x + 40 > A.x && frogger.position.x+8 < (A.x + A.w))
    {
        return true;
    }
    return false;
}
void CApp::check_intoWater(SDL_Rect A[], int size)
{
    if (frogger.position.y == A[0].y)
    {
        bool isCollite[10] = { 0 };
        for (int i = 0; i < size; i++)
        {
            isCollite[i] = check_intoWater(A[i]);
        }
        if (accumulate(isCollite, isCollite + size, 0) > 0)
        {
            frogger.velocity.x = -1;
        }
        else
        {
            Revival();
        }
    }
}
void CApp::check_intoWater(Log A[], int size)
{
    if (frogger.position.y == A[0].position.y)
    {
        bool isCollite[10] = { 0 };
        for (int i = 0; i < size; i++)
        {
            isCollite[i] = check_intoWater(A[i].position);
        }
        if (accumulate(isCollite, isCollite + size, 0) > 0)
        {
            frogger.velocity.x = 1;
        }
        else
        {
            Revival();
        }
    }
}
void CApp::check_intoWater()
{  
    check_intoWater(TurtleSpot0, NUM_TURTLE0);
    check_intoWater(TurtleSpot1, NUM_TURTLE1);
    check_intoWater(Log0, NUM_LOG0);
    check_intoWater(Log1, NUM_LOG1);
    check_intoWater(Log2, NUM_LOG2);
}
//==============================================================================
//  Check Goal
//==============================================================================
void CApp::check_goal()
{
    int x1[6] = { 0,100,244,388,532,676};
    int x2[6] = {44,188,332,476,620,window_w};
    int isX[5] = { 48,192,336,480,624 };
    for (int i = 0; i < 6; i++)
    {
        if (frogger.position.y < coordV[2])
        {
            if (frogger.position.x >= x1[i]+20 && frogger.position.x <= x2[i]-20)
            {
                frogger.velocity.x = 0;
                Revival();
            }
            else if (i < 5) {
                if (isGoal[i] == false)
                {
                    if (frogger.position.x >= x2[i] - 20 && frogger.position.x <= x1[i + 1] + 20)
                    {
                        isGoal[i] = true;
                        goal_frog[i].position.x = isX[i];
                        frogger.position.x = window_w / 2 - 24;
                        frogger.position.y = coordV[13];
                        frogger.velocity.x = 0;
                        int sum = accumulate(isGoal, isGoal + 5, 0);
                        if (sum == 5)
                        {
                            score += 1000;
                            if (soundEffect.mCurrentSprite == soundEffect.ON)
                                Mix_PlayChannel(-1, gGameOver, 0);
                        }
                        else
                        {
                            score = score + 50; // Increase score by 50
                            if (soundEffect.mCurrentSprite == soundEffect.ON)
                                Mix_PlayChannel(-1, gGoal, 0);
                        }
                    }
                }
                else
                {
                    if (frogger.position.x >= x2[i] - 20 && frogger.position.x <= x1[i + 1] + 20)
                    {
                        Revival();
                    }
                }
                
            }
        }
        
    }

    for (int i = 0; i < 5; i++)
    {
        if (isGoal[i] == true)
        {
            goal_frog[i].display(renderer, NULL, 0, NULL);
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (frogger.position.y == coordV[i] && isCoordV[i] == false)
        {
            isCoordV[i] = true;
            score += 10;
        }
    }

    if (frogger.position.x <0 || frogger.position.x + 48 > window_w)
    {
        Revival();
    }
}
//==============================================================================
//  GameStart Scene
//==============================================================================
void CApp::GameStart()
{
        SDL_RenderClear(renderer);
        option.display(renderer);
        methodbtn.display(renderer);

        displayGameStart(window_w / 2, window_h / 2 - 100, "FROGGER GAME", color2);
        displayGameStart(window_w / 2, window_h / 2, "PRESS ENTER TO START", color);
        displayGameStart(window_w / 2, window_h /2 + 50, "PRESS ESC TO EXIT", color);
        displayGameStart(window_w / 2, window_h / 2 + 150, "SINGLE PLAYER", color);

        // Check option button is clicked
        if (option.mCurrentSprite == option.OFF)
        {
            GameOption();
        }
        // Check method button is clicked
        if (methodbtn.mCurrentSprite == methodbtn.OFF)
        {
            GameMethod();
        }
        else
        {
            pause.mCurrentSprite = pause.ON;
            method.src.y = 0;
        }
}
//==============================================================================
//  GameOption Scene
//==============================================================================
void CApp::GameOption()
{
    option.display(renderer);
    displayGameStats(audio.position.x - 40 , 9, "BG", score);
    audio.display(renderer);
    displayGameStats(soundEffect.position.x - 40, 9, "SE", score);
    soundEffect.display(renderer);
}
//==============================================================================
//  GameMethod Scene
//==============================================================================
void CApp::GameMethod()
{
    SDL_RenderClear(renderer);
    method.move();
    method.display(renderer);
    methodbtn.display(renderer);
    pause.display(renderer);
    // Check pause button is clicked
    if (pause.mCurrentSprite == pause.OFF)
    {
        method.velocity.y = 0;
    }
    else
    {
        method.velocity.y = 1;
    }
}
//==============================================================================
//  GamePlay Scene
//==============================================================================
void CApp::GamePlay()
{
    SDL_RenderClear(renderer);

    river.move();
    river.display(renderer);

    bg.display(renderer);

    MoveLogs();
    MoveCars();
    MoveTurtles();

    frogger.move();
    frogger.display(renderer, NULL, frogger.degree, NULL);

    check_intoWater();
    check_goal();

    //==============================================================================
    // Disply GameStats on Window
    //==============================================================================

    displayGameStats(20, 9, "Score: %3d", score);
    displayGameStats(20, coordV[14] + 9, "Live: %3d", numberOfLivesLeft);
    
    option.display(renderer);
    if (option.mCurrentSprite == option.OFF)
    {
        GameOption();
    }
}
//==============================================================================
//  GameOver Scene
//==============================================================================
void CApp::GameOver()
{
    int sum = accumulate(isGoal, isGoal + 5, 0);

    if (sum == 5)
    {
        SDL_RenderClear(renderer);
        Mix_PauseMusic();

        displayGameOver(window_w / 2, window_h / 2, "KILLED IT!");
        displayGameOver(window_w / 2, window_h / 2 + 50, "Press 'P' to Play Again");
        displayGameOver(window_w / 2, window_h / 2 + 100, "Press 'ESC' to EXIT");
    }

    if (numberOfLivesLeft <= 0)
    {
        SDL_RenderClear(renderer);
        Mix_PauseMusic();

        displayGameOver(window_w / 2, window_h / 2, "GAME OVER");
        displayGameOver(window_w / 2, window_h / 2 + 50, "Press 'P' to Play Again");
        displayGameOver(window_w / 2, window_h / 2 + 100, "Press 'ESC' to EXIT");
    }
}

//==============================================================================
//  Game Loop
//==============================================================================
void CApp::OnLoop()
{

    SDL_RenderClear(renderer);
    // Game Scenes
    if (!Start)
    {   
        GameStart();
    }
    else if(Start)
    {        
        GamePlay();
    }

    GameOver();
}

//==============================================================================