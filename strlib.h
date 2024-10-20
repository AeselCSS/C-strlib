#ifndef STRLIB_H
#define STRLIB_H

#include <stdbool.h>

extern const int unicodeWhitespace[];

// Error codes for the string library
typedef enum {
    STR_SUCCESS = 0,
    STR_ERROR_NULL_INPUT,
    STR_ERROR_INVALID_INDEX,
    STR_ERROR_MEMORY_ALLOCATION,
    STR_ERROR_INVALID_UTF8
} StrError;

extern StrError str_last_error;  // Holds the last error state

// ==== HELPER FUNCTIONS ====
// Copies characters from src to dest from start to end
StrError str_copyRange(const char* src, int start, int end, char* dest);

// Returns pointer to the first occurrence of substr in str after start position
const char* str_find(const char* str, const char* substr, int start);

const char* str_findHelper(const char* str, const char* substr);

// Copies characters from src to dest until a specified string (delimiter) is found
StrError str_copyUntil(const char* src, const char* delimiter, char* dest);

// Checks if a code point is a Unicode whitespace character
int str_isUnicodeWhitespace(int codePoint);

// Checks if a character is a whitespace character
int str_isWhitespace(const char* str);

// Validates if a string is valid UTF-8
bool str_isValidUTF8(const char* str);

// Returns the length of the UTF-8 sequence starting with the given byte
int str_getUTF8SequenceLength(unsigned char byte);

// Returns the code point from a sequence of UTF-8 bytes
int str_getCodePointFromBytes(const char* str, int seqLen);

// Returns the Unicode code point from the start of the string and advances the pointer
int str_getUTF8CodePoint(const char** str);

// ==== MAIN FUNCTIONS ====
// Returns the length of a string (in Unicode code points)
int str_length(const char* str);

// Returns the character at a specific index in a string
char* str_charAt(const char* str, int index);

// Returns the ASCII/Unicode value of the character at a specific index in a string
int str_charCodeAt(const char* str, int index);

// Returns the index of the first occurrence of a substring in a string
int str_indexOf(const char* str, const char* substr);

// Returns the index of the last occurrence of a substring in a string
int str_lastIndexOf(const char* str, const char* substr);

// Joins two strings together and stores the result in the result buffer
StrError str_concat(const char* str1, const char* str2, char* result);

// Converts the entire string to lowercase
StrError str_toLowerCase(char* str);

// Converts the entire string to uppercase
StrError str_toUpperCase(char* str);

// Removes leading whitespace from a string
StrError str_trimStart(char* str);

// Removes trailing whitespace from a string
StrError str_trimEnd(char* str);

// Removes leading and trailing whitespace from a string
StrError str_trim(char* str);

// Repeats a string a given number of times and stores the result in the result buffer
StrError str_repeat(const char* str, int count, char* result);

// Checks if a string starts with a given prefix
int str_startsWith(const char* str, const char* prefix);

// Checks if a string ends with a given suffix
int str_endsWith(const char* str, const char* suffix);

// Extracts a substring from a string and stores it in the result buffer
void str_slice(const char* str, int start, int end, char* result);

// Extracts a substring from a string and stores it in the result buffer
StrError str_substring(const char* str, int start, int end, char* result);

// Returns the Unicode code point at a specific index in a string
int str_codePointAt(const char* str, int index, int* codePoint);

// Converts a Unicode code point to a string
char* str_fromCodePoint(int codePoint);

// Checks if a string includes a given substring
int str_includes(const char* str, const char* substr);

// Pads a string with a given character at the start to reach a target length
StrError str_padStart(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize);

// Pads a string with a given character at the end to reach a target length
StrError str_padEnd(const char* str, int targetLength, const char* padStr, char* result, size_t resultSize);

// Replaces all occurrences of a substring with another substring in a string
StrError str_replace(const char* str, const char* searchValue, const char* newValue, char* result);

#endif // STRLIB_H
