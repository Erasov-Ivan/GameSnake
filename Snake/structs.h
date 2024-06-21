#pragma once
#include "raylib.h"

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 1000
#define SEGMENT_SIZE 50


typedef struct Snake {
	Vector2* head;
	Vector2** body;
	int body_lenght;
	Vector2* direction;
	int skin_code;
}Snake;

typedef struct Food {
	Vector2 position;
	Texture* texture;
	int frame;
}Food;
