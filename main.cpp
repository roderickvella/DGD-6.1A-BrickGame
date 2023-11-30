#include "raylib.h"
#include <vector>

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

            if(position.x <=0 || position.x >= GetScreenWidth()){
                speed.x *= -1; //reverse the horizontal direction of the ball
            }

            if(position.y <=0 || position.y >= GetScreenHeight()){
                speed.y *= -1; //reverse the vertical direction of the ball
            }
        }
};

// void GenerateBricks(std::vector<Brick>& bricks){
//     //Assuming that our screen is 800px in width,we can fit 8 bricks in a row if each brick is 100px wide
//     for(int i=0; i <8; i++){
//         float x = 100 * i; //calculate the x position of the brick based on the index
//         float y=0; //set the y position of the brick to 0
//         Vector2 position = {x,y}; //create a vector2 to hold the x and y position of the brick
//         Vector2 size = {100,50}; //create a vector2 to hold the width and height of the brick

//         //randomly generate a color for the brick
//         int r = GetRandomValue(0,255);
//         int g = GetRandomValue(0,255);
//         int b = GetRandomValue(0,255);

//         Color color = {r,g,b,255}; //create a color based on the random values

//         //create a brick instance
//         Brick brick(position,size,color);
//         bricks.push_back(brick); //add the brick to the vector

//     }
// }


void GenerateBricks(std::vector<Brick>& bricks){
    float brickWidth = 100;
    float brickHeight = 50;

    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 8; col++){
            float x = brickWidth * col; // calculate the x position of the brick
            float y = brickHeight * row; // calculate the y position of the brick

            Vector2 position = {x, y};
            Vector2 size = {brickWidth, brickHeight};

            int r = GetRandomValue(0, 255);
            int g = GetRandomValue(0, 255);
            int b = GetRandomValue(0, 255);

            Color color = {r, g, b, 255};

            Brick brick(position, size, color);
            bricks.push_back(brick);
        }
    }
}


void DrawBricks(std::vector<Brick>& bricks){
    //iterate through the vector of bricks
    for(int i=0; i < bricks.size(); i++){
        bricks[i].Draw(); //draw the brick
    }
}

void HandleBallBrickCollisions(Ball& ball, std::vector<Brick>& bricks){
    //check for collisions between the ball and the bricks
    for(int i=0; i<bricks.size(); i++){
        //make use of CheckCollisionCircleRec
        if(CheckCollisionCircleRec(ball.position, ball.radius,Rectangle{bricks[i].position.x, bricks[i].position.y, bricks[i].size.x, bricks[i].size.y})){
            //reverse the vertical direction of the ball
            ball.speed.y *= -1;
            //remove the brick from the vector
            bricks.erase(bricks.begin() + i);
            break; //break out of the loop
        }
    }

} 



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    std::vector<Brick> bricks; //create a vector of bricks

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Brick Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    //create a single brick instance
    //Brick brick({200,50},{100,50},RED);

    //create a single ball instance
    Ball ball({400,300},10,RED,{200,200}); 


     //generate the bricks
    GenerateBricks(bricks);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ball.Update(); //update the ball
        HandleBallBrickCollisions(ball,bricks); //handle the ball and brick collisions
             
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //brick.Draw(); //draw the brick
            DrawBricks(bricks); //draw the bricks
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