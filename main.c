/*******************************************************************************************
*
*   raylib [core] example - Basic window
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

#include <stddef.h>
#include <stdlib.h>

const int screenWidth = 1600;
const int screenHeight = 900;

const int scarfySpeed = 10;
const int gravity = 1;
const int groundYPos = (3 * screenHeight) / 4;

const int jumpUpFrame = 3;
const int jumpDownFrame = 4;
const int footstepFrame1 = 1;
const int footstepFrame2 = 4;

bool isFootstepFrame(int frameIndex) {
	
	if(frameIndex == footstepFrame1 || frameIndex == footstepFrame2) {
		return true;
	} else {
		return false;
	}
}

bool isScarfyOnGround(Texture2D *scarfy, Vector2 *scarfyPosition) {
	if(scarfyPosition->y + scarfy->height >= groundYPos) {
		return true;
	} else {
		return false;
	}
}

/** Returns true if the texture is valid (e.g., was loaded).
 */
bool isTextureValid(const Texture2D *texture) {
	return texture->id > 0;
}

/** Displays a single line error message, and exits when the user pushes ESCape, or the window's close
 * button.
 */
void showErrorAndExit(const char *errMsg) {
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText(errMsg, 20, 20, 20, BLACK);
		EndDrawing();
	}
	
	exit(EXIT_FAILURE);
}

void showCantLoadFileErrorAndExit(const char *filename) {
	showErrorAndExit(TextFormat("ERROR: Couldn't load %s.", filename));
}

void cleanup() {
	CloseAudioDevice(); 

    CloseWindow();        // Close window and OpenGL context
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    

    InitWindow(screenWidth, screenHeight, "RayLib - 2D Character Animation");
	
	InitAudioDevice();
	
	atexit(cleanup);

	const char *filename = "scarfy.png";
	Texture2D scarfy = LoadTexture(filename);
	if(!isTextureValid(&scarfy)) {
		showCantLoadFileErrorAndExit(filename);
	}
	unsigned numFrames = 6;
	int frameWidth = scarfy.width / numFrames;
	Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)scarfy.height };
	Vector2 scarfyPosition = {screenWidth / 2.0f, groundYPos - scarfy.height};
    Vector2 scarfyVelocity = {0.0f,0.0f};
	
	filename = "Single-footstep-in-grass-A-www.fesliyanstudios.com.mp3";
	Sound footstepSound = LoadSound(filename);
	if(!footstepSound.frameCount) {
		showCantLoadFileErrorAndExit(filename);
	}
	filename = "Single-footstep-in-grass-B-www.fesliyanstudios.com.mp3";
	Sound landingSound = LoadSound(filename);
	if(!landingSound.frameCount) {
		showCantLoadFileErrorAndExit(filename);
	}
	
	unsigned frameDelay = 5;
	unsigned frameDelayCounter = 0;
	unsigned frameIndex = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		// Update
		if (isScarfyOnGround(&scarfy, &scarfyPosition)) {
			if (IsKeyDown(KEY_UP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
				scarfyVelocity.y = - 2 * scarfySpeed;
			}
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
		}
		
		bool scarfyMoving = scarfyVelocity.x != 0.0f || scarfyVelocity.y != 0.0f;
        //----------------------------------------------------------------------------------
		
		bool wasScarfyOnGround = isScarfyOnGround(&scarfy, &scarfyPosition);
		scarfyPosition = Vector2Add(scarfyPosition, scarfyVelocity);
		bool scarfyIsOnGround = isScarfyOnGround(&scarfy, &scarfyPosition);
		if(scarfyIsOnGround) {
			scarfyVelocity.y = 0;
			scarfyPosition.y = groundYPos - scarfy.height;
			if(!wasScarfyOnGround) {
				PlaySound(landingSound);
			}
		} else {
			scarfyVelocity.y += gravity;
		}
		
		++frameDelayCounter;
		if(frameDelayCounter > frameDelay) {
			frameDelayCounter = 0;
			
			if(scarfyMoving) {
				if(scarfyIsOnGround) {
					++frameIndex;
					frameIndex %= numFrames;
					
					if(isFootstepFrame(frameIndex)) {
						PlaySound(footstepSound);
					}
				} else {
					if(scarfyVelocity.y < 0) {
						frameIndex = jumpUpFrame;
					} else {
						frameIndex = jumpDownFrame;
					}
				}
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

	cleanup();
	atexit(NULL);
    //--------------------------------------------------------------------------------------

    return EXIT_SUCCESS;
}