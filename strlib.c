#include <stddef.h> // For NULL definition

// ==== HELPER FUNCTIONS ====
// Copies characters from src to dest from start to end
// How it works: Move the src pointer to the start position, then copy characters until the end position
void str_copyRange(const char* src, int start, int end, char* dest) {
    src += start; // Move to the start position
    while (start++ < end && *src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Finds the first occurrence of substr in str after the specified start index
// How it works: Iterate through the string and compare substr with each substring
const char* str_find(const char* str, const char* substr, int start) {
    int i = start;
    int j;
    while (str[i] != '\0') {
        j = 0;
            while (str[i + j] != '\0' && substr[j] != '\0' && str[i + j] == substr[j]) { // ensures we dont go past the end of either str nor substr and ensures the current char is a match in both strings.  
            j++;
        }
        if (substr[j] == '\0') { // Found the whole substring
            return &str[i]; // return a pointer to the starting position of the substring in the main string str.
        }
        i++;
    }
    return NULL; // Substring not found.
}

// Copies characters from src to dest until a specified string (delimiter) is found
// How it works: Copy characters from src to dest until the delimiter is found
void str_copyUntil(const char* src, const char* delimiter, char* dest) {
    const char* pos = str_find(src, delimiter, 0);
    while (*src && src != pos) { // Stop at delimiter
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Checks if a character is a whitespace character
int str_isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

// ==== MAIN FUNCTIONS ====
// Returns the length of the string
// How it works: Iterate through the string until the null terminator is found
int str_length(const char* str) {
    int length = 0;
    while (*str++) {
        length++;
    }
    return length;
}

// Returns the character at a given index in the string
// How it works: Check if the index is within bounds, then return the character at that index
char str_charAt(const char* str, int index) {
    return (index < 0 || index >= str_length(str)) ? '\0' : str[index];
}

// Returns the ASCII value of the character at a given index in the string
// How it works: Check if the index is within bounds, then return the ASCII value of the character at that index
int str_charCodeAt(const char* str, int index) {
    return (index < 0 || index >= str_length(str)) ? -1 : (int)str[index];
}

// Returns the index of the first occurrence of a substring in a string
// How it works: Use str_find to find the substring in the string
int str_indexOf(const char* str, const char* substr) {
    const char* pos = str_find(str, substr, 0);
    return pos ? pos - str : -1;
}

// Returns the index of the last occurrence of a substring in a string
// How it works: Iterate through the string and find the last occurrence of the substring
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
// How it works: Copy the first string to the result, then copy the second string
void str_concat(const char* str1, const char* str2, char* result) {
    while (*str1) *result++ = *str1++;
    while (*str2) *result++ = *str2++;
    *result = '\0';
}

// Convert the entire string to lowercase
// How it works: Iterate through the string and convert each character to lowercase
void str_toLowerCase(char* str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') *str += 32;
        str++;
    }
}

// Convert the entire string to uppercase
// How it works: Iterate through the string and convert each character to uppercase
void str_toUpperCase(char* str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') *str -= 32;
        str++;
    }
}

// Remove leading whitespace characters from a string
// How it works: Iterate through the string and skip leading whitespace characters
void str_trimStart(char* str) {
    char *start = str;
    while (*start && str_isWhitespace(*start)) start++;
    while (*start) *str++ = *start++;
    *str = '\0';
}

// Remove trailing whitespace characters from a string
// How it works: Find the last non-whitespace character and set the next character to null
void str_trimEnd(char* str) {
    char *end = str + str_length(str) - 1;
    while (end >= str && str_isWhitespace(*end)) end--;
    *(end + 1) = '\0';
}

// Trim whitespace characters from both the start and end of the string
// How it works: Use str_trimStart and str_trimEnd to remove leading and trailing whitespace
void str_trim(char* str) {
    str_trimStart(str);
    str_trimEnd(str);
}

// Repeat a string a given number of times
// How it works: Copy the string multiple times to the result
void str_repeat(const char* str, int count, char* result) {
    if (count < 0) return;
    while (count--) {
        const char *temp = str;
        while (*temp) *result++ = *temp++;
    }
    *result = '\0';
}

// Check if a string starts with a given prefix
// How it works: Compare the prefix with the start of the string
int str_startsWith(const char* str, const char* prefix) {
    while (*prefix) {
        if (*str++ != *prefix++) return 0;
    }
    return 1;
}

// Check if a string ends with a given suffix
// How it works: Compare the suffix with the end of the string
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
// How it works: Copy characters from the start index to the end index
void str_slice(const char* str, int start, int end, char* result) {
    int len = str_length(str);
    if (start < 0) start = 0;
    if (end > len) end = len;
    if (start > end) {
        *result = '\0';
        return;
    }
    str_copyRange(str, start, end, result);
}

// Extract a substring from a string
// How it works: Swap the start and end indices if start is greater than end
void str_substring(const char* str, int start, int end, char* result) {
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    str_slice(str, start, end, result);
}

// Check if a string includes a given substring
// How it works: Check if the index of the substring is not -1
int str_includes(const char* str, const char* substr) {
    return str_indexOf(str, substr) != -1;
}

// Pad a string with a given character at the start to reach a target length
// How it works: Copy the padding string until the target length is reached
void str_padStart(const char* str, int targetLength, const char* padStr, char* result) {
    int strLen = str_length(str), padLen = str_length(padStr);
    if (targetLength <= strLen) {
        str_concat(str, "", result);
        return;
    }
    int padCount = targetLength - strLen;
    while (padCount > padLen) {
        str_concat(padStr, padStr, result);
        padCount -= padLen;
    }
    while (padCount-- > 0) *result++ = *padStr++;
    str_concat(result, str, result);
}

// Pad a string with a given character at the end to reach a target length
// How it works: Copy the string and then copy the padding string until the target length is reached
void str_padEnd(const char* str, int targetLength, const char* padStr, char* result) {
    int strLen = str_length(str), padLen = str_length(padStr);
    str_concat(str, "", result);
    int padCount = targetLength - strLen;
    while (padCount > padLen) {
        str_concat(padStr, padStr, result);
        padCount -= padLen;
    }
    while (padCount-- > 0) *result++ = *padStr++;
    *result = '\0';
}

// Replace all occurrences of a substring with another substring in a string
// How it works: Find the substring and replace it with the new substring
void str_replace(const char* str, const char* searchValue, const char* newValue, char* result) {
    const char* pos = str;
    int searchLen = str_length(searchValue), newValueLen = str_length(newValue);
    while ((pos = str_find(pos, searchValue, 0)) != NULL) { // Use NULL instead of '\0'
        str_copyUntil(str, searchValue, result);
        result += pos - str;
        str = pos + searchLen;
        for (int i = 0; i < newValueLen; i++) *result++ = newValue[i];
        pos = str;
    }
    while (*str) *result++ = *str++;
    *result = '\0';
}
