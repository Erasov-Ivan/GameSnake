#pragma once
#include "result.h"
#include "structs.h"

void CreateFood(Result* result, Snake* snake);
void GenerateFoodPosition(Result* result, Snake* snake, Food* food);
void DrawFood(Result* result, Food* food);
void DeleteFood(Result* result, Food* food);
