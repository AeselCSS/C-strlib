#include <stddef.h>  // For NULL definition
#include <stdbool.h> // For bool definition
#include <stdio.h>
#include <stdlib.h>  // For malloc and free
#include <string.h>  // For strncpy, strncat, and strcmp
#include "strlib.h"

// List of common Unicode whitespace code points
const int unicodeWhitespace[] = { 
    0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x0020, 0x0085, 0x00A0, 0x1680, 
    0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007, 0x2008, 0x2009, 0x200A, 
    0x2028, 0x2029, 0x202F, 0x205F, 0x3000
};

StrError str_last_error = STR_SUCCESS;

// Copies characters from src to dest from start to end
StrError str_copyRange(const char* src, int start, int end, char* dest) {
    if (!src || !dest) return (str_last_error = STR_ERROR_NULL_INPUT);
    
    int i = 0;
    while (*src && i < start) {
        str_getUTF8CodePoint(&src);
        i++;
    }
    
    while (*src && i < end) {
        const char* srcStart = src;
        str_getUTF8CodePoint(&src);
        int len = src - srcStart;
        strncpy(dest, srcStart, len);
        dest += len;
        i++;
    }
    
    *dest = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Finds the first occurrence of a substring in a string
const char* str_find(const char* str, const char* substr, int start) {
    if (!str || !substr) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return NULL;
    }
    if (start < 0) {
        str_last_error = STR_ERROR_INVALID_INDEX;
        return NULL;
    }

    int i = 0;
    while (*str && i < start) {
        str_getUTF8CodePoint(&str);
        i++;
    }

    return str_findHelper(str, substr);
}

// Helper function to find the substring in the string
const char* str_findHelper(const char* str, const char* substr) {
    if (!str || !substr) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return NULL;
    }

    while (*str) {
        const char* tempStr = str;
        const char* tempSubstr = substr;
        int matched = 1;
        
        while (*tempSubstr && *tempStr) {
            int codePoint1 = str_getUTF8CodePoint(&tempStr);
            int codePoint2 = str_getUTF8CodePoint(&tempSubstr);
            if (codePoint1 != codePoint2) {
                matched = 0;
                break;
            }
        }

        if (matched && *tempSubstr == '\0') return str;
        
        str_getUTF8CodePoint(&str);
    }
    str_last_error = STR_SUCCESS;
    return NULL;
}

// Copies characters from src to dest until the delimiter is found
StrError str_copyUntil(const char* src, const char* delimiter, char* dest) {
    if (!src || !delimiter || !dest) return (str_last_error = STR_ERROR_NULL_INPUT);

    const char* pos = str_find(src, delimiter, 0);
    while (*src && src != pos) {
        const char* srcStart = src;
        str_getUTF8CodePoint(&src);
        int len = src - srcStart;
        strncpy(dest, srcStart, len);
        dest += len;
    }
    
    *dest = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Checks if a Unicode code point is a whitespace character
int str_isUnicodeWhitespace(int codePoint) {
    int size = sizeof(unicodeWhitespace) / sizeof(unicodeWhitespace[0]);
    for (int i = 0; i < size; i++) {
        if (unicodeWhitespace[i] == codePoint) return 1;
    }
    return 0;
}

// Checks if a character is a whitespace character
int str_isWhitespace(const char* str) {
    if (!str) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return 0;
    }

    int codePoint = str_getUTF8CodePoint(&str);
    return (codePoint == 0x20 || codePoint == 0x09 || codePoint == 0x0A || 
            codePoint == 0x0D || str_isUnicodeWhitespace(codePoint));
}

// Validates if a string is valid UTF-8
bool str_isValidUTF8(const char* str) {
    if (!str) return false;

    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == -1 || (seqLen == 4 && str_getCodePointFromBytes(str, seqLen) > 0x10FFFF)) {
            return false;
        }
    }
    return true;
}

// Gets the length of the UTF-8 sequence starting with a byte
int str_getUTF8SequenceLength(unsigned char byte) {
    if (byte <= 0x7F) return 1;
    else if ((byte & 0xE0) == 0xC0) return 2;
    else if ((byte & 0xF0) == 0xE0) return 3;
    else if ((byte & 0xF8) == 0xF0) return 4;
    return -1;
}

// Returns the code point from a sequence of UTF-8 bytes
int str_getCodePointFromBytes(const char* str, int seqLen) {
    if (!str || seqLen < 1 || seqLen > 4) return -1;

    int codePoint = 0;
    if (seqLen == 1) return *str;
    if (seqLen == 2) {
        codePoint = (*str & 0x1F) << 6;
        codePoint |= (*(str + 1) & 0x3F);
    } else if (seqLen == 3) {
        codePoint = (*str & 0x0F) << 12;
        codePoint |= (*(str + 1) & 0x3F) << 6;
        codePoint |= (*(str + 2) & 0x3F);
    } else if (seqLen == 4) {
        codePoint = (*str & 0x07) << 18;
        codePoint |= (*(str + 1) & 0x3F) << 12;
        codePoint |= (*(str + 2) & 0x3F) << 6;
        codePoint |= (*(str + 3) & 0x3F);
    }
    return codePoint;
}

// Gets the Unicode code point from the start of the string and advances the pointer
int str_getUTF8CodePoint(const char** str) {
    if (!str || !*str) return -1;

    unsigned char byte = (unsigned char)**str;
    int seqLen = str_getUTF8SequenceLength(byte);
    if (seqLen == -1) return -1;

    int codePoint = str_getCodePointFromBytes(*str, seqLen);
    *str += seqLen;
    return codePoint;
}

// Returns the length of the string in code points
int str_length(const char* str) {
    if (!str) return -1;

    int length = 0;
    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == -1) return -1;
        length++;
    }
    return length;
}

// Returns the character at a specific index in a string
char* str_charAt(const char* str, int index) {
    if (!str || index < 0) return NULL;

    int i = 0;
    const char* start;
    while (*str) {
        start = str;
        str_getUTF8CodePoint(&str);
        if (i == index) {
            int len = str - start;
            char* result = malloc(len + 1);
            if (!result) return NULL;
            strncpy(result, start, len);
            result[len] = '\0';
            return result;
        }
        i++;
    }
    return NULL;
}

// Returns the ASCII value of the character at a specific index in a string
int str_charCodeAt(const char* str, int index) {
    if (!str) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return -1;
    }
    if (index < 0) {
        str_last_error = STR_ERROR_INVALID_INDEX;
        return -1;
    }

    int i = 0;
    while (*str) {
        int codePoint = str_getUTF8CodePoint(&str);
        if (i == index) {
            str_last_error = STR_SUCCESS;
            return codePoint;
        }
        i++;
    }
    str_last_error = STR_ERROR_INVALID_INDEX;
    return -1;
}

// Returns the index of the first occurrence of a substring in a string
int str_indexOf(const char* str, const char* substr) {
    if (!str || !substr) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return -1;
    }

    int i = 0;
    while (*str) {
        if (str_findHelper(str, substr)) {
            str_last_error = STR_SUCCESS;
            return i;
        }
        str_getUTF8CodePoint(&str);
        i++;
    }

    str_last_error = STR_SUCCESS;
    return -1;
}

// Returns the index of the last occurrence of a substring in a string
int str_lastIndexOf(const char* str, const char* substr) {
    if (!str || !substr) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return -1;
    }

    int lastIndex = -1;
    int index = 0;
    while (*str) {
        const char* pos = str_find(str, substr, index);
        if (pos) {
            lastIndex = pos - str;
            index = lastIndex + 1;
        } else {
            break;
        }
    }
    return lastIndex;
}

// Joins two strings together
StrError str_concat(const char* str1, const char* str2, char* result) {
    if (!str1 || !str2 || !result) return (str_last_error = STR_ERROR_NULL_INPUT);

    while (*str1) {
        int seqLen = str_getUTF8SequenceLength((unsigned char)*str1);
        strncpy(result, str1, seqLen);
        result += seqLen;
        str1 += seqLen;
    }

    while (*str2) {
        int seqLen = str_getUTF8SequenceLength((unsigned char)*str2);
        strncpy(result, str2, seqLen);
        result += seqLen;
        str2 += seqLen;
    }

    *result = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Converts the entire string to lowercase
StrError str_toLowerCase(char* str) {
    if (!str) return (str_last_error = STR_ERROR_NULL_INPUT);

    const char* src = str;
    while (*str) {
        int codePoint = str_getUTF8CodePoint(&src);
        if (codePoint >= 'A' && codePoint <= 'Z') {
            *str = *str + 32;  // Convert ASCII uppercase to lowercase
        }
        str++;
    }

    return (str_last_error = STR_SUCCESS);
}

// Converts the entire string to uppercase
StrError str_toUpperCase(char* str) {
    if (!str) return (str_last_error = STR_ERROR_NULL_INPUT);

    const char* src = str;
    while (*str) {
        int codePoint = str_getUTF8CodePoint(&src);
        if (codePoint >= 'a' && codePoint <= 'z') {
            *str = *str - 32;  // Convert ASCII lowercase to uppercase
        }
        str++;
    }

    return (str_last_error = STR_SUCCESS);
}

// Removes leading whitespace from a string
StrError str_trimStart(char* str) {
    if (!str) return (str_last_error = STR_ERROR_NULL_INPUT);

    const char* start = str;
    while (*start && str_isWhitespace(start)) {
        str_getUTF8CodePoint(&start);
    }
    memmove(str, start, strlen(start) + 1);
    return (str_last_error = STR_SUCCESS);
}

// Removes trailing whitespace from a string
StrError str_trimEnd(char* str) {
    if (!str || !*str) return (str_last_error = STR_ERROR_NULL_INPUT);

    char* end = str + strlen(str);
    char* last = end - 1;

    while (last >= str) {
        while (last > str && (*last & 0xC0) == 0x80) {
            last--;
        }
        
        if (!str_isWhitespace(last)) break;
        
        end = last;
        last = end - 1;
    }

    *end = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Trims whitespace from both ends of the string
StrError str_trim(char* str) {
    str_trimStart(str);
    str_trimEnd(str);
    return (str_last_error = STR_SUCCESS);
}

// Repeats a string a given number of times
StrError str_repeat(const char* str, int count, char* result) {
    if (!str || !result) return (str_last_error = STR_ERROR_NULL_INPUT);
    if (count < 0) return (str_last_error = STR_ERROR_INVALID_INDEX);

    int strLen = str_length(str);
    if (strLen == -1) return (str_last_error = STR_ERROR_INVALID_UTF8);

    for (int i = 0; i < count; i++) {
        strncpy(result, str, strLen);
        result += strLen;
    }

    *result = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Check if a string starts with a given prefix
int str_startsWith(const char* str, const char* prefix) {
    if (!str || !prefix) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return 0;
    }

    while (*prefix) {
        if (*str++ != *prefix++) return 0;
    }

    return 1;
}

// Check if a string ends with a given suffix
int str_endsWith(const char* str, const char* suffix) {
    if (!str || !suffix) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return 0;
    }

    int strLen = str_length(str);
    int suffixLen = str_length(suffix);

    if (suffixLen > strLen) return 0;

    str += strLen - suffixLen;

    while (*suffix) {
        if (*str++ != *suffix++) return 0;
    }

    return 1;
}

// Check if a string includes a given substring
int str_includes(const char* str, const char* substr) {
    if (!str || !substr) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return 0;
    }

    return str_indexOf(str, substr) != -1;
}

// Extracts a substring from a string and stores it in result
void str_slice(const char* str, int start, int end, char* result) {
    if (!str || !result) {
        str_last_error = STR_ERROR_NULL_INPUT;
        return;
    }

    int i = 0;
    while (*str && i < start) {
        str_getUTF8CodePoint(&str);
        i++;
    }

    while (*str && i < end) {
        int seqLen = str_getUTF8SequenceLength((unsigned char)*str);
        strncpy(result, str, seqLen);
        result += seqLen;
        str += seqLen;
        i++;
    }

    *result = '\0';
}

// Extracts a substring from a string and stores it in result
StrError str_substring(const char* str, int start, int end, char* result) {
    if (!str || !result) return (str_last_error = STR_ERROR_NULL_INPUT);

    int i = 0;
    const char* startPtr = str;
    
    while (*str && i < start) {
        str_getUTF8CodePoint(&str);
        i++;
    }

    startPtr = str;

    while (*str && i < end) {
        str_getUTF8CodePoint(&str);
        i++;
    }

    str_copyRange(startPtr, 0, str - startPtr, result);
    return (str_last_error = STR_SUCCESS);
}


// Pads a string with a given character at the start to reach a target length
StrError str_padStart(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize) {
    if (!str || !padStr || !result) return (str_last_error = STR_ERROR_NULL_INPUT);

    int strLen = str_length(str);
    int padLen = str_length(padStr);
    if (targetLength <= strLen || targetLength >= resultSize) return (str_last_error = STR_ERROR_INVALID_INDEX);

    char temp[resultSize];
    temp[0] = '\0';

    int padCount = targetLength - strLen;
    while (padCount > padLen) {
        str_concat(temp, padStr, temp);
        padCount -= padLen;
    }
    while (padCount-- > 0) strncat(temp, padStr, 1);

    str_concat(temp, str, result);
    return (str_last_error = STR_SUCCESS);
}

// Pads a string with a given character at the end to reach a target length
StrError str_padEnd(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize) {
    if (!str || !padStr || !result) return (str_last_error = STR_ERROR_NULL_INPUT);

    int strLen = str_length(str);
    int padLen = str_length(padStr);
    if (targetLength >= resultSize) return (str_last_error = STR_ERROR_MEMORY_ALLOCATION);

    str_concat(str, "", result);

    int padCount = targetLength - strLen;
    while (padCount > padLen) {
        str_concat(result, padStr, result);
        padCount -= padLen;
    }
    while (padCount-- > 0) strncat(result, padStr, 1);

    result[targetLength] = '\0';
    return (str_last_error = STR_SUCCESS);
}

// Replaces all occurrences of a substring with another substring in a string
StrError str_replace(const char* str, const char* searchValue, const char* newValue, char* result) {
    if (!str || !searchValue || !newValue || !result) return (str_last_error = STR_ERROR_NULL_INPUT);

    const char* pos = str;
    int searchLenBytes = strlen(searchValue);
    int newValueLenBytes = strlen(newValue);

    while ((pos = str_findHelper(pos, searchValue)) != NULL) {
        int bytesToCopy = pos - str;
        strncpy(result, str, bytesToCopy);
        result += bytesToCopy;
        strcpy(result, newValue);
        result += newValueLenBytes;
        str = pos + searchLenBytes;
        pos = str;
    }

    strcpy(result, str);
    return (str_last_error = STR_SUCCESS);
}
