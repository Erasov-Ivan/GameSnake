#pragma once
#pragma warning(disable : 4996)
#include "raylib.h"
#include "malloc.h"
#include <stdio.h> 
#include <stdlib.h>
#include "structs.h"
#include "snake.h"
#include "food.h"
#include "result.h"


void PrintErrorCode(int error_code);
void MainMenu(Result* result, Camera2D camera, bool is_after_skins, bool is_after_playing);
void PlayingProcess(Result* result, Snake* snake, Food* food, Camera2D camera);
void SkinsMenu(Result* result, Camera2D camera, int skin_code);
int PauseMenu(Camera2D camera);
void GameOver(Camera2D camera, int score);