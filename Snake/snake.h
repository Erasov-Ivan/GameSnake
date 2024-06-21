#pragma once
#include "structs.h"
#include "result.h"
#include "raylib.h"

void CreateSnake(Result* result, int skin_code);
void CreateSnakeForSkins(Result* result);
void MoveSnake(Result* result, Snake* snake, Food* food);
void DrawSnake(Result* result, Snake* snake);
void DeleteSnake(Result* result, Snake* snake);
Color GenerateColor(int skin_code, int body_lenght, int position);
