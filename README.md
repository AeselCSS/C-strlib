## Method overview

| Method                | Status              | Comment                                       | Implemented  |
|-----------------------|---------------------|-----------------------------------------------|--------------|
| `charAt()`            | Implementable       | Returns the character at a specific index     | ✅           |
| `charCodeAt()`        | Implementable       | Returns the ASCII code of the character       |              |
| `concat()`            | Implementable       | Concatenates two strings                      | ✅           |
| `endsWith()`          | Implementable       | Checks if the string ends with a substring    |              |
| `includes()`          | Implementable       | Checks if the string contains a substring     |              |
| `indexOf()`           | Implementable       | Finds the first occurrence of a substring     | ✅           |
| `lastIndexOf()`       | Implementable       | Finds the last occurrence of a substring      |              |
| `length`              | Implementable       | Returns the length of the string (as function)| ✅           |
| `startsWith()`        | Implementable       | Checks if the string starts with a substring  |              |
| `slice()`             | Implementable       | Returns a portion of the string               |              |
| `toLowerCase()`       | Implementable       | Converts to lowercase                         | ✅           |
| `toUpperCase()`       | Implementable       | Converts to uppercase                         |              |
| `trim()`              | Implementable       | Removes whitespace from both ends             |              |
| `trimStart()`         | Implementable       | Removes whitespace from the start             |              |
| `trimEnd()`           | Implementable       | Removes whitespace from the end               |              |
| `repeat()`            | Implementable       | Repeats the string `count` times              |              |
| `substring()`         | Modification Needed | Similar to `slice` but does not support negative indices |              |
| `padStart()`          | Modification Needed | Pads the string to the target length from the start |              |
| `padEnd()`            | Modification Needed | Pads the string to the target length from the end |              |
| `replace()`           | Modification Needed | No regex, only static replacement             |              |
| `split()`             | Modification Needed | Splits the string based on a separator, no regex |              |
| `localeCompare()`     | Modification Needed | No locale support, similar to `strcmp`        |              |
| `match()`             | Not Implementable   | Requires regex support                        |              |
| `matchAll()`          | Not Implementable   | Requires regex support                        |              |
| `replaceAll()`        | Not Implementable   | Requires regex or advanced manipulation       |              |
| `search()`            | Not Implementable   | Requires regex                                |              |
| `codePointAt()`       | Not Implementable   | Requires Unicode support                      |              |
| `normalize()`         | Not Implementable   | Requires Unicode normalization                |              |
| `isWellFormed()`      | Not Implementable   | Requires Unicode support                      |              |
| `toWellFormed()`      | Not Implementable   | Requires Unicode support                      |              |
| `toLocaleLowerCase()` | Not Implementable   | Requires locale support                       |              |
| `toLocaleUpperCase()` | Not Implementable   | Requires locale support                       |              |
| `valueOf()`           | Not Implementable   | Unnecessary in C                              |              |
