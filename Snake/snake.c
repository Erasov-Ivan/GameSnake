#include "snake.h"


void CreateSnakeForSkins(Result* result) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	Snake* snake = (Snake*)malloc(sizeof(Snake));
	Vector2* head = (Vector2*)malloc(sizeof(Vector2));
	Vector2** body = (Vector2**)malloc(0);
	Vector2* direction = (Vector2*)malloc(sizeof(Vector2));
	if (!snake || !head || !body || !direction) {
		result->error = true;
		result->error_code = 1;
		return;
	}
	head->x = SCREEN_WIDTH / 3;
	head->y = SCREEN_HEIGHT / 6;
	snake->head = head;
	direction->x = -1;
	direction->y = 0;
	snake->body = body;
	snake->body_lenght = 0;
	snake->direction = direction;
	snake->skin_code = 0;
	for (int i = SCREEN_WIDTH / 3 + SEGMENT_SIZE; i < SCREEN_WIDTH / 3 * 2; i += SEGMENT_SIZE) {
		Vector2* body_element = (Vector2*)malloc(sizeof(Vector2));
		if (!body_element) {
			result->error = true;
			result->error_code = 1;
			return;
		}
		body_element->x = i;
		body_element->y = SCREEN_HEIGHT / 6;
		Vector2** tmp = (Vector2**)realloc(snake->body, (snake->body_lenght + 1) * sizeof(Vector2*));
		if (!tmp) {
			result->error = true;
			result->error_code = 1;
			return;
		}
		snake->body = tmp;
		snake->body[snake->body_lenght] = body_element;
		snake->body_lenght += 1;
	}
	result->error = false;
	result->error_code = -1;
	result->result = snake;

}


void CreateSnake(Result* result, int skin_code) {
	if (!result) {
		printf("%s\n", ERROR_CODE_0);
		exit(1);
	}
	Snake* snake = (Snake*)malloc(sizeof(Snake));
	Vector2* head = (Vector2*)malloc(sizeof(Vector2));
	Vector2** body = (Vector2**)malloc(sizeof(Vector2*));
	Vector2* body_element = (Vector2*)malloc(sizeof(Vector2));
	Vector2* direction = (Vector2*)malloc(sizeof(Vector2));
	if (!snake || !head || !body || !body_element || !direction) {
		result->error = true;
		result->error_code = 1;
		return;
	}
	head->x = SCREEN_WIDTH / 2;
	head->y = SCREEN_HEIGHT / 2;
	snake->head = head;
	body_element->x = head->x;
	body_element->y = head->y + SEGMENT_SIZE;
	body[0] = body_element;
	direction->x = 0;
	direction->y = -1;
	snake->body = body;
	snake->body_lenght = 1;
	snake->direction = direction;
	snake->skin_code = skin_code;
	result->error = false;
	result->error_code = -1;
	result->result = snake;

}


void MoveSnake(Result* result, Snake* snake, Food* food) {
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
	if (!snake->body || !snake->head || !snake->direction) {
		result->error = true;
		result->error_code = 0;
		return;
	}
	Vector2 tmpHead;
	tmpHead.x = snake->head->x;
	tmpHead.y = snake->head->y;

	snake->head->x += snake->direction->x * SEGMENT_SIZE;
	snake->head->y += snake->direction->y * SEGMENT_SIZE;
	if (snake->head->x < 0) {
		snake->head->x = SCREEN_WIDTH - SEGMENT_SIZE;
	}
	if (snake->head->x >= SCREEN_WIDTH) {
		snake->head->x = 0;
	}
	if (snake->head->y < 0) {
		snake->head->y = SCREEN_HEIGHT - SEGMENT_SIZE;
	}
	if (snake->head->y >= SCREEN_HEIGHT) {
		snake->head->y = 0;
	}

	if (snake->head->x == food->position.x && snake->head->y == food->position.y) {
		GenerateFoodPosition(result, snake, food);
		Vector2** tmp = (Vector2**)realloc(snake->body, (snake->body_lenght + 1) * sizeof(Vector2*));
		Vector2* tmpV = (Vector2*)malloc(sizeof(Vector2));
		if (!tmp || !tmpV) {
			result->error = true;
			result->error_code = 1;
			return;
		}
		snake->body = tmp;
		snake->body[snake->body_lenght] = tmpV;
		snake->body_lenght += 1;
	}
	for (int i = (int)snake->body_lenght - 2; i >= 0; i--) {
		snake->body[i + 1]->x = snake->body[i]->x;
		snake->body[i + 1]->y = snake->body[i]->y;
	}
	snake->body[0]->x = tmpHead.x;
	snake->body[0]->y = tmpHead.y;

	for (unsigned int i = 0; i < snake->body_lenght; i++) {
		if (snake->body[i]->x == snake->head->x && snake->body[i]->y == snake->head->y) {
			result->error = false;
			result->result = -2;
			return;
		}
	}

	result->error = false;
	result->error_code = -1;
}

void DrawSnake(Result* result, Snake* snake) {
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
	DrawRectangle(snake->head->x, snake->head->y, SEGMENT_SIZE - 1, SEGMENT_SIZE - 1, GenerateColor(snake->skin_code, snake->body_lenght, 0));
	for (unsigned int i = 0; i < snake->body_lenght; i++) {
		DrawRectangle(snake->body[i]->x, snake->body[i]->y, SEGMENT_SIZE - 1, SEGMENT_SIZE - 1, GenerateColor(snake->skin_code, snake->body_lenght, i + 1));
	}
	result->error = false;
}


void DeleteSnake(Result* result, Snake* snake) {
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
	for (unsigned int i = 0; i < snake->body_lenght - 1; i++) {
		free(snake->body[i]);
	}
	free(snake->body);
	free(snake->head);
	free(snake->direction);
	free(snake);
	result->error = false;
}

Color GenerateColor(int skin_code, int body_lenght, int position) {
	Color COLORS[8] = { RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, PURPLE, BLACK };
	if (skin_code >= 0 && skin_code < 8) { return COLORS[skin_code]; }
	if (skin_code == 8) { return COLORS[position%7]; }
	if (skin_code == 9) { return (Color) { (int)(255/body_lenght*position), 0, 0, 255 }; }
	if (skin_code == 10) { return (Color) { 0, (int)(255 / body_lenght * position), 0, 255 }; }
	if (skin_code == 11) { return (Color) { 0, 0, (int)(255 / body_lenght * position), 255 }; }
	return BLACK;
}