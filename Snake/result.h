#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include "raylib.h"

#define ERROR_CODE_0 "Got null pointer"
#define ERROR_CODE_1 "Error during memory allocation"
#define ERROR_CODE_13 "How you did this? It's impossible"
#define UNKNOWN_ERROR "Unknown error_code"


typedef struct Result {
	bool error;
	int error_code;
	void* result;
}Result;

void PrintErrorCode(int error_code);
bool CheckResult(Result* result);
