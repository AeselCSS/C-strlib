#ifndef STRLIB_H
#define STRLIB_H

// Beregner længden af strengen
int str_length(const char* str);

// Returnerer tegnet ved en given index i strengen
char str_charAt(const char* str, int index);

// Returnerer indexet for første forekomst af et substring i en streng
int str_indexOf(const char* str, const char* substr);

// Kæder to strenge sammen
void str_concat(const char* str1, const char* str2, char* result);

// Konverterer hele strengen til små bogstaver
void str_toLowerCase(char* str);

#endif // STRLIB_H
