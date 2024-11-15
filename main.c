/*******************************************************************************************
*
*   RayLib 2D Challenge - An animated character
*
*   @author Hans de Ruiter
*
*   @copyright (c) 2022 by Kea Sigma Delta Limited, all rights reserved
*
*   License:
*   This software is provided 'as-is', without any express or implied warranty. In no event 
*   will the authors be held liable for any damages arising from the use of this software.
*   
*   Permission is granted to anyone to use this software for any purpose, including 
*   commercial applications, and to alter it and redistribute it freely, subject to the 
*   following restrictions:
*   
*   1. The origin of this software must not be misrepresented; you must not claim that you 
*   wrote the original software. If you use this software in a product, an acknowledgment 
*   in the product documentation would be appreciated but is not required.
*   
*   2. Altered source versions must be plainly marked as such, and must not be misrepresented 
*   as being the original software.
*   
*   3. This notice may not be removed or altered from any source distribution.
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#include <stdbool.h>

bool isTextureValid(const Texture2D *texture) {
	return texture->id > 0;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
	
	const int scarfySpeed = 5;

    InitWindow(screenWidth, screenHeight, "RayLib - 2D Character Animation");

	const char *filename = "scarfy.png";
	Texture2D scarfy = LoadTexture(filename);
	if(!isTextureValid(&scarfy)) {
		
		while (!WindowShouldClose()) {
			BeginDrawing();
				ClearBackground(RAYWHITE);
				DrawText(TextFormat("ERROR: Couldn't load %s.", filename), 20, 20, 20, BLACK);
			EndDrawing();
		}
		return 10;
	}
	
	unsigned numFrames = 6;
	int frameWidth = scarfy.width / numFrames;
	Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)scarfy.height };
	Vector2 scarfyPosition = {screenWidth / 2.0f, screenHeight / 2.0f};
    Vector2 scarfyVelocity = {0.0f,0.0f};
	
	unsigned frameDelay = 5;
	unsigned frameDelayCounter = 0;
	unsigned frameIndex = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		// Update
		if (IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
			scarfyVelocity.x = scarfySpeed;
			if(frameRec.width < 0) {
				frameRec.width = -frameRec.width;
			}
        } else if (IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
			scarfyVelocity.x = -scarfySpeed;
			if(frameRec.width > 0) {
				frameRec.width = -frameRec.width;
			}
		} else {
			scarfyVelocity.x = 0;
		}
		bool scarfyMoving = scarfyVelocity.x != 0.0f || scarfyVelocity.y != 0.0f;
        //----------------------------------------------------------------------------------
		scarfyPosition = Vector2Add(scarfyPosition, scarfyVelocity);
		
		++frameDelayCounter;
		if(frameDelayCounter > frameDelay) {
			frameDelayCounter = 0;
			
			if(scarfyMoving) {
				++frameIndex;
				frameIndex %= numFrames;
				frameRec.x = (float) frameWidth * frameIndex;
			}
		}
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
			
			DrawTextureRec(scarfy, frameRec, scarfyPosition, WHITE);
            

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