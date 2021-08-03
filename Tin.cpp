#include "Tin.h"

// Task 3
bool checkMinusOperator (string inputString) {
    regex operator_Minus("(.*)( -)(.*)");
    if (regex_match(inputString, operator_Minus))
        return true;
    return false;
}
// Task 8
bool checkHashtagsOperator (string inputString) {
    regex operator_Hashtags("(#)(.*)");
    if (regex_match(inputString, operator_Hashtags))
        return true;
    return false;
}

// Task 11
bool checkRangeOperator (string inputString) {
    regex operator_Range("(.*)(..)(.*)");
    if (regex_match(inputString, operator_Range))
        return true;
    return false;
}
