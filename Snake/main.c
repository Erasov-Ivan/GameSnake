#include "raylib.h"
#include "malloc.h"
#include <stdio.h> 
#include <stdlib.h>
#include "structs.h"
#include "snake.h"
#include "food.h"
#include "scenes.h"
#include "result.h"


int main()
{
    srand(time(0));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    Result* result = (Result*)malloc(sizeof(Result));
    if (!result) {
        exit(1);
    }
    CreateSnake(result, 0);
    if (CheckResult(result)) { return 0; }
    Snake* snake = result->result;

    CreateFood(result, snake);
    if (CheckResult(result)) { return 0; }
    Food* food = result->result;

    Sound audio = LoadSound("audio.mp3");
    SetSoundVolume(audio, 1.0);
    PlaySound(audio);

    bool is_after_skins = false;
    bool is_after_playing = false;
    int skin_code = 0;

    SetTargetFPS(60);

    while (1)
    {
        MainMenu(result, camera, is_after_skins, is_after_playing);
        is_after_skins = false;
        is_after_playing = false;
        if (CheckResult(result)) { break; }
        if (result->result == 3) {
            break;
        }
        if (result->result == 1) {
            PlayingProcess(result, snake, food, camera);
            if (CheckResult(result)) { break; }
            if (result->result == -2 || result->result == -3) {
                is_after_playing = true;
                GameOver(camera, snake->body_lenght - 1);
                // Reseting 
                skin_code = snake->skin_code;
                DeleteSnake(result, snake);
                if (CheckResult(result)) { break; }
                CreateSnake(result, skin_code);
                if (CheckResult(result)) { break; }
                snake = result->result;
                GenerateFoodPosition(result, snake, food);
                if (CheckResult(result)) { break; }
            }
        }
        if (result->result == 2) {
            if (CheckResult(result)) { break; }
            SkinsMenu(result, camera, snake->skin_code);
            is_after_skins = true;
            if (CheckResult(result)) { break; }
            if (result->result != NULL) {
                snake->skin_code = result->result;
            }
        }
    }

    StopSound(audio);
    DeleteSnake(result, snake);
    if (CheckResult(result)) { return 0; }
    DeleteFood(result, food);
    if (CheckResult(result)) { return 0; }
    free(result);
    CloseWindow();
    return 0;
}