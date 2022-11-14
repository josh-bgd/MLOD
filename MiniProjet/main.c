/*********************************************************************************************
*
*   raylib - classic game: snake
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define SNAKE_LENGTH   256
#define SQUARE_SIZE     31
#define MAX_INPUT_CHARS     5

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Snake {
    Vector2 position;
    Vector2 size;
    Vector2 speed;
    Color color;
} Snake;

typedef struct Food { 
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} Food;

//je créer un fruit BadFood qui enlève une case au serpent

typedef struct BadFood {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} BadFood;

//je créer un ShrinkFood qui va faire rétrécir le serpent d'une case à chaque pas tant qu'il n'a pas mangé un Fruit

typedef struct ShrinkFood {
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
} ShrinkFood;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------

static const int screenWidth = 800;
static const int screenHeight = 450;

static const int gridWidth = screenWidth - 150;
static const int gridHeight = 450;

static int framesCounter = 0;
static bool gameOver;
static bool pause;
static bool shrink;
int score;
int hiscore;
char name[MAX_INPUT_CHARS + 1] = "\0"; 
Rectangle textBox1 = { screenWidth/2.0f - 60, 180, 140, 50 };
Rectangle textBox2 = { 300, 300, 300, 300 };
Rectangle textBox3 = { 450, 300, 300, 380};

static Food fruit = { 0 };
static BadFood badFruit = { 0 };
static ShrinkFood shrinkFruit = { 0 };
static Snake snake[SNAKE_LENGTH] = { 0 };
static Vector2 snakePosition[SNAKE_LENGTH] = { 0 };
static bool allowMove = false;
static Vector2 offset = { 0 };
static int counterTail = 0;
static bool pseudoEntered;
int letterCount = 0;
bool mouseOnText = false;
bool samePlayer = true;


//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Mini Projet MLOD: snake");

    InitGame();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    
    framesCounter = 0;
    gameOver = false;
    pause = false;
    shrink = false;
    score = 0;
    if (!samePlayer)
    {
        pseudoEntered = false;
        name[MAX_INPUT_CHARS + 1] = "\0"; 
    }

    counterTail = 1;
    allowMove = false;

    offset.x = gridWidth%SQUARE_SIZE;
    offset.y = gridHeight%SQUARE_SIZE;

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snake[i].position = (Vector2){ offset.x/2, offset.y/2 };
        snake[i].size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
        snake[i].speed = (Vector2){ SQUARE_SIZE, 0 };

        if (i == 0) snake[i].color = RAYWHITE;
        else snake[i].color = WHITE;
    }

    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        snakePosition[i] = (Vector2){ 0.0f, 0.0f };
    }

    fruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
    fruit.color = SKYBLUE;
    fruit.active = false;
    
    // j'initialise un badFruit de couleur rouge cette fois-ci
    
    badFruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
    badFruit.color = RED;
    badFruit.active = false;
    
    // j'initialise un shrinkFruit de couleur violette cette fois-ci
    
    shrinkFruit.size = (Vector2){ SQUARE_SIZE, SQUARE_SIZE };
    shrinkFruit.color = YELLOW;
    shrinkFruit.active = false;
    
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver && pseudoEntered)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            // Player control
            if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ SQUARE_SIZE, 0 };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ -SQUARE_SIZE, 0 };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ 0, -SQUARE_SIZE };
                allowMove = false;
            }
            if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0) && allowMove)
            {
                snake[0].speed = (Vector2){ 0, SQUARE_SIZE };
                allowMove = false;
            }

            // Snake movement
            for (int i = 0; i < counterTail; i++) snakePosition[i] = snake[i].position;

            if ((framesCounter%5) == 0)
            {
                for (int i = 0; i < counterTail; i++)
                {
                    if (i == 0)
                    {
                        snake[0].position.x += snake[0].speed.x;
                        snake[0].position.y += snake[0].speed.y;
                        allowMove = true;
                    }
                    else snake[i].position = snakePosition[i-1];
                }
            }



            // Wall behaviour
            if ((snake[0].position.x) > (gridWidth - offset.x))
            {
                snake[0].position.x = offset.x/2;
            }
                
            else if
                ((snake[0].position.y) > (gridHeight - offset.y)) 
                {
                   snake[0].position.y = offset.y/2; 
                }
            
            else if
                (snake[0].position.x < 0) 
                {
                snake[0].position.x = gridWidth - offset.x/2 - SQUARE_SIZE; 
                }
            
            else if
                (snake[0].position.y < 0) 
                {
                   snake[0].position.y = gridHeight - offset.y/2 - SQUARE_SIZE; 
                }
              

            // Collision with yourself
            for (int i = 1; i < counterTail; i++)
            {
                if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y))
                {
                    if (score > hiscore){
                    hiscore = score;
                    }
                    gameOver = true;
                }
            }       
           
           
                // Fruit position calculation
            if (!fruit.active)
            {
                fruit.active = true;
                fruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };

                for (int i = 0; i < counterTail; i++)
                {
                    while ((fruit.position.x == snake[i].position.x) && (fruit.position.y == snake[i].position.y))
                    {
                        fruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };
                        i = 0;
                    }
                }
            }
            
            // je rajoute un badFruit
            
            if (!badFruit.active)
            {
                badFruit.active = true;
                badFruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };

                for (int i = 0; i < counterTail; i++)
                {
                    while ((badFruit.position.x == snake[i].position.x) && (badFruit.position.y == snake[i].position.y))
                    {
                        badFruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };
                        i = 0;
                    }
                }
            }
            
            // je rajoute un shrinkFruit
            
            if (!shrinkFruit.active)
            {
                shrinkFruit.active = true;
                shrinkFruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };

                for (int i = 0; i < counterTail; i++)
                {
                    while ((shrinkFruit.position.x == snake[i].position.x) && (shrinkFruit.position.y == snake[i].position.y))
                    {
                        shrinkFruit.position = (Vector2){ GetRandomValue(0, (gridWidth/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.x/2, GetRandomValue(0, (gridHeight/SQUARE_SIZE) - 1)*SQUARE_SIZE + offset.y/2 };
                        i = 0;
                    }
                }
            }
            

            // Collisions
            
            if ((snake[0].position.x < (fruit.position.x + fruit.size.x) && (snake[0].position.x + snake[0].size.x) > fruit.position.x) &&
                (snake[0].position.y < (fruit.position.y + fruit.size.y) && (snake[0].position.y + snake[0].size.y) > fruit.position.y))
            {
                snake[counterTail].position = snakePosition[counterTail - 1];
                counterTail += 1;
                score += counterTail*15;
                shrink= false;
                fruit.active = false;
            }
            
            
            // je mets en place la collision avec un badFruit
            
            else if ((snake[0].position.x < (badFruit.position.x + badFruit.size.x) && (snake[0].position.x + snake[0].size.x) > badFruit.position.x) &&
                (snake[0].position.y < (badFruit.position.y + badFruit.size.y) && (snake[0].position.y + snake[0].size.y) > badFruit.position.y))
            {
                snake[counterTail].position = snakePosition[counterTail - 1];
                if(counterTail>1) 
                {
                    score += counterTail*30;
                    counterTail -= 1;
                }
                else {
                    if (score > hiscore){
                    hiscore = score;
                    }
                    gameOver = true;
                }
                badFruit.active = false;
            }
            
            // je mets en place la collision avec un shrinkFruit
            
            else if ((snake[0].position.x < (shrinkFruit.position.x + shrinkFruit.size.x) && (snake[0].position.x + snake[0].size.x) > shrinkFruit.position.x) &&
                (snake[0].position.y < (shrinkFruit.position.y + shrinkFruit.size.y) && (snake[0].position.y + snake[0].size.y) > shrinkFruit.position.y))
            {
                snake[counterTail].position = snakePosition[counterTail - 1];
                shrink = true;
                shrinkFruit.active = false; 
            }
            
        if (shrink && (framesCounter%20==0))
        {
            if(counterTail>1) 
                {
                    score += counterTail*800;
                    counterTail -= 1; 
                }
                else {
                    if (score > hiscore){
                    hiscore = score;
                    }
                    gameOver = true;
                }
        }
            
            framesCounter++;
        
        }
    }
    else if (!gameOver && !pseudoEntered)
    {
         if (CheckCollisionPointRec(GetMousePosition(), textBox1)) mouseOnText = true;
        else mouseOnText = false;

            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                    pseudoEntered = false;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
                pseudoEntered = false;
            }
            
            if (name[0]!='\0' || name[0]!=" "){
                
                if (IsKeyPressed(KEY_ENTER))
                {
                    pseudoEntered = true;
                }
            }
            framesCounter++;
    }
    
    else if (gameOver && pseudoEntered)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
        
        if (IsKeyPressed(KEY_RIGHT))
        {
            samePlayer = false;
        }
        
        if (IsKeyPressed(KEY_LEFT))
        {
            samePlayer = true;
        }
    }    
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(BLACK);

        if (!gameOver && pseudoEntered)
        {
            // Draw grid lines
            for (int i = 0; i < gridWidth/SQUARE_SIZE + 1; i++)
            {
                DrawLineV((Vector2){SQUARE_SIZE*i + offset.x/2, offset.y/2}, (Vector2){SQUARE_SIZE*i + offset.x/2, gridHeight - offset.y/2}, LIGHTGRAY);
            }

            for (int i = 0; i < gridHeight/SQUARE_SIZE + 1; i++)
            {
                DrawLineV((Vector2){offset.x/2, SQUARE_SIZE*i + offset.y/2}, (Vector2){gridWidth - offset.x/2, SQUARE_SIZE*i + offset.y/2}, LIGHTGRAY);
            }

            // Draw snake
            for (int i = 0; i < counterTail; i++) DrawRectangleV(snake[i].position, snake[i].size, snake[i].color);

            // Draw fruit to pick
            DrawRectangleV(fruit.position, fruit.size, fruit.color);
            
            // Dessiner un badFruit
            DrawRectangleV(badFruit.position, badFruit.size, badFruit.color);
            
            // Dessiner un shrinkFruit
            DrawRectangleV(shrinkFruit.position, shrinkFruit.size
            , shrinkFruit.color);
            
            DrawText(TextFormat("Score: %07i", score), 651, 80, 18, WHITE);
            
            DrawText(TextFormat("HiScore: %07i", hiscore), 651, 120, 18, YELLOW);
            
            DrawText(TextFormat("Pseudo: %s", name), 651, 160, 20, BLUE);
        

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        
        else if (!gameOver && !pseudoEntered)
        {
            DrawText("WRITE YOUR PSEUDO", 240, 140, 20, BLACK);

            DrawRectangleRec(textBox1, BLACK);
            if (mouseOnText) DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, RED);
            else DrawRectangleLines((int)textBox1.x, (int)textBox1.y, (int)textBox1.width, (int)textBox1.height, WHITE);

            DrawText(name, (int)textBox1.x + 5, (int)textBox1.y + 8, 40, RED);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, WHITE);

            
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox1.x + 8 + MeasureText(name, 40), (int)textBox1.y + 12, 40, RED);
                }
                else 
                {
                    DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, BLUE);
                    DrawText("Or press ENTER to start playing...", 230, 340, 20, BLUE);
                }
        }
        
        else if (gameOver && pseudoEntered) 
        { 
            DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
            DrawText(TextFormat("Score: %07i", score), 330, 80, 20, WHITE);
            DrawText(TextFormat("HiScore: %07i", hiscore), 320
            , 120, 20, YELLOW);
            DrawText(TextFormat("same Player?"), 340, 240, 20, BLUE);
            if(samePlayer) 
            {
               DrawRectangleRec(textBox2, BLACK);
               DrawText("YES", (int)textBox2.x + 5, (int)textBox2.y + 8, 40, RED);
            }
            else 
            {
                DrawRectangleRec(textBox3, BLACK);
                DrawText("NO", (int)textBox3.x + 5, (int)textBox3.y + 8, 40, RED);
            }
        }
        
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
