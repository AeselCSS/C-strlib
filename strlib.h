#ifndef STRLIB_H
#define STRLIB_H

// Copies characters from src to dest from start to end
void str_copyRange(const char* src, int start, int end, char* dest);

// Returns pointer to the first occurrence of substr in str after start position
const char* str_find(const char* str, const char* substr, int start);

// Copies characters from src to dest until a specified string (delimiter) is found
void str_copyUntil(const char* src, const char* delimiter, char* dest);

// Checks if a character is a whitespace character
int str_isWhitespace(char c);

// Returns the length of a string
int str_length(const char* str);

// Returns the character at a specific index in a string
char str_charAt(const char* str, int index);

// Returns the ASCII value of the character at a specific index in a string
int str_charCodeAt(const char* str, int index);

// Returns the index of the first occurrence of a substring in a string
int str_indexOf(const char* str, const char* substr);

// Returns the index of the last occurrence of a substring in a string
int str_lastIndexOf(const char* str, const char* substr);

// Joins two strings together
void str_concat(const char* str1, const char* str2, char* result);

// Converts the entire string to lowercase
void str_toLowerCase(char* str);

// Converts the entire string to uppercase
void str_toUpperCase(char* str);

// Removes leading whitespace from a string
void str_trimStart(const char* str);

// Removes trailing whitespace from a string
void str_trimEnd(const char* str);

// Removes leading and trailing whitespace from a string
void str_trim(const char* str);

// Repeats a string a given number of times
void str_repeat(const char* str, int count, char* result);

// Checks if a string starts with a given prefix
int str_startsWith(const char* str, const char* prefix);

// Checks if a string ends with a given suffix
int str_endsWith(const char* str, const char* suffix);

// Replaces all occurrences of a substring with another substring in a string
void str_slice(const char* str, int start, int end, char* result);

// Extracts a substring from a string
void str_substring(const char* str, int start, int end, char* result);

// Checks if a string includes a given substring
int str_includes(const char* str, const char* substr);

// Pad a string with a given character at the start to reach a target length
void str_padStart(const char* str, int targetLength, const char* padStr, char* result);

// Pad a string with a given character at the end to reach a target length
void str_padEnd(const char* str, int targetLength, const char* padStr, char* result);

// Replace all occurrences of a substring with another substring in a string
void str_replace(const char* str, const char* searchValue, const char* newValue, char* result);

#endif // STRLIB_H
