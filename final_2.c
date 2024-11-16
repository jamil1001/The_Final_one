#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>
int main(void)
{
    const int screenWidth = 700;
    const int screenHeight = 500;
    const int scarfySpeed = 5;

    InitWindow(screenWidth, screenHeight, "2D_Game");

    // to set my character png in the window
    const char *myfile = "scarfy.png";
    Texture2D scarfy = LoadTexture(myfile);

    bool scarfymoving = false;

    // to make frame from my character pic
    unsigned numFrames = 6;
    int frameWidth = scarfy.width / numFrames;
    Rectangle frameRec = {0.0f, 0.0f, (float)frameWidth, (float)scarfy.height};
    Vector2 scarfyPosition = {screenWidth / 2.5f, screenHeight / 2.5f};
    Vector2 scarfyVelocity = {0.0f, 0.0f};

    unsigned frameDelay = 7;
    unsigned frameDelayCounter = 0;
    int frameindex = 0;
    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // step to use key_button
        if (IsKeyDown(KEY_RIGHT))
        {
            if (frameRec.width < 0)
            {
                frameRec.width = -frameRec.width;
            }
            // scarfymoving = true;
            scarfyVelocity.x = scarfySpeed;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            // scarfymoving = true;
            scarfyVelocity.x = -scarfySpeed;
            if (frameRec.width > 0)
            {
                frameRec.width = -frameRec.width;
            }
            
        }
        else
        {
            scarfyVelocity.x = 0;
        }
        // boot works like if , if scarfyvelocity != 0 then its make scarfymoving true from false
        bool scarfymoving = scarfyVelocity.x != 0.0f || scarfyVelocity.y != 0.0f;

        scarfyPosition = Vector2Add(scarfyPosition, scarfyVelocity);
        ++frameDelayCounter;
        if (frameDelayCounter > frameDelay)
        {
            frameDelayCounter = 0;
            if (scarfymoving)
            {
                ++frameindex;
                frameindex %= numFrames;
                frameRec.x = (float)frameWidth * frameindex, (float)scarfy.height;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureRec(scarfy, frameRec, scarfyPosition, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
