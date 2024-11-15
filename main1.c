
/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by <user_name> (@<user_github>) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 <user_name> (@<user_github>)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    const char *myfile = "scarfy.png";
    Texture2D scarfy = LoadTexture(myfile);


    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables / Implement example logic at this point
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // TODO: Draw everything that requires to be drawn at this point:

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);  // Example

        DrawTexture(scarfy , 15 ,45 ,WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
