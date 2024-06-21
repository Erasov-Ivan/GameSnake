#include <stdlib.h>
#include "structs.h"
#include "result.h"

void PrintErrorCode(int error_code) {
    switch (error_code)
    {
    case 0:
        printf("%s", ERROR_CODE_0);
        break;
    case 1:
        printf("%s", ERROR_CODE_1);
        break;
    case 13:
        printf("%s", ERROR_CODE_13);
        break;
    default:
        printf("%s", UNKNOWN_ERROR);
        break;
    }
}

bool CheckResult(Result* result) {
    if (!result) {
        PrintErrorCode(0);
        return true;
    }
    if (result->error) {
        PrintErrorCode(result->error_code);
        return true;
    }
    return false;
}