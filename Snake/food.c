#include "food.h"


void GenerateFoodPosition(Result* result, Snake* snake, Food* food) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	if (!snake) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	if (snake->body_lenght < 1) {
		result->error = true;
		result->error_code = 13;
		return;
	}
	if (!snake->body || !snake->head) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	if (!food) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	bool ex = true;
	while (1) {
		ex = true;
		food->position.x = (rand() % (SCREEN_WIDTH / SEGMENT_SIZE)) * SEGMENT_SIZE;
		food->position.y = (rand() % (SCREEN_HEIGHT / SEGMENT_SIZE)) * SEGMENT_SIZE;
		if (food->position.x == snake->head->x && food->position.y == snake->head->y) {
			ex = false;
		}
		else {
			for (unsigned int i = 0; i < snake->body_lenght; i++) {
				if (food->position.x == snake->body[i]->x && food->position.y == snake->body[i]->y) {
					ex = false;
					break;
				}
			}
		}
		if (ex) {
			break;
		}
	}
	result->error = false;
}

void CreateFood(Result* result, Snake* snake) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	if (!snake) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	if (snake->body_lenght < 1) {
		result->error = true;
		result->error_code = 13;
		return;
	}
	if (!snake->body || !snake->head) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	Food* food = (Food*)malloc(sizeof(Food));
	if (!food) {
		result->error = true;
		result->error_code = 1;
		return;
	}
	food->texture = LoadTexture("strawberry.png");
	GenerateFoodPosition(result, snake, food);
	result->result = food;
}

void DrawFood(Result* result, Food* food) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	if (!food) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	DrawTextureV(food->texture, food->position, WHITE);
	result->error = false;
}

void DeleteFood(Result* result, Food* food) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	if (!food) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	free(food);
	result->error = false;
}