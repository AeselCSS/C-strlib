#include <stdio.h>
#include "strlib.h"

int main() {
    char str1[50] = "Hello, World!";
    char str2[] = "World";
    char result[100]; // Larger buffer for concatenated results

    // Test str_length
    printf("Length of '%s': %d\n", str1, str_length(str1)); // Should print 13

    // Test str_charAt
    printf("Character at index 7: %c\n", str_charAt(str1, 7)); // Should print 'W'

    // Test str_charCodeAt
    printf("ASCII value at index 7: %d\n", str_charCodeAt(str1, 7)); // Should print 87 ('W')

    // Test str_indexOf
    printf("Index of 'World': %d\n", str_indexOf(str1, str2)); // Should print 7

    // Test str_lastIndexOf
    char str3[] = "Hello, Hello, World!";
    printf("Last index of 'Hello' in '%s': %d\n", str3, str_lastIndexOf(str3, "Hello")); // Should print 7

    // Test str_concat
    str_concat(str1, str2, result);
    printf("Concatenation: %s\n", result); // Should print "Hello, World!World"

    // Reset str1 for further tests
    str_concat("Hello, World!", "", str1);

    // Test str_toLowerCase
    str_toLowerCase(str1);
    printf("Lowercase: %s\n", str1); // Should print "hello, world!"

    // Test str_toUpperCase
    str_toUpperCase(str1);
    printf("Uppercase: %s\n", str1); // Should print "HELLO, WORLD!"

    // Test str_trimStart
    char str4[] = "   Trim me!";
    str_trimStart(str4);
    printf("Trim start: '%s'\n", str4); // Should print "Trim me!"

    // Test str_trimEnd
    char str5[] = "Trim me!   ";
    str_trimEnd(str5);
    printf("Trim end: '%s'\n", str5); // Should print "Trim me!"

    // Test str_trim
    char str6[] = "   Trim me!   ";
    str_trim(str6);
    printf("Trim both: '%s'\n", str6); // Should print "Trim me!"

    // Test str_repeat
    str_repeat("Repeat", 3, result);
    printf("Repeat 3 times: %s\n", result); // Should print "RepeatRepeatRepeat"

    // Test str_startsWith
    printf("Starts with 'Hello': %d\n", str_startsWith("Hello, World!", "Hello")); // Should print 1 (true)

    // Test str_endsWith
    printf("Ends with 'World!': %d\n", str_endsWith("Hello, World!", "World!")); // Should print 1 (true)

    // Test str_slice
    str_slice("Hello, World!", 7, 12, result);
    printf("Slice from index 7 to 12: %s\n", result); // Should print "World"

    // Test str_substring
    str_substring("Hello, World!", 12, 7, result);
    printf("Substring from index 12 to 7: %s\n", result); // Should print "World" (handles reversed indices)

    // Test str_includes
    printf("Includes 'World': %d\n", str_includes("Hello, World!", "World")); // Should print 1 (true)

    // Test str_padStart
    str_padStart("Pad", 10, " ", result);
    printf("Pad start to length 10: '%s'\n", result); // Should print "       Pad"

    // Test str_padEnd
    str_padEnd("Pad", 10, " ", result);
    printf("Pad end to length 10: '%s'\n", result); // Should print "Pad       "

    // Test str_replace
    str_replace("Hello, World!", "World", "Universe", result);
    printf("Replace 'World' with 'Universe': %s\n", result); // Should print "Hello, Universe!"

    return 0;
}
