//==============================================================================
#include "CApp.h"
//==============================================================================

bool CApp::OnInit()
{
    int i;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Game202: Lab6_HyangSuShin",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    if (!window)
        return false;
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    // initialize sdl ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    // Initialize font and color of text
    font = TTF_OpenFont("font\\lazy.ttf", 30);      //Game stats
    font1 = TTF_OpenFont("font\\lazy.ttf", 40);     //Game Over
    font2 = TTF_OpenFont("font\\Sketchy.ttf", 40);  //Game start

    color = { 255, 255, 255 };  //Game stats
    color1 = { 255, 255, 255 }; //white
    color2 = { 223, 255, 0 };   //green

    // Initialize the subsystem for joystick
    /*SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    if (SDL_NumJoysticks() > 0)
    {
       joy = SDL_JoystickOpen(0);

    }*/

    // Random number generator
    srand(time(NULL));

    // Vertical Coordinate
    coordV[0] = 24;
    for (int i = 1; i < 15; i++)
    {
        coordV[i] = coordV[i-1] + 48;
    }
    coordV[0] = 0;
    
    // Initialize Check is frogger passed this coordinate
    for (int i = 0; i < 15; i++)
    {
        isCoordV[i] = false;
    }

    // Initialize lives
    numberOfLivesLeft = 5;
    
    // Initialize score
    score = 0;
    
    // Initialize Check is all in goal
    for (int i = 0; i < 5; i++)
    {
        isGoal[i] = false;
    }

    //==============================================================================
    //BackGround
    //==============================================================================

    strncpy_s(bg.imagename, "pictures\\bg.bmp", 255);
    bg.loadPlayer(renderer);

    //==============================================================================
    //River
    //==============================================================================

    strncpy_s(river.imagename, "pictures\\river.bmp", 255);
    river.loadPlayer(renderer);  //Render on to the screen
    river.set_scroll_loc(0, 0, window_w, 320); //set_scroll_loc(x position, y position, width, height);

    //==============================================================================
    //GameMethod
    //==============================================================================

    strncpy_s(method.imagename, "pictures\\gameMethod.bmp", 255);
    method.loadPlayer(renderer);  //Render on to the screen
    method.set_scroll_loc(0, 0, window_w, window_h); //set_scroll_loc(x position, y position, width, height);

    //==============================================================================
    //Log Object
    //==============================================================================
    int LogW[3] = { 144, 192, 96 };
    int IntervalLog[3] = { (WINDOW_WIDTH - (LogW[0] * (NUM_LOG0-1))) / (NUM_LOG0-1),
                            (WINDOW_WIDTH - (LogW[1] * (NUM_LOG1 - 1))) / (NUM_LOG1 - 1),
                            (WINDOW_WIDTH - (LogW[2] * (NUM_LOG2 - 1))) / (NUM_LOG2 - 1) };

    for (int i = 0; i < NUM_LOG0; i++)
    {
        Log0[i] = Log("pictures\\log_0.bmp", 0, 0, 0, 0);
        Log0[i].position.x = -(LogW[0]/2) + (IntervalLog[0] * i) + (LogW[0] * i);
        Log0[i].position.y = coordV[2];
        Log0[i].velocity.x = 1;
        Log0[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_LOG1; i++)
    {
        Log1[i] = Log("pictures\\log_1.bmp", 0, 0, 0, 0);
        Log1[i].position.x = -(LogW[1] / 2) + (IntervalLog[1] * i) + (LogW[1] * i);
        Log1[i].position.y = coordV[4];
        Log1[i].velocity.x = 1;
        Log1[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_LOG2; i++)
    {
        Log2[i] = Log("pictures\\log_2.bmp", 0, 0, 0, 0);
        Log2[i].position.x = -(LogW[2] / 2) + (IntervalLog[2] * i) + (LogW[2] * i);
        Log2[i].position.y = coordV[5];
        Log2[i].velocity.x = 1;
        Log2[i].loadPlayer(renderer);
    }

    //==============================================================================
    //Car Object
    //==============================================================================

    for (int i = 0; i < NUM_CARS0to2; i++)
    {
        Car0[i] = Car("pictures\\vehicle_0.bmp", 0, 0, 0, 0);
        Car0[i].position.x = (WINDOW_WIDTH/NUM_CARS0to2)/2 + ((WINDOW_WIDTH/NUM_CARS0to2)*i);
        Car0[i].position.y = WINDOW_HEIGHT - 48*3;
        Car0[i].velocity.x = -1;
        Car0[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_CARS0to2; i++)
    {
        Car1[i] = Car("pictures\\vehicle_1.bmp", 0, 0, 0, 0);
        Car1[i].position.x = (WINDOW_WIDTH / NUM_CARS0to2) / 2 + ((WINDOW_WIDTH / NUM_CARS0to2) * i);
        Car1[i].position.y = WINDOW_HEIGHT - 48*4;
        Car1[i].velocity.x = 1;
        Car1[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_CARS0to2; i++)
    {
        Car2[i] = Car("pictures\\vehicle_2.bmp", 0, 0, 0, 0);
        Car2[i].position.x = (WINDOW_WIDTH / NUM_CARS0to2) / 2 + ((WINDOW_WIDTH / NUM_CARS0to2) * i);
        Car2[i].position.y = WINDOW_HEIGHT - 48*5;
        Car2[i].velocity.x = -1;
        Car2[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_CARS3; i++)
    {
        Car3[i] = Car("pictures\\vehicle_3.bmp", 0, 0, 0, 0);
        Car3[i].position.x = (WINDOW_WIDTH / NUM_CARS0to2) / 2 + ((WINDOW_WIDTH / NUM_CARS0to2) * i);
        Car3[i].position.y = WINDOW_HEIGHT - 48*6;
        Car3[i].velocity.x = 1;
        Car3[i].loadPlayer(renderer);
    }
    for (int i = 0; i < NUM_CARS4; i++)
    {
        Car4[i] = Car("pictures\\vehicle_4.bmp", 0, 0, 0, 0);
        Car4[i].position.x = (WINDOW_WIDTH / NUM_CARS0to2) / 2 + ((WINDOW_WIDTH / NUM_CARS0to2) * i);
        Car4[i].position.y = WINDOW_HEIGHT - 48*7;
        Car4[i].velocity.x = -1;
        Car4[i].loadPlayer(renderer);
    }

    //==============================================================================
    //Frogger
    //==============================================================================

    frogger = Frogger("pictures\\frog_0.bmp", window_w/2 -24, coordV[13], 0, 0);
    frogger.loadPlayer(renderer);
    for (int i = 0; i < 5; i++)
    {
        goal_frog[i] = Frogger("pictures\\goal_frog.bmp", 0, coordV[1], 0, 0);
        goal_frog[i].loadPlayer(renderer);
    }

    //==============================================================================
    //Turtle
    //==============================================================================
    int TurtleW[2] = { 82, 124 };
    int IntervalTurtle[2] = { (WINDOW_WIDTH - (TurtleW[0] * (NUM_TURTLE0 - 1))) / (NUM_TURTLE0 - 1),
                              (WINDOW_WIDTH - (TurtleW[1] * (NUM_TURTLE1 - 1))) / (NUM_TURTLE1 - 1)};
    
    for (int i = 0; i < NUM_TURTLE0; i++)
    {
        Turtle0[i].set_sheet("pictures\\turtle_0.bmp");

        if (Turtle0[i].load_sheet(renderer) != 0)
        {
            printf("Bad load of runner animation file\n");
        }

        Turtle0[i].config_sheet(5, 0, 0, 82, 48, 5, 1, 0);
        Turtle0[i].Xvelocity = -1;
        TurtleSpot0[i].h = Turtle0[i].images[0].h;
        TurtleSpot0[i].w = Turtle0[i].images[0].w;
        TurtleSpot0[i].x = -(TurtleW[0] / 2) + (IntervalTurtle[0] * i) + (TurtleW[0] * i);
        TurtleSpot0[i].y = coordV[3];
    }

    for (int i = 0; i < NUM_TURTLE1; i++)
    {
        Turtle1[i].set_sheet("pictures\\turtle_1.bmp");

        if (Turtle1[i].load_sheet(renderer) != 0)
        {
            printf("Bad load of runner animation file\n");
        }

        Turtle1[i].config_sheet(5, 0, 0, 124, 48, 5, 1, 0);
        Turtle1[i].Xvelocity = -1;
        TurtleSpot1[i].h = Turtle1[i].images[0].h;
        TurtleSpot1[i].w = Turtle1[i].images[0].w;
        TurtleSpot1[i].x = -(TurtleW[1] / 2) + (IntervalTurtle[1] * i) + (TurtleW[1] * i);
        TurtleSpot1[i].y = coordV[6];
    }
    //==============================================================================
    //Buttons
    //==============================================================================
    option = OptionBtn("pictures\\option_40.bmp", window_w - 48, 4, 40, 40);
    option.loadPlayer(renderer);
    audio = AudioBtn("pictures\\audio_40.bmp", window_w - 48 * 2 - 10, 4, 40, 40);
    audio.loadPlayer(renderer);
    if (BGMOff)
    {
        audio.mCurrentSprite = audio.OFF;
    }
    soundEffect = SoundEffectBtn("pictures\\audio_40.bmp", window_w - 48 * 3 - 60, 4, 40, 40);
    soundEffect.loadPlayer(renderer);
    if (SEOff)
    {
        soundEffect.mCurrentSprite = soundEffect.OFF;
    }
    methodbtn = MethodBtn("pictures\\method.bmp", 10, 4, 40, 40);
    methodbtn.loadPlayer(renderer);
    pause = CButton("pictures\\pause.bmp", window_w - 48, window_h -48, 40, 40);
    pause.loadPlayer(renderer);
    return true;
}
//==============================================================================

