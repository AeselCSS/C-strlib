#include "strlib.h"

// Beregner længden af strengen
int str_length(const char* str) {
    int length = 0;
    while (*str++) {
        length++;
    }
    return length;
}

// Returnerer tegnet ved en given index i strengen
char str_charAt(const char* str, int index) {
    if (index < 0 || index >= str_length(str)) {
        return '\0'; // Returner null character ved ugyldigt index
    }
    return *(str + index);
}

// Returnerer indexet for første forekomst af et substring i en streng
int str_indexOf(const char* str, const char* substr) {
    const char *p1, *p2;
    int index = 0;
    while (*str) {
        p1 = str;
        p2 = substr;
        while (*p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) {
            return index; // Fundet substring
        }
        str++;
        index++;
    }
    return -1; // Ikke fundet
}

// Kæder to strenge sammen og gemmer resultatet i result
void str_concat(const char* str1, const char* str2, char* result) {
    while (*str1) {
        *result++ = *str1++;
    }
    while (*str2) {
        *result++ = *str2++;
    }
    *result = '\0';
}

// Konverterer hele strengen til små bogstaver
void str_toLowerCase(char* str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str += 32;
        }
        str++;
    }
}
