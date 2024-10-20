#include <stdio.h>
#include "strlib.h"
#include <stdlib.h>


void test_ascii_cases() {
    // Test 1: ASCII-only string
    char str1[50] = "Hello, World!";
    char str2[] = "World";
    char result[100]; // Larger buffer for concatenated results

    printf("=== ASCII Tests ===\n");

    // Test str_length with ASCII
    printf("Length of '%s': %d\n", str1, str_length(str1)); // Should print 13

    // Test str_charAt with ASCII
    char* charAt = str_charAt(str1, 7);
    if (charAt) {
        printf("Character at index 7: %s\n", charAt); // Should print 'W'
        free(charAt);
    }

    // Test str_charCodeAt with ASCII
    printf("ASCII value at index 7: %d\n", str_charCodeAt(str1, 7)); // Should print 87 ('W')

    // Test str_indexOf with ASCII
    printf("Index of 'World': %d\n", str_indexOf(str1, str2)); // Should print 7

    // Test str_lastIndexOf with ASCII
    char str3[] = "Hello, Hello, World!";
    printf("Last index of 'Hello' in '%s': %d\n", str3, str_lastIndexOf(str3, "Hello")); // Should print 7

    // Test str_concat with ASCII
    str_concat(str1, str2, result);
    printf("Concatenation: %s\n", result); // Should print "Hello, World!World"

    // Reset str1 for further tests
    str_concat("Hello, World!", "", str1);

    // Test str_toLowerCase with ASCII
    str_toLowerCase(str1);
    printf("Lowercase: %s\n", str1); // Should print "hello, world!"

    // Test str_toUpperCase with ASCII
    str_toUpperCase(str1);
    printf("Uppercase: %s\n", str1); // Should print "HELLO, WORLD!"

    // Test str_trimStart with ASCII
    char str4[] = "   Trim me!";
    str_trimStart(str4);
    printf("Trim start: '%s'\n", str4); // Should print "Trim me!"

    // Test str_trimEnd with ASCII
    char str5[] = "Trim me!   ";
    str_trimEnd(str5);
    printf("Trim end: '%s'\n", str5); // Should print "Trim me!"

    // Test str_trim with ASCII
    char str6[] = "   Trim me!   ";
    str_trim(str6);
    printf("Trim both: '%s'\n", str6); // Should print "Trim me!"

    // Test str_repeat with ASCII
    str_repeat("Repeat", 3, result);
    printf("Repeat 3 times: %s\n", result); // Should print "RepeatRepeatRepeat"

    // Test str_startsWith with ASCII
    printf("Starts with 'Hello': %d\n", str_startsWith("Hello, World!", "Hello")); // Should print 1 (true)

    // Test str_endsWith with ASCII
    printf("Ends with 'World!': %d\n", str_endsWith("Hello, World!", "World!")); // Should print 1 (true)

    // Test str_slice with ASCII
    str_slice("Hello, World!", 7, 12, result);
    printf("Slice from index 7 to 12: %s\n", result); // Should print "World"

    // Test str_substring with ASCII
    str_substring("Hello, World!", 7, 12, result);
    printf("Substring from index 7 to 12: %s\n", result); // Should print "World"

    // Test str_includes with ASCII
    printf("Includes 'World': %d\n", str_includes("Hello, World!", "World")); // Should print 1 (true)

    // Test str_padStart with ASCII
    str_padStart("Pad", 10, " ", result, sizeof(result));  // Pass a string " " and the result buffer size
    printf("Pad start to length 10: '%s'\n", result); // Should print "       Pad"

    // Test str_padEnd with ASCII
    str_padEnd("Pad", 10, " ", result, sizeof(result));  // Pass a string " " and the result buffer size
    printf("Pad end to length 10: '%s'\n", result); // Should print "Pad       "

    // Test str_replace with ASCII
    str_replace("Hello, World!", "World", "Universe", result);
    printf("Replace 'World' with 'Universe': %s\n", result); // Should print "Hello, Universe!"
}

void test_utf8_cases() {
    // Test 2: UTF-8 string (without emojis)
    printf("\n=== UTF-8 Tests ===\n");

    char result[100];  // Add this missing declaration

    // Test str_length with UTF-8
    char utf8Str[] = "Héllö, 世界!";
    printf("Length of '%s' (UTF-8): %d\n", utf8Str, str_length(utf8Str)); // Should print 10

    // Test str_charAt with UTF-8
    char* charAt = str_charAt(utf8Str, 7);  // Add missing charAt declaration
    if (charAt) {
        printf("Character at index 7 (UTF-8): %s\n", charAt); // Should print '世'
        free(charAt);
    }

    // Test str_charCodeAt with UTF-8
    printf("Code point at index 7 (UTF-8): %d\n", str_charCodeAt(utf8Str, 7)); // Should print 19990 ('世')

    // Test str_indexOf with UTF-8
    printf("Index of '世界': %d\n", str_indexOf(utf8Str, "世界")); // Should print 7

    // Test str_concat with UTF-8
    str_concat(utf8Str, "World", result);
    printf("UTF-8 Concatenation: %s\n", result); // Should print "Héllö, 世界!World"

    // Test str_toLowerCase with UTF-8
    char utf8Upper[] = "HÉLLÖ, 世界!";
    str_toLowerCase(utf8Upper);
    printf("UTF-8 Lowercase: %s\n", utf8Upper); // Should print "héllö, 世界!"

    // Test str_toUpperCase with UTF-8
    str_toUpperCase(utf8Str);
    printf("UTF-8 Uppercase: %s\n", utf8Str); // Should print "HÉLLÖ, 世界!"

    // Test str_slice with UTF-8
    str_slice(utf8Str, 7, 9, result);
    printf("UTF-8 Slice from index 7 to 9: %s\n", result); // Should print "世界"

    // Test str_replace with UTF-8
    str_replace(utf8Str, "世界", "Universe", result);
    printf("Replace '世界' with 'Universe': %s\n", result); // Should print "Héllö, Universe!"

    // UTF-8 whitespace tests
    char utf8SpaceStr[] = " \u3000\u2002Héllö, 世界! \u2005\u3000 ";  // Contains regular spaces, em spaces, en spaces
    printf("Original with UTF-8 spaces: '%s'\n", utf8SpaceStr);

    // Test str_trimStart with UTF-8
    str_trimStart(utf8SpaceStr);
    printf("Trim UTF-8 start: '%s'\n", utf8SpaceStr); // Should print "Héllö, 世界! \u2005\u3000 "

    // Reset string for trim end test
    char utf8SpaceStrEnd[] = " \u3000\u2002Héllö, 世界! \u2005\u3000 ";  // Reset to original with spaces
    str_trimEnd(utf8SpaceStrEnd);
    printf("Trim UTF-8 end: '%s'\n", utf8SpaceStrEnd); // Should print " \u3000\u2002Héllö, 世界!"

    // Reset string for trim both sides
    char utf8SpaceStrBoth[] = " \u3000\u2002Héllö, 世界! \u2005\u3000 ";  // Reset to original with spaces
    str_trim(utf8SpaceStrBoth);
    printf("Trim UTF-8 both: '%s'\n", utf8SpaceStrBoth); // Should print "Héllö, 世界!"

    // Test regular trimming on ASCII spaces
    char asciiSpaceStr[] = "    Trim me!    ";
    str_trim(asciiSpaceStr);
    printf("Trim both (ASCII): '%s'\n", asciiSpaceStr); // Should print "Trim me!"
}

void test_utf8_with_emojis_cases() {
    // Test 3: UTF-8 + Emojis
    printf("\n=== UTF-8 + Emoji Tests ===\n");

    char utf8EmojiStr[] = "Hello, 🌍🚀!";  // "🌍" and "🚀" are emojis
    char result[100];  // Add missing declaration

    // Test str_length with UTF-8 + Emojis
    printf("Length of '%s' (UTF-8 + Emojis): %d\n", utf8EmojiStr, str_length(utf8EmojiStr)); // Should print 10 (counts Unicode code points)

    // Test str_charAt with UTF-8 + Emojis
    char* charAtEmoji = str_charAt(utf8EmojiStr, 7); // Position of the Earth emoji 🌍
    if (charAtEmoji) {
        printf("Character at index 7 (UTF-8 + Emojis): %s\n", charAtEmoji); // Should print "🌍"
        free(charAtEmoji);
    }

    // Test str_charCodeAt with UTF-8 + Emojis
    printf("Code point at index 7 (UTF-8 + Emojis): %d\n", str_charCodeAt(utf8EmojiStr, 7)); // Should print the code point for 🌍 (127757)

    // Test str_indexOf with UTF-8 + Emojis
    printf("Index of '🚀': %d\n", str_indexOf(utf8EmojiStr, "🚀")); // Should print 8 (index of the rocket emoji)

    // Test str_replace with UTF-8 + Emojis
    str_replace(utf8EmojiStr, "🚀", "🛸", result);  // Replacing the rocket emoji 🚀 with the UFO emoji 🛸
    printf("Replace '🚀' with '🛸': %s\n", result); // Should print "Hello, 🌍🛸!"

    // Test str_concat with UTF-8 + Emojis
    char utf8EmojiStr2[] = " Goodbye, 🌙!";
    str_concat(utf8EmojiStr, utf8EmojiStr2, result);
    printf("UTF-8 + Emoji Concatenation: %s\n", result); // Should print "Hello, 🌍🚀! Goodbye, 🌙!"

    // Test str_toLowerCase with UTF-8 + Emojis (emojis shouldn't be affected)
    str_toLowerCase(utf8EmojiStr);
    printf("Lowercase (UTF-8 + Emojis): %s\n", utf8EmojiStr); // Should print "hello, 🌍🚀!"

    // Test str_toUpperCase with UTF-8 + Emojis (emojis shouldn't be affected)
    str_toUpperCase(utf8EmojiStr);
    printf("Uppercase (UTF-8 + Emojis): %s\n", utf8EmojiStr); // Should print "HELLO, 🌍🚀!"
}

int main() {
    test_ascii_cases();
    test_utf8_cases();
    test_utf8_with_emojis_cases();

    return 0;
}
