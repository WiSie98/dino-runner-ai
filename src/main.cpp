#include <cstdlib>

#include "raylib.h"
#include "config.h"

#include "core/headerfiles/header.h"
#include "scenes/headerfiles/scenes.h"
#include "core/headerfiles/scene_manager.h"
#include "actors/headerfiles/actor_player.h"
#include "actors/headerfiles/actor_ai.h"
#include "core/headerfiles/camera.h"

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    unsigned int target_fps = 60;       // Flag to set the Target FPS
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;            // Flag to set window to exit

    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    InitAudioDevice();
    SetTargetFPS(target_fps);
    SetExitKey(KEY_F4);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    Texture2D actor_texture = LoadTexture("assets/graphics/spritesheets/vp_sptsht_player.png");

    SceneManager sceneManager;
    GenerateScenes(&sceneManager.getScenes());
    sceneManager.switchToScene(START_SCENE);

    ActorPlayer player(STARTASPLAYER, actor_texture);
    MainCamera mainCamera(2.0f, 0.0f);

    std::vector<ActorAI> ai_vector;

    for (int i = 0; i < NUMOFAI; i++) {
        ActorAI ai(true, 4, 8, 3, actor_texture);
        ai_vector.push_back(ai);
    }

    // Main game loop
    while (!exitWindow) {
        // Updates that are made by frame are coded here
        if (WindowShouldClose() || exitWindowRequested) {
            exitWindow = true;
        }

        sceneManager.switchToScene(sceneManager.getCurrentScene()->setNextScene(player, ai_vector, exitWindowRequested));
        sceneManager.update(player, ai_vector, mainCamera);

        BeginDrawing();
            // You can draw on the screen between BeginDrawing() and EndDrawing()
            ClearBackground(BLACK);
            sceneManager.draw(player, ai_vector, mainCamera);

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadTexture(actor_texture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
