#include <stdio.h>
#include "strlib.h"

int main() {
    char str1[] = "Hello, World!";
    char str2[] = "World";
    char result[50];

    printf("Length of '%s': %d\n", str1, str_length(str1));
    printf("Character at index 7: %c\n", str_charAt(str1, 7));
    printf("Index of 'World': %d\n", str_indexOf(str1, str2));

    str_concat(str1, str2, result);
    printf("Concatenation: %s\n", result);

    str_toLowerCase(str1);
    printf("Lowercase: %s\n", str1);

    return 0;
}
