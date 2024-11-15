#include "raylib.h"
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    const char *myfile = "scarfy.png";
    Texture2D scarfy = LoadTexture(myfile);

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);
             DrawTexture(scarfy , 15 ,45 ,WHITE);
        EndDrawing();

    }

      CloseWindow();

       return 0;
}

