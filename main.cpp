#include "raylib.h"

class Brick {
    public:
        Vector2 position; //Holds the x and y position of the brick
        Vector2 size; //Holds the width and height of the brick
        Color color; //Holds the color of the brick

        //Constructor of the brick class
        Brick(Vector2 position, Vector2 size, Color color) {
            this->position = position;
            this->size = size;
            this->color = color;
        }

        //Draws the brick
        void Draw(){
            DrawRectangleV(position, size, color);
        }

};

class Ball{
    public:
        Vector2 position; //Holds the x and y position of the ball
        float radius; //Holds the radius of the ball
        Color color; //Holds the color of the ball
        Vector2 speed; //Holds the speed of the ball

        //Constructor of the ball class
        Ball(Vector2 position, float radius, Color color, Vector2 speed) {
            this->position = position;
            this->radius = radius;
            this->color = color;
            this->speed = speed;
        }

        //Draws the ball
        void Draw(){
            DrawCircleV(position, radius, color);
        }

        void Update(){
            //modify the position of the ball based on its speed
            position.x += speed.x * GetFrameTime();
            position.y += speed.y * GetFrameTime();
        }
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Brick Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //create a single brick instance
    Brick brick({200,50},{100,50},RED);

    //create a single ball instance
    Ball ball({400,300},10,RED,{50,50});

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ball.Update(); //update the ball
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            brick.Draw(); //draw the brick
            ball.Draw(); //draw the ball

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}