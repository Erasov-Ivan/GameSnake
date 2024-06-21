#include "scenes.h"


void PlayingProcess(Result* result, Snake* snake, Food* food, Camera2D camera) {
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
    int pause_res = 0;
    int count = 0;
    while (1) {
        //KEY_RIGHT
        if (IsKeyDown(262)) {
            if (snake->direction->x != -1) {
                snake->direction->x = 1;
                snake->direction->y = 0;
            }
        }
        //KEY_LEFT
        if (IsKeyDown(263)) {
            if (snake->direction->x != 1) {
                snake->direction->x = -1;
                snake->direction->y = 0;
            }
        }
        //KEY_DOWN
        if (IsKeyDown(264)) {
            if (snake->direction->y != -1) {
                snake->direction->x = 0;
                snake->direction->y = 1;
            }
        }
        //KEY_UP
        if (IsKeyDown(265)) {
            if (snake->direction->y != 1) {
                snake->direction->x = 0;
                snake->direction->y = -1;
            }
        }
        //SPACE
        if (IsKeyPressed(32)) {
            pause_res = PauseMenu(camera);
            if (pause_res == 1) {
                result->result = -3;
                break;
            }
        }

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        count++;
        if (count == 5) {
            count = 0;
            MoveSnake(result, snake, food);
            if (result->error) {
                PrintErrorCode(result->error_code);
                return 0;
            }
            if (result->result == -2) {
                return;
            }
        }
        DrawSnake(result, snake);
        if (result->error) {
            PrintErrorCode(result->error_code);
            return 0;
        }
        DrawFood(result, food);
        if (result->error) {
            PrintErrorCode(result->error_code);
            return 0;
        }


        EndMode2D();
        EndDrawing();
     //----------------------------------------------------------------------------------
    }
}


void MainMenu(Result* result, Camera2D camera, bool is_after_skins, bool is_after_playing) {
    if (!result) {
        printf("%s\n", ERROR_CODE_0);
        exit(1);
    }

    Rectangle ButtonStart = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };
    Rectangle ButtonSkins = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 3, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };
    Rectangle ButtonExit = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 5, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };
    while (1) {
        if (IsMouseButtonPressed(0)) {
            if (CheckCollisionPointRec(GetMousePosition(), ButtonStart)) {
                result->error = false;
                result->error_code = -1;
                result->result = 1;
                break;
            }
            if (CheckCollisionPointRec(GetMousePosition(), ButtonSkins)) {
                if (is_after_playing) { is_after_playing = false; }
                else {
                    result->error = false;
                    result->error_code = -1;
                    result->result = 2;
                    break;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), ButtonExit)) {
                if (is_after_skins) { is_after_skins = false; }
                else {
                    result->error = false;
                    result->error_code = -1;
                    result->result = 3;
                    break;
                }
            }
        }
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);
        
        DrawRectangle(100, 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, LIGHTGRAY);
        DrawRectangleRec(ButtonStart, GRAY);
        DrawText("  start", ButtonStart.x, ButtonStart.y, SCREEN_HEIGHT / 7, BLACK);
        DrawRectangleRec(ButtonSkins, GRAY);
        DrawText("  skins", ButtonSkins.x, ButtonSkins.y, SCREEN_HEIGHT / 7, BLACK);
        DrawRectangleRec(ButtonExit, GRAY);
        DrawText("   exit", ButtonExit.x, ButtonExit.y, SCREEN_HEIGHT / 7, BLACK);

        EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}

void SkinsMenu(Result* result, Camera2D camera, int skin_code) {
    Rectangle ButtonBack = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 3, SCREEN_WIDTH / 6 - 5, SCREEN_HEIGHT / 7 };
    Rectangle ButtonNext = (Rectangle){ SCREEN_WIDTH / 3 + SCREEN_WIDTH / 6 + 5, SCREEN_HEIGHT / 7 * 3, SCREEN_WIDTH / 6 - 5, SCREEN_HEIGHT / 7 };
    Rectangle ButtonExit = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 5, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };
    CreateSnakeForSkins(result);
    if (result->error) {
        return;
    }
    Snake* snake = result->result;
    snake->skin_code = skin_code;
    bool first_time = true;
    while (1) {
        if (IsMouseButtonPressed(0)) {
            if (CheckCollisionPointRec(GetMousePosition(), ButtonBack)) {
                if (first_time) { first_time = false; }
                else {
                    skin_code++;
                    if (skin_code > 11) {
                        skin_code = 0;
                    }
                    snake->skin_code = skin_code;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), ButtonNext)) {
                if (first_time) { first_time = false; }
                else {
                    skin_code--;
                    if (skin_code < 0) {
                        skin_code = 11;
                    }
                    snake->skin_code = skin_code;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), ButtonExit)) {
                result->error = false;
                result->error_code = -1;
                result->result = skin_code;
                break;
            }
        }
        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);

        DrawRectangle(100, 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, LIGHTGRAY);
        DrawRectangleRec(ButtonBack, GRAY);
        DrawText(" <-", ButtonBack.x, ButtonBack.y, SCREEN_HEIGHT / 7, BLACK);
        DrawRectangleRec(ButtonNext, GRAY);
        DrawText("  ->", ButtonNext.x, ButtonNext.y, SCREEN_HEIGHT / 7, BLACK);
        DrawRectangleRec(ButtonExit, GRAY);
        DrawText("   exit", ButtonExit.x, ButtonExit.y, SCREEN_HEIGHT / 7, BLACK);
        DrawSnake(result, snake);
        if (result->error) {
            break;
        }


        EndMode2D();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    DeleteSnake(result, snake);
}

int PauseMenu(Camera2D camera) {
    Rectangle ButtonContinue = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };
    Rectangle ButtonExit = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 3, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };

    int pause_res = 0;
    while (1) {
        if (IsMouseButtonPressed(0)) {
            if (CheckCollisionPointRec(GetMousePosition(), ButtonContinue)) {
                break;
            }
            if (CheckCollisionPointRec(GetMousePosition(), ButtonExit)) {
                pause_res = 1;
                break;
            }
        }
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);
        DrawRectangle(100, 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, (Color) { 200, 200, 200, 100 });
        DrawRectangleRec(ButtonContinue, GRAY);
        DrawText("continue", ButtonContinue.x, ButtonContinue.y, SCREEN_HEIGHT / 7, BLACK);
        DrawRectangleRec(ButtonExit, GRAY);
        DrawText("   exit", ButtonExit.x, ButtonExit.y, SCREEN_HEIGHT / 7, BLACK);
        EndMode2D();
        EndDrawing();
    }
    return pause_res;
}

void GameOver(Camera2D camera, int score) {
    Rectangle ButtonExit = (Rectangle){ SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 3, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 };

    while (1) {
        if (IsMouseButtonPressed(0)) {
            if (CheckCollisionPointRec(GetMousePosition(), ButtonExit)) {
                break;
            }
        }
        char* buff[10];
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(WHITE);
        DrawRectangle(100, 100, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, (Color) { 200, 200, 200, 100 });
        DrawText("Game over", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7, SCREEN_HEIGHT / 15, BLACK);
        DrawText("Your score: ", SCREEN_WIDTH / 3, SCREEN_HEIGHT / 7 * 2, SCREEN_HEIGHT / 15, BLACK);
        DrawText(_itoa(score, buff, 10, 10), SCREEN_WIDTH / 3 * 2 - 100, SCREEN_HEIGHT / 7 * 2, SCREEN_HEIGHT / 15, BLACK);
        DrawRectangleRec(ButtonExit, GRAY);
        DrawText("   ok", ButtonExit.x, ButtonExit.y, SCREEN_HEIGHT / 7, BLACK);
        EndMode2D();
        EndDrawing();
    }
}