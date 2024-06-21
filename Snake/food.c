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
	Texture* tmp = (Texture*)malloc(16 * sizeof(Texture));
	if (!tmp) {
		result->error = true;
		result->error_code = 1;
		return;
	}
	food->texture = tmp;
	food->texture[0] = LoadTexture("strawberry/1.png");
	food->texture[1] = LoadTexture("strawberry/2.png");
	food->texture[2] = LoadTexture("strawberry/3.png");
	food->texture[3] = LoadTexture("strawberry/4.png");
	food->texture[4] = LoadTexture("strawberry/5.png");
	food->texture[5] = LoadTexture("strawberry/6.png");
	food->texture[6] = LoadTexture("strawberry/7.png");
	food->texture[7] = LoadTexture("strawberry/8.png");
	food->texture[8] = LoadTexture("strawberry/9.png");
	food->texture[9] = LoadTexture("strawberry/10.png");
	food->texture[10] = LoadTexture("strawberry/11.png");
	food->texture[11] = LoadTexture("strawberry/12.png");
	food->texture[12] = LoadTexture("strawberry/13.png");
	food->texture[13] = LoadTexture("strawberry/14.png");
	food->texture[14] = LoadTexture("strawberry/15.png");
	food->texture[15] = LoadTexture("strawberry/16.png");

	food->frame = 0;
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
	DrawTextureV(food->texture[div(food->frame, 5).quot], food->position, WHITE);
	food->frame++;
	if (div(food->frame, 5).quot > 15) { food->frame = 0; }
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
	if (!food->texture) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	free(food->texture);
	free(food);
	result->error = false;
}
