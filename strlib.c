#include <stddef.h> // For NULL definition
#include <stdbool.h> // For bool definition
#include <stdio.h>

// List of common Unicode whitespace code points
const int unicodeWhitespace[] = {
    0x0009, 0x000A, 0x000B, 0x000C, 0x000D, // ASCII control characters
    0x0020, // Space
    0x0085, // Next Line
    0x00A0, // No-Break Space
    0x1680, // Ogham Space Mark
    0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007, 0x2008, 0x2009, 0x200A, // En quad to Hair space
    0x2028, 0x2029, // Line Separator and Paragraph Separator
    0x202F, // Narrow No-Break Space
    0x205F, // Medium Mathematical Space
    0x3000  // Ideographic Space
};

// ==== HELPER FUNCTIONS ====
// Copies characters from src to dest from start to end
void str_copyRange(const char* src, int start, int end, char* dest) {
    int i = 0;
    int codePoint;
    while (*src && i < start) {
        str_getUTF8CodePoint(&src);  // Advance the pointer based on code point
        i++;
    }
    while (*src && i < end) {
        const char* srcStart = src;  // Preserve the starting point of the code point
        str_getUTF8CodePoint(&src);  // Get the next code point and advance the pointer
        int len = src - srcStart;    // Calculate the number of bytes for this code point
        strncpy(dest, srcStart, len); // Copy the full code point to the destination
        dest += len;  // Advance the destination pointer
        i++;
    }
    *dest = '\0';  // Null-terminate the destination string
}

// Find the first occurrence of a substring in a string
const char* str_find(const char* str, const char* substr, int start) {
    if (start < 0) return NULL;  // Invalid start index
    int i = 0;
    while (*str && i < start) {
        str_getUTF8CodePoint(&str);  // Advance the string pointer by the code point length
        i++;
    }
    return str_findHelper(str, substr);  // Start searching from the adjusted position
}

const char* str_findHelper(const char* str, const char* substr) {
    while (*str) {
        const char* tempStr = str;
        const char* tempSubstr = substr;
        int matched = 1;
        while (*tempSubstr && *tempStr) {
            int codePoint1 = str_getUTF8CodePoint(&tempStr);  // Get the next code point from str
            int codePoint2 = str_getUTF8CodePoint(&tempSubstr);  // Get the next code point from substr
            if (codePoint1 != codePoint2) {
                matched = 0;
                break;
            }
        }
        if (matched && *tempSubstr == '\0') {
            return str;  // Substring found
        }
        str_getUTF8CodePoint(&str);  // Move the pointer to the next code point
    }
    return NULL;  // Substring not found
}

// Copy characters from src to dest until a delimiter is found
void str_copyUntil(const char* src, const char* delimiter, char* dest) {
    const char* pos = str_find(src, delimiter, 0);  // Find the delimiter in the source string
    while (*src && src != pos) {
        const char* srcStart = src;
        str_getUTF8CodePoint(&src);  // Extract the code point and advance src
        int len = src - srcStart;    // Get the byte length of the code point
        strncpy(dest, srcStart, len);  // Copy the code point to the destination
        dest += len;  // Advance the destination pointer
    }
    *dest = '\0'; 
}

// Checks if a code point is a Unicode whitespace character
int str_isUnicodeWhitespace(int codePoint) {
    int size = sizeof(unicodeWhitespace) / sizeof(unicodeWhitespace[0]);
    for (int i = 0; i < size; i++) {
        if (unicodeWhitespace[i] == codePoint) {
            return 1; // Found in the list
        }
    }
    return 0;
}

// Checks if a character is a whitespace character
int str_isWhitespace(const char* str) {
    int codePoint = str_getUTF8CodePoint(&str);
    // Check if the code point matches ASCII whitespace or Unicode whitespace
    return (codePoint == 0x20 || // Space
            codePoint == 0x09 || // Tab
            codePoint == 0x0A || // Line Feed
            codePoint == 0x0D || // Carriage Return
            str_isUnicodeWhitespace(codePoint)); // Check Unicode whitespace
}

// Checks if a character is a whitespace character
bool str_isValidUTF8(const char* str) {
    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == -1 || (seqLen == 4 && str_getCodePointFromBytes(str, seqLen) > 0x10FFFF)) {
            return false;  // Invalid UTF-8 or code points above 0x10FFFF
        }
    }
    return true;
}

// Returns the length of the UTF-8 sequence starting with the given byte
int str_getUTF8SequenceLength(unsigned char byte) {
    if (byte <= 0x7F) return 1; // ASCII
    else if ((byte & 0xE0) == 0xC0) return 2; // 2-byte UTF-8
    else if ((byte & 0xF0) == 0xE0) return 3; // 3-byte UTF-8
    else if ((byte & 0xF8) == 0xF0) return 4; // 4-byte UTF-8
    return -1; // Invalid UTF-8 byte
}

// Returns the code point from a sequence of UTF-8 bytes
int str_getCodePointFromBytes(const char* str, int seqLen) {
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

// Returns the Unicode code point from the start of the string and advances the pointer
int str_getUTF8CodePoint(const char** str) {
    unsigned char byte = (unsigned char)**str;
    int seqLen = str_getUTF8SequenceLength(byte);
    if (seqLen == -1) {
        return -1; // Invalid UTF-8 byte
    }
    int codePoint = str_getCodePointFromBytes(*str, seqLen);
    *str += seqLen; // Advance the pointer to the next character
    return codePoint;
}

// ==== MAIN FUNCTIONS ====
// Returns the length of the string
int str_length(const char* str) {
    int length = 0;
    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == -1) return -1; // Invalid UTF-8 byte
        length++;
    }
    return length;
}

// Returns the character at a given index in the string
char* str_charAt(const char* str, int index) {
    int i = 0;
    const char* start;
    while (*str) {
        start = str;  // Store the start of the current code point
        int codePoint = str_getUTF8CodePoint(&str);  // Extract the code point and advance
        if (i == index) {
            int len = str - start;  // Calculate the byte length of the code point
            char* result = malloc(len + 1);
            if (!result) return NULL; // Check for allocation failure
            strncpy(result, start, len);  // Copy the code point
            result[len] = '\0';  // Null-terminate
            return result;
        }
        i++;
    }
    return NULL;  // Index out of bounds
}

// Returns the ASCII value of the character at a given index in the string
int str_charCodeAt(const char* str, int index) {
    int i = 0;
    while (*str) {
        int codePoint = str_getUTF8CodePoint(&str);  // Extract the code point once
        if (i == index) {
            return codePoint;  // Return the code point at the desired index
        }
        i++;
    }
    return -1; // Index out of bounds
}

// Returns the index of the first occurrence of a substring in a string
int str_indexOf(const char* str, const char* substr) {
    const char* pos = str_find(str, substr, 0);
    if (pos) {
        return (pos - str) / str_getUTF8CodePoint(&str);
    }
    return -1;
}

// Returns the index of the last occurrence of a substring in a string
int str_lastIndexOf(const char* str, const char* substr) {
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

// Join two strings together
void str_concat(const char* str1, const char* str2, char* result) {
    int len1 = str_length(str1);
    int len2 = str_length(str2);
    strncpy(result, str1, len1);
    strncpy(result + len1, str2, len2);
    result[len1 + len2] = '\0';  // Null-terminate the result
}

// Convert the entire string to lowercase (UTF-8 compatible on a very basic level for now)
void str_toLowerCase(char* str) {
    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == 1) { // ASCII
            if (*str >= 'A' && *str <= 'Z') {
                *str += 32; // Convert ASCII uppercase to lowercase (32 is the difference between ASCII uppercase and lowercase)
            }
        } else {
            // Handle common non-ASCII Latin characters
            int codePoint = str_getUTF8CodePoint(&str);
            if (codePoint >= 0x00C0 && codePoint <= 0x00D6) { // 'À' to 'Ö'
                codePoint -= 32;
            } else if (codePoint >= 0x00D8 && codePoint <= 0x00DE) { // 'Ø' to 'Þ'
                codePoint -= 32;
            }
            char* lowerChar = str_fromCodePoint(codePoint);
            memcpy(str, lowerChar, seqLen); // Copy the new lowercase character over
            free(lowerChar);
        }
    }
}

// Convert the entire string to uppercase (UTF-8 compatible)
void str_toUpperCase(char* str) {
    while (*str) {
        int seqLen = str_getUTF8CodePoint(&str);
        if (seqLen == 1) { // ASCII
            if (*str >= 'a' && *str <= 'z') {
                *str -= 32; // Convert ASCII lowercase to uppercase (32 is the difference between ASCII uppercase and lowercase)
            }
        } else {
            // Handle common non-ASCII Latin characters
            int codePoint = str_getUTF8CodePoint(&str);
            if (codePoint >= 0x00C0 && codePoint <= 0x00D6) { // 'À' to 'Ö'
                codePoint -= 32;
            } else if (codePoint >= 0x00D8 && codePoint <= 0x00DE) { // 'Ø' to 'Þ'
                codePoint -= 32;
            }
            char* upperChar = str_fromCodePoint(codePoint);
            memcpy(str, upperChar, seqLen); // Copy the new uppercase character over
            free(upperChar);
        }
    }
}

// Remove leading whitespace characters from a string
void str_trimStart(char* str) {
    const char* start = str;
    while (*start && str_isWhitespace(start)) {
        str_getUTF8CodePoint(&start);  // Skip over the leading whitespace
    }
    strcpy(str, start);  // Copy the remaining part of the string back to the start
}

// Remove trailing whitespace characters from a string
void str_trimEnd(char* str) {
    char* end = str + str_length(str);
    while (end > str) {
        const char* temp = end;
        int codePoint = str_getUTF8CodePoint(&temp);  // Get the last code point
        if (!str_isWhitespace(temp)) {
            break;  // Stop when a non-whitespace character is found
        }
        end--;  // Move the pointer back for trimming
    }
    *(end + 1) = '\0';  // Null-terminate the string after the last non-whitespace
}

// Trim whitespace characters from both the start and end of the string
void str_trim(char* str) {
    str_trimStart(str);
    str_trimEnd(str);
}

// Repeat a string a given number of times
void str_repeat(const char* str, int count, char* result) {
    if (count < 0) return;
    int strLen = str_length(str);
    for (int i = 0; i < count; i++) {
        strncpy(result, str, strLen);
        result += strLen;  // Advance result pointer
    }
    *result = '\0';  // Null-terminate
}

// Check if a string starts with a given prefix
int str_startsWith(const char* str, const char* prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) return 0;
    }
    return 1;
}

// Check if a string ends with a given suffix
int str_endsWith(const char* str, const char* suffix) {
    int strLen = str_length(str), suffixLen = str_length(suffix);
    if (suffixLen > strLen) return 0;
    str += strLen - suffixLen;
    while (*suffix) {
        if (*str++ != *suffix++) return 0;
    }
    return 1;
}

// Extract a substring from a string
void str_slice(const char* str, int start, int end, char* result) {
    int i = 0;
    while (*str && i < start) {
        str_getUTF8CodePoint(&str);
        i++;
    }
    while (*str && i < end) {
        int seqLen = str_getUTF8CodePoint(&str);
        for (int j = 0; j < seqLen; j++) {
            *result++ = *str++;
        }
        i++;
    }
    *result = '\0';
}

// Extract a substring from a string
void str_substring(const char* str, int start, int end, char* result) {
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
}

// Returns the Unicode code point at the given index
int str_codePointAt(const char* str, int index, int* codePoint) {
    int i = 0;
    while (*str) {
        if (i == index) {
            *codePoint = str_getUTF8CodePoint(&str);  // Extract the code point at the index
            return *codePoint;
        }
        str_getUTF8CodePoint(&str);  // Advance to the next code point
        i++;
    }
    return -1;  // Index out of bounds
}

// Returns a UTF-8 string for a given Unicode code point
char* str_fromCodePoint(int codePoint) {
    char* result;
    if (codePoint <= 0x7F) {
        result = (char*)malloc(2); // 1 byte + null terminator
        result[0] = (char)codePoint;
        result[1] = '\0';
    } else if (codePoint <= 0x7FF) {
        result = (char*)malloc(3); // 2 bytes + null terminator
        result[0] = (char)((codePoint >> 6) | 0xC0);
        result[1] = (char)((codePoint & 0x3F) | 0x80);
        result[2] = '\0';
    } else if (codePoint <= 0xFFFF) {
        result = (char*)malloc(4); // 3 bytes + null terminator
        result[0] = (char)((codePoint >> 12) | 0xE0);
        result[1] = (char)(((codePoint >> 6) & 0x3F) | 0x80);
        result[2] = (char)((codePoint & 0x3F) | 0x80);
        result[3] = '\0';
    } else if (codePoint <= 0x10FFFF) {
        result = (char*)malloc(5); // 4 bytes + null terminator
        result[0] = (char)((codePoint >> 18) | 0xF0);
        result[1] = (char)(((codePoint >> 12) & 0x3F) | 0x80);
        result[2] = (char)(((codePoint >> 6) & 0x3F) | 0x80);
        result[3] = (char)((codePoint & 0x3F) | 0x80);
        result[4] = '\0';
    } else {
        return NULL; // Invalid code point
    }
    return result;
}

// Check if a string includes a given substring
int str_includes(const char* str, const char* substr) {
    return str_indexOf(str, substr) != -1;
}

// Pad a string with a given character at the start to reach a target length
void str_padStart(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize) {
    int strLen = str_length(str), padLen = str_length(padStr);
    if (targetLength <= strLen) {
        str_concat(str, "", result);
        return;
    }
    int padCount = targetLength - strLen;
    if (targetLength >= resultSize) {
        fprintf(stderr, "Error: Buffer size is too small.\n");
        return;
    }
    char temp[resultSize];
    temp[0] = '\0';
    while (padCount > padLen) {
        str_concat(temp, padStr, temp);
        padCount -= padLen;
    }
    while (padCount-- > 0) strncat(temp, padStr, 1);
    str_concat(temp, str, result);
}

// Pad a string with a given character at the end to reach a target length
void str_padEnd(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize) {
    int strLen = str_length(str), padLen = str_length(padStr);
    if (targetLength >= resultSize) {
        fprintf(stderr, "Error: Buffer size is too small.\n");
        return;
    }
    str_concat(str, "", result);
    int padCount = targetLength - strLen;
    while (padCount > padLen) {
        str_concat(result, padStr, result);
        padCount -= padLen;
    }
    while (padCount-- > 0) strncat(result, padStr, 1);
    result[targetLength] = '\0';
}

// Replace all occurrences of a substring with another substring in a string
void str_replace(const char* str, const char* searchValue, const char* newValue, char* result) {
    const char* pos = str;
    int searchLen = str_length(searchValue);
    int newValueLen = str_length(newValue);

    while ((pos = str_findHelper(pos, searchValue)) != NULL) {
        // Copy up to the match
        str_copyUntil(str, searchValue, result);
        result += (pos - str);  // Advance result pointer after the copied part
        str = pos + searchLen;  // Move str pointer after the matched searchValue

        // Copy the replacement value
        strcpy(result, newValue);  // Safely copy the new value
        result += newValueLen;  // Advance result pointer after copying

        pos = str;  // Continue searching after the replacement
    }

    // Copy the remaining part of the original string
    strcpy(result, str);
}