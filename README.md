This project has been created as part of the 42 curriculum by **mohfalla**

# libft

## Description

**libft** is the very first project of the 42 Common Core.  
Its goal is to recreate a selection of essential functions from the C standard library (and some useful additional ones) in order to build a personal, reusable library called `libft.a`.

By implementing these functions from scratch, students gain a deep understanding of:
- Low-level memory manipulation
- String handling
- Character classification and transformation
- Linked list management
- Pointers, memory allocation, and proper error handling

The library is divided into:
- Mandatory part: reimplementations of standard functions (`strlen`, `strchr`, `memcpy`, `atoi`, etc.) and some BSD extensions (`strlcpy`, `strlcat`, etc.)
- Bonus part: singly linked list manipulation functions (`ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`, `ft_lstadd_back`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`)

The final deliverable is a static library `libft.a` that can be linked to future projects, along with the corresponding header `libft.h`.

## Instructions

### Compilation

The library is compiled using the provided `Makefile`.

```bash
make          # compiles the mandatory part → libft.a
make bonus    # compiles the mandatory + bonus part → libft.a (with bonus functions)
make clean    # removes object files
make fclean   # removes object files + libft.a
make re       # fclean + make
```
### Usage

Include the header in your project:
```C
#include "libft.h"
```
Compile your program linking the library:
```bash
gcc main.c -L. -lft -o my_program
```
(The -L. tells the linker to look for libraries in the current directory, -lft links libft.a.)


# Detailed Description of the Library

## Mandatory Functions

| Category                  | Functions                                                                 |
|---------------------------|---------------------------------------------------------------------------|
| **Character tests**       | ft_isalpha, ft_isdigit, ft_isalnum, ft_isascii, ft_isprint                |
| **Character conversion**  | ft_toupper, ft_tolower                                                     |
| **String length**         | ft_strlen                                                                 |
| **Memory manipulation**   | ft_memset, ft_bzero, ft_memcpy, ft_memmove, ft_memchr, ft_memcmp           |
| **Safe string copy/cat**  | ft_strlcpy, ft_strlcat                                                    |
| **String search**         | ft_strchr, ft_strrchr, ft_strnstr, ft_strncmp                             |
| **Conversion**            | ft_atoi                                                                   |
| **Memory allocation**     | ft_calloc, ft_strdup                                                      |
| **String manipulation**   | ft_substr, ft_strjoin, ft_strtrim, ft_split                               |
| **Output functions**      | ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd                  |
| **Advanced string**       | ft_strmapi, ft_striteri                                                   |
| **Integer to string**     | ft_itoa                                                                   |

## Bonus Functions (Linked List)

| Function         | Description                                                  |
|------------------|--------------------------------------------------------------|
| ft_lstnew        | Creates a new list node                                      |
| ft_lstadd_front  | Adds a node at the beginning of the list                     |
| ft_lstsize       | Returns the number of nodes in the list                      |
| ft_lstlast       | Returns the last node of the list                            |
| ft_lstadd_back   | Adds a node at the end of the list                           |
| ft_lstdelone     | Frees a single node (content + node)                         |
| ft_lstclear      | Frees the entire list and sets the pointer to NULL           |
| ft_lstiter       | Applies a function to each node's content                    |
| ft_lstmap        | Creates a new list by applying a function to each content    |

## Resources

### References

- man pages (on Linux/macOS): primary reference for all standard functions (man strlen, man memcpy, etc.)
- C Standard Library documentation: <https://en.cppreference.com/w/c>
- A guide for having a more Understandable explanation of each function: <https://42-cursus.gitbook.io/guide/0-rank-00/libft>
- CS50: Introduction to Computer Science: <https://pll.harvard.edu/course/cs50-introduction-computer-science>
- "The C Programming Language" by Kernighan & Ritchie (for deeper understanding)

### Use of AI

Artificial Intelligence (chatGpt, Gemini, Grok) was used during development for the following tasks:

- Clarifying edge-case behavior of certain functions (e.g., exact behavior of strlcpy/strlcat on truncation).
- Generating pseudo-code explanations and summarizing function requirements.
- Helping structure this README.md file.
- Debugging rare corner cases (e.g., ft_itoa with INT_MIN).

**AI was not used to generate the actual implementation code of any function. All source code was written manually by the student.**

![42](https://imgs.search.brave.com/ZJD_fa2-7tWJvDIS__i3LSpQhM6NgglceHFzEvcA3_Q/rs:fit:860:0:0:0/g:ce/aHR0cHM6Ly9naXRo/dWIuY29tL3VkZGlu/LWEvbGliZnQvcmF3/L21hc3Rlci8ubWlz/Yy9pbWFnZXMvbGli/ZnRfaGVhZGVyLnBu/Zw)

# FIRST PART
---
### ft_isalpha
---
#### Explanation
`ft_isalpha(c)` checks if the character `c` is an alphabetic character (A-Z or a-z). It returns a non-zero value if true, otherwise zero. This function is locale-dependent but typically checks against ASCII ranges.

#### Pseudo Code

```C
int    ft_isalpha(int c)
{
    if (/* c value is one of the lowercase letter in the ASCII table  or if c value is one the uppercase letter in the ASCII table*/)
        return (/* non-zero value of your choice */);
    return (0);
}
```

#### Edge Cases

- Non-character inputs (e.g., negative values or values > 127 in signed char).
- Locale-specific characters (e.g., accented letters in non-ASCII locales).
- EOF value (typically -1), which should return false.

___
### Is the Cast to `unsigned char` Necessary?

No, not strictly for this specific implementation, but it is **highly recommended** as a best practice.

#### 1. Why it's not strictly necessary here

You are only checking the basic ASCII range (A-Z and a-z), which have positive values (65–90 and 97–122). These positive values are unaffected by sign extension, even if the input `char` was interpreted as signed.

#### 2. Why it's necessary in general (Best Practice)

Standard C library functions like `isalpha` are designed to handle character values greater than 127 (extended ASCII or non-ASCII characters).

- If your system uses a **signed** `char`, any character value > 127 (e.g., 130) is converted to a **negative** integer (e.g., -126) when passed as an `int` argument.
- Comparing a negative integer to positive character literals like `'a'` will fail incorrectly.
- The cast `(unsigned char)c` prevents sign extension by ensuring the value is converted to `int` as its original positive byte value before comparison.

#### Conclusion

**Keep the cast.**  
It aligns with the standard library's robust handling of character inputs and prevents subtle bugs on systems where `char` is signed—especially important if you ever extend the function to check a wider range of characters (like `isprint` or `isalnum`).


### Why the original functions return value is different from my code?
The Standard isalpha Return ValueThe POSIX standard for isalpha (and other <ctype.h> functions) states:"The isalpha() function returns non-zero if $c$ is a character for which isupper() or islower() is true, and 0 if $c$ is not such a character."The key is non-zero, not necessarily 1.The standard library's implementation often returns the value of the mask or an intermediate calculation, not necessarily a simple 1.A common way to implement these functions uses a lookup table (an array of character flags).Example of a Common Standard Library Implementation LogicImagine a global array, __ctype_b_loc, where each index corresponds to a character's value (0-255), and the value at that index is a bitmask of properties (e.g., bit 1 = is alpha, bit 2 = is digit, etc.):

---
### isdigit
---
#### Explanation
`isdigit(c)` checks if the character `c` is a decimal digit (0-9). It returns a non-zero value if true, otherwise zero.

#### Pseudo Code
```c
int    ft_isdigit(int c)
{
    if (/* c value is one of the decimal digit characters in the ASCII table */)
        return (/* non-zero value of your choice */);
    return (0);
}
```
#### Edge Cases

- Non-ASCII digits (e.g., full-width digits in Unicode).
- Negative char values or values outside 0-255.
- Hexadecimal digits like 'A' (should return false).

---
### isalnum
---
#### Explanation
`isalnum(c)` checks if the character `c` is alphanumeric (A-Z, a-z, or 0-9). It returns a non-zero value if true, otherwise zero.
#### Pseudo Code
```C
int    ft_isalnum(int c)
{
    if (/* c isalpha or c isdigit */)
        return (/* non-zero value of your choice */);
    return (0);
}
```
### Edge Cases

- Punctuation or symbols (e.g., '_') – should return false.
- Locale-dependent alphanumerics.
- EOF or invalid char values.

---
### isascii
---
#### Explanation
`isascii(c)` checks if the character `c` is a 7-bit ASCII character (0-127). It returns a non-zero value if true, otherwise zero. This is not standard C but often available as an extension.
#### Pseudo Code
```C
int    ft_isascii(int c)
{
    if (/* c is between 0 and decimal 127 */)
        return (/* non-zero value of your choice */);
    return (0);
}
```
#### Edge Cases

- Negative values in signed char (e.g., -1).
- Extended ASCII (128-255) – should return false.
- Non-integer inputs if cast improperly.

---
### isprint
---
#### Explanation
`isprint(c)` checks if the character `c` is printable (including space, but excluding control characters). It returns a non-zero value if true, otherwise zero.
#### Pseudo Code
```C
int    ft_isprint(int c)
{
    if (/* c is between 32 and 126 */)
        return (/* non-zero value of your choice */);
    return (0);
}
```
#### Edge Cases

- Control characters (e.g., '\n', ASCII 10) – false.
- Delete character (ASCII 127) – often false.
- Extended characters (>127) – locale-dependent.

---
### strlen
---
#### Explanation
`strlen(s)` returns the length of the null-terminated string `s`, excluding the null terminator.
#### Pseudo Code
```C
size_t    ft_strlen(const char *s)
{
    while( /* we are not reading \0 character */)
        /* increment a counter and read next char */
    return (/* the counter */);
}
```
#### Edge Cases

- NULL pointer – undefined behavior (crash).
- Empty string ("") – returns 0.
- String without null terminator – infinite loop or overflow.

---
### memset
---
#### Explanation
`memset(s, c, n)` sets the first `n` bytes of the memory area pointed to by `s` to the value `c`.
#### Pseudo Code
```C
void    *ft_memset(void *b, int c, size_t len)
{
    /* declare a temporary unsigned char * */
    /* make this temporary variable equals to void *b converted to unsigned char */
    /* loop on the temporary variable while we didn't reach len */
        /* in that loop, set the current byte equal to c converted to unsigned char */
    /* return void *b */
}
```
#### Edge Cases

- NULL pointer for s – undefined.
- n=0 – no-op, returns s.
- Overlapping memory or invalid n (e.g., larger than allocated) – buffer overflow.

---
### bzero
---
#### Explanation
`bzero(s, n)` sets the first `n` bytes of the memory area pointed to by `s` to zero. This is a BSD extension, equivalent to memset(s, 0, n).
#### Pseudo Code
```C
void    ft_bzero(void *s, size_t n)
{
    /* declare a temporary pointer */
    /* make the temporary pointer equal to *s converted to a char * */
    /* loop on the temporary pointer while we didn't reach n characters */
        /* in that loop, set the current byte equal to 0 */
}
```
#### Edge Cases

- Same as memset, but specifically for zeroing.
- n larger than allocated memory – overflow.
- NULL s – undefined.

---
### memcpy
---
#### Explanation
`memcpy(dest, src, n)` copies `n` bytes from memory area `src` to `dest`. It does not handle overlapping regions safely.
#### Pseudo Code
```C
void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    /* declare a temporary pointer for dst */
    /* declare a temporary pointer for src */
    
    /* if src and dst are NULL, return dst */
    /* make dst tmp pointer equal to dst converted to unsigned char * */
    /* make src tmp pointer equal to src converted to unsigned char * */
    /* loop over the dst tmp pointer while we didn't reach n */
        /* set the current byte of dst tmp pointer equal to current byte of src tmp pointer */
        /* return dst */
}
```
#### Edge Cases

- Overlapping src and dest – undefined behavior.
- NULL pointers – undefined.
- n=0 – no-op.

---
### memmove
---
#### Explanation
`memmove(dest, src, n)` copies `n` bytes from `src` to `dest`, handling overlapping regions safely (uses a temporary buffer if needed).
#### Pseudo Code
```C
void    *ft_memmove(void *dst, const void *src, size_t len)
{
    /* declare 2 temporary pointer for src and dst */
    /* declare a counter */
    /* check if both src and dst are NULL */
    /* make dst tmp pointer equal to dst converted to char * */
    /* make src tmp pointer equal to src converted to char * */
    /* if src and dst are overlapping */
        /* loop while len is greater than 0 and copy src into dst */
    /* if src and dst are not overlapping */
        /* loop while our counter is less than len and copy src into dst */
    /* return dst */
}
```
#### Edge Cases

- Overlapping regions (e.g., dest = src + 1).
- NULL pointers – undefined.
- Same src and dest – no-op if n valid.

<https://cs50.stackexchange.com/questions/14615/memory-overlap-in-c>
### What is memory overlapping ?
Suppose we have an array of 5 chars, where each char is a byte long


```C
+++++++++++++++++++++++++++++++
| 'a' | 'b' | 'c' | 'd' | 'e' |
+++++++++++++++++++++++++++++++
 0x100 0x101 0x102 0x103 0x104
 ```
 Now according to the man page of `memcpy`, it takes 3 arguments, a pointer to the destination block of memory, a pointer to the source block of memory, and the size of bytes to be copied.

What if the destination is `0x102`, the source is ``0x100`` and the size is `3` ?
Memory overlapping happens here. That is, ``0x100`` would be copied into ``0x102``, ``0x101`` would be copied into ``0x103`` and ``0x102`` would be copied into ``0x104``.

Notice that we first copied into ``0x102`` then we copied from ``0x102`` which means that the value which was originally in ``0x102`` was lost as we overwrote it with the value we copied into ``0x102`` before we copy from it. So we would end up with something like

```C
+++++++++++++++++++++++++++++++
| 'a' | 'b' | 'a' | 'b' | 'a' |
+++++++++++++++++++++++++++++++
 0x100 0x101 0x102 0x103 0x104
 ```
Instead of


```C
+++++++++++++++++++++++++++++++
| 'a' | 'b' | 'a' | 'b' | 'c' |
+++++++++++++++++++++++++++++++
 0x100 0x101 0x102 0x103 0x104
 ```
 ##### How does a function like memmove take care of memory overlapping ?

According to its man page, it first copies the bytes to be copied into a temporary array then pastes them into the destination block as oppose to a function like ``memcpy`` which copies directly from the source block to the destination block.

That's for memory overlapping, it is also said that ``memmove`` copies the bytes to be copied into a temporary array then pastes them into the destination block. That's not the way I did it because as said in the subject of the LIBFT, we can't use ``malloc()`` for this function.

The way I did it without using ``malloc()``, is to first check if the 2 memory blocks are overlapping or not. If they are overlapping we'll copy from the end of the source memory block until the start. If they are not overlapping we'll copy "normally", from start to end.

---
### strlcpy
---
#### Explanation
`strlcpy(dest, src, size)` copies the null-terminated string `src` to `dest`, ensuring null-termination and not exceeding `size` bytes. Returns the length of src. This is a BSD extension for safer string copying.
#### Pseudo Code
```C
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    /* get the length of src */
    /* check if dstsize is big enough to accomodate src length 
     * plus the NUL character
     */
    /* copy the whole src into dst */
    /* else */
    /* copy dstsize - 1 characters into dst */
    return (/* length of src */);
}
```
#### Edge Cases

- size=0 – no copy, returns src length.
- src longer than size – truncated, null-terminated.
- NULL pointers – undefined.

---
### strlcat
---
#### Explanation
`strlcat(dest, src, size)` appends `src` to `dest`, ensuring null-termination and not exceeding `size` bytes (including existing dest content). Returns the total length of the concatenated string. BSD extension.
#### seudo Code
```C
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    /* get the original length of src */
    /* get the original length of dst */
    /* if the length of dst is equal to dstsize */
    /* simply return the the length of dst + the length of src */
    /* if dstsize is big enough to accomodate both src and dst */
    /* concatenate src at the end of dst */
    /* else, concatenate dstsize character maximum */
    return (/* length of src + length of dst */);
}
```
#### Edge Cases

- dest not null-terminated – undefined.
- size <= strlen(dest) – no append, returns total length.
- NULL pointers – undefined.

---
### toupper
---
#### Explanation
`toupper(c)` converts the lowercase character `c` to uppercase if applicable, otherwise returns c unchanged.
#### Pseudo Code
```C
int    ft_toupper(int c)
{
    if (/* c is lower-case letter */)
        return (/* corresponding upper-case letter */);
    return (c);
}
```
#### Edge Cases

- Non-alphabetic characters – unchanged.
- Locale-specific (e.g., accented letters).
- Negative or invalid char values.

---
### tolower
---
#### Explanation
`tolower(c)` converts the uppercase character `c` to lowercase if applicable, otherwise returns c unchanged.
#### Pseudo Code
```C
int    ft_tolower(int c)
{
    if (/* c is an upper-case letter */)
        return (/* corresponding lower-case letter */);
    return (c);
}
```
#### Edge Cases

- Similar to toupper: non-alpha unchanged, locale issues.

---
### strchr
---
#### Explanation
`strchr(s, c)` returns a pointer to the first occurrence of character `c` in string `s`, or NULL if not found.
#### Pseudo Code
```C
char *ft_strchr(const char *s, int c)
{
    /* loop over the whole string */
    /* check if current character is equal to the one we have to find */
    /* once we looped over the whole string, check again for the character
     * in case the character we have to find is '\0'
     */
    /* if we didn't find c in the string, return NULL */
}
```
#### Edge Cases

- c = '\0' – returns pointer to end of string.
- NULL s – undefined.
- Empty s – NULL unless c='\0'.

---
### strrchr
---
#### Explanation
`strrchr(s, c)` returns a pointer to the last occurrence of character `c` in string `s`, or NULL if not found.
#### Pseudo Code
```C
char *ft_strrchr(const char *s, int c)
{
    /* we can use basically the same code as ft_strchr() but not returning
     * the value as soon as we find the character, just setting a variable
     * each time, and returning it at the end of the function
     */
    /* loop over the whole string */
    /* check if current character is equal to the one we have to find */
    /* once we looped over the whole string, check again for the character
     * in case the character we have to find is '\0'
     */
    /* if we didn't find c in the string, return NULL */
}
```
#### Edge Cases

- c = '\0' – returns pointer to end.
- Multiple occurrences – returns last.
- NULL s or not found – NULL.

---
### strncmp
---
#### Explanation
`strncmp(s1, s2, n)` compares the first `n` characters of `s1` and `s2`, returning <0 if s1 < s2, >0 if s1 > s2, 0 if equal.
#### Pseudo Code
```C
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    /* loop over both string until we reach n characters */
    /* check if current s1 character is different than
     * current s2 character
     */
         /* if characters are different, return the difference
          * between both characters
          */
      /* if we read both strings until n characters and no difference
       * were found, return 0 as there is no difference
       */
}
```
#### Edge Cases

- n=0 – returns 0.
- One string shorter than n – compares up to null.
- NULL pointers – undefined.

---
### memchr
---
#### Explanation
`memchr(s, c, n)` returns a pointer to the first occurrence of byte `c` in the first `n` bytes of `s`, or NULL if not found.
#### Pseudo Code
```C
void *ft_memchr(const void *s, int c, size_t n)
{
    /* as said in the man, the search is done for c converted to
     * an unsigned char, so we have to convert both c and s to 
     * unsigned char
     */
    /* loop over the byte string until our counter is equal to n */
    /* compare the current byte to c */
        /* if they are the same, return the address of this byte as a
         * void *
         */
    /* if we searched n bytes and didn't find what we were looking for
     * return NULL
     */
    /* as you can see, this is very close to the strchr and strrchr
     * functions, so take a look at these before looking at the
     * solution
     */
}
```
#### Edge Cases

- n=0 – NULL.
- c not a byte value (truncated).
- NULL s – undefined.

---
### memcmp
---
#### Explanation
`memcmp(s1, s2, n)` compares the first `n` bytes of `s1` and `s2`, returning <0, >0, or 0 similar to strncmp but for memory.
#### Pseudo Code
```C
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    /* loop over both strings until we reach n bytes */
    /* check if current s1 byte is different than current
     * s2 byte
     */
           /* if bytes are different, return the difference
            * between both characters
            */
     /* if we read both byte strings until n bytes and no difference
      * were found, return 0 as there is no difference
      */
}
```
#### Edge Cases

- n=0 – 0.
- Unsigned comparison (bytes treated as unsigned).
- NULL pointers – undefined.

---
### strnstr
---
#### Explanation
`strnstr(haystack, needle, len)` searches for the substring `needle` in the first `len` bytes of `haystack`. Returns pointer to first occurrence or NULL. POSIX/BSD extension.
#### Pseudo Code
```C
char *ft_strnst(const char *haystack, const char *needle, size_t len)
{
    /* check if needle is empty */
        /* return haystack */
    /* loop over haystack */
        /* while current character of haystack is equal to the corresponding
         * character in needle */
             /* check if we have the complete needle */
}
```
#### Edge Cases

- Empty needle – returns haystack.
- len < needle length – NULL.
- NULL pointers – undefined.

---
### atoi
---
#### Explanation
`atoi(s)` converts the string `s` to an integer, ignoring leading whitespace and stopping at non-digit. Handles optional sign.
#### Pseudo Code
```C
textfunction atoi(s):
    i = 0
    while s[i] is whitespace: i += 1
    sign = 1
    if s[i] == '-': sign = -1; i += 1
    elif s[i] == '+': i += 1
    result = 0
    while s[i] is digit:
        result = result * 10 + (s[i] - '0')
        i += 1
    return sign * result
```
#### Edge Cases

- Overflow (e.g., "999999999999" – undefined, often wraps).
- Invalid strings (e.g., "abc" – 0).
- Leading zeros (e.g., "00123" – 123).
- NULL s – undefined.

---
### calloc
---
#### Explanation
c`alloc(nmemb, size)` allocates memory for an array of `nmemb` elements, each of `size` bytes, and initializes all bytes to zero. It returns a pointer to the allocated memory (properly aligned for any type) or NULL if allocation fails.
Unlike malloc(nmemb * size), calloc performs zero-initialization and checks for integer overflow in the multiplication (in good implementations).
#### Pseudo Code
```C
textfunction calloc(nmemb, size):
    total_size = nmemb * size
    if total_size overflows or nmemb == 0 or size == 0:
        return NULL  // some implementations return NULL for 0
    ptr = malloc(total_size)  // or equivalent allocation
    if ptr == NULL:
        return NULL
    memset(ptr, 0, total_size)
    return ptr
```
#### Edge Cases

- nmemb == 0 or size == 0: Standard allows returning either NULL or a unique - - pointer that can be freed (implementation-defined).
- Overflow in nmemb * size (e.g., very large values): Should return NULL (POSIX - requires this check).
- Allocation failure (out of memory): Returns NULL.
- Alignment: Returned pointer must be suitably aligned for any object type.

---
### strdup
---
#### Explanation
`strdup(s)` creates a duplicate of the null-terminated string `s` by allocating sufficient memory with malloc and copying the string (including the terminating '\0'). It returns a pointer to the new string or NULL if allocation fails or if s is NULL (some implementations).
This function is not part of the C standard but is a POSIX/BSD extension widely available.
#### Pseudo Code
```C
textfunction strdup(s):
    if s == NULL:
        return NULL  // optional; some implementations undefined
    len = strlen(s) + 1  // include null terminator
    ptr = malloc(len)
    if ptr == NULL:
        return NULL
    memcpy(ptr, s, len)  // or strcpy(ptr, s)
    return ptr
```
#### Edge Cases

- s == NULL: Behavior is undefined by POSIX (some implementations return NULL, others crash). Always check input in portable code.
- Empty string "": Allocates 1 byte for '\0' and returns pointer to it.
- Allocation failure: Returns NULL.
- Very long strings: Risk of integer overflow in strlen(s) + 1 or malloc failure.
- The caller is responsible for free()-ing the returned pointer.

---
![part two](https://dwaves.de/wp-content/uploads/2022/06/gnu-linux-bash-console-ascii-art-sl-steam-locomotive.gif)

# SECOND PART
---
### ft_substr
---
#### Explanation
`ft_substr(s, start, len)` allocates memory using malloc and returns a new null-terminated string that is a substring of `s`.
The substring begins at index `start` in s and has a maximum length of `len` characters (not including the terminating '\0').
If start is beyond the end of s, or if allocation fails, the function returns NULL.
If the remaining part of s starting from start is shorter than len, the substring will be as long as possible (up to the end of s).
#### Pseudo Code
```C 
ft_substr(s, start, len):
    if s == NULL:
        return NULL
    
    string_length = strlen(s)
    
    // If start is beyond the string, return empty string
    if start >= string_length:
        return malloc(1) and set to "\0"  // or simply return NULL in some interpretations, but usually empty string
    
    // Effective length: min(len, remaining characters)
    actual_len = min(len, string_length - start)
    
    // Allocate memory: actual_len characters + 1 for '\0'
    substr = malloc(actual_len + 1)
    if substr == NULL:
        return NULL
    
    // Copy the characters
    for i from 0 to actual_len - 1:
        substr[i] = s[start + i]
    
    substr[actual_len] = '\0'
    
    return substr
```
#### Edge Cases

- s == NULL: Should return NULL (undefined behavior if not checked, but safe implementations check it).
- start >= strlen(s): Should return a pointer to an empty string (""), i.e., malloc(1) with '\0'.
- len == 0: Should return an empty string (allocates 1 byte for '\0').
- start + len overflows or exceeds string length: Only copy up to the end of s.
- Allocation failure (malloc returns NULL): Return NULL immediately.
- Very large len (e.g., SIZE_MAX): Limited by remaining string length and available memory.
- The returned string must be free()-able by the caller.

#### Example Behaviors

| s          | start | len | Result       |
|------------|-------|-----|--------------|
| "hello"    | 0     | 5   | "hello"      |
| "hello"    | 2     | 3   | "llo"        |
| "hello"    | 5     | 10  | "" (empty)   |
| "hello"    | 10    | 5   | "" (empty)   |
| "hello"    | 1     | 0   | "" (empty)   |
| NULL       | any   | any | NULL         |

---
### ft_strjoin
---
#### Explanation
`ft_strjoin(s1, s2)` allocates memory using malloc and returns a new null-terminated string that is the concatenation of `s1` followed by `s2`.
The function creates a fresh copy of both strings in the new allocated memory. The original strings s1 and s2 are not modified.
If either s1 or s2 is NULL, behavior is typically undefined.
If memory allocation fails, the function returns NULL.
#### Pseudo Code
```C
 ft_strjoin(s1, s2):
    if s1 == NULL or s2 == NULL:
        return NULL  // strict version; some implementations handle NULL as ""

    len1 = strlen(s1)
    len2 = strlen(s2)
    total_len = len1 + len2

    new_str = malloc(total_len + 1)  // +1 for '\0'
    if new_str == NULL:
        return NULL

    // Copy s1
    for i from 0 to len1 - 1:
        new_str[i] = s1[i]

    // Copy s2
    for i from 0 to len2 - 1:
        new_str[len1 + i] = s2[i]

    new_str[total_len] = '\0'

    return new_str
```
Alternatively, using memcpy (more efficient):
```C
textnew_str = malloc(strlen(s1) + strlen(s2) + 1)
if new_str == NULL:
    return NULL
memcpy(new_str, s1, len1)
memcpy(new_str + len1, s2, len2)
new_str[len1 + len2] = '\0'
return new_str
```
#### Edge Cases

- s1 == NULL or s2 == NULL: In strict 42/libft, this is undefined behavior (often results in crash). Some student implementations check and return NULL or treat as empty string — but for evaluation, assume inputs are valid.
- One or both strings are empty (""): Should work correctly (e.g., ft_strjoin("", "hello") → "hello").
- Very long strings: Risk of integer overflow in strlen(s1) + strlen(s2) (if sum exceeds size_t max), or malloc failure.
- Allocation failure: Must return NULL.
- The returned string must be free()-able by the caller.

### Example Behaviors

| s1         | s2         | Result                          |
|------------|------------|---------------------------------|
| "hello"    | " world"   | "hello world"                   |
| "abc"      | ""         | "abc"                           |
| ""         | "def"      | "def"                           |
| ""         | ""         | ""                              |
| "prefix"   | "suffix"   | "prefixsuffix"                  |
| NULL       | "test"     | Undefined (crash or NULL depending on impl) |

---
### ft_strtrim
---
#### Explanation
`ft_strtrim(s1, set)` allocates memory using malloc and returns a new null-terminated string that is a copy of `s1` with all characters specified in `set` removed from the beginning and end of the string.
Only leading and trailing characters matching any character in set are removed. Characters in the middle of s1 are preserved, even if they appear in set.
If s1 consists entirely of characters from set, an empty string ("") is returned.
If allocation fails, the function returns NULL.
#### Pseudo Code
```C
 ft_strtrim(s1, set):
    if s1 == NULL or set == NULL:
        return NULL  // strict behavior; some handle NULL set as trim nothing

    // Find the first character not in set (start index)
    start = 0
    while s1[start] != '\0' and s1[start] is in set:
        start += 1

    // If we reached the end, whole string is trimmable → return empty string
    if s1[start] == '\0':
        return malloc(1) with '\0'  // empty string

    // Find the last character not in set (end index)
    end = strlen(s1) - 1
    while end > start and s1[end] is in set:
        end -= 1

    // Length of the trimmed string
    trim_len = end - start + 1

    // Allocate memory
    trimmed = malloc(trim_len + 1)
    if trimmed == NULL:
        return NULL

    // Copy the middle part
    for i from 0 to trim_len - 1:
        trimmed[i] = s1[start + i]

    trimmed[trim_len] = '\0'

    return trimmed
```
#### Helper: "is in set" check
To check if a character is in set, loop through set until '\0' or match found:
```C
 char_in_set(c, set):
    i = 0
    while set[i] != '\0':
        if set[i] == c:
            return true
        i += 1
    return false
```
#### Edge Cases

- s1 == NULL or set == NULL: In strict 42/libft, behavior is undefined (likely crash). Most evaluators expect no explicit check — assume inputs are valid.
- set is empty (""): No characters to trim → return a full copy of s1.
- s1 is empty (""): Return an empty string.
- All characters in s1 are in set: Return an empty string (malloc(1) with '\0').
- No characters need trimming: Return a full copy of s1.
- Only leading/trailing characters to trim: Correctly remove them.
- set contains duplicate characters: Doesn't matter — treated as a set.
- Very long s1 or set: Risk of malloc failure or performance issues (but O(n×m) is acceptable for libft).

### Example Behaviors

| s1              | set     | Result                                      |
|-----------------|---------|---------------------------------------------|
| " hello "       | ""      | "hello"                                     |
| "xxxabcxxx"     | "x"     | "abc"                                       |
| "abc"           | "x"     | "abc"                                       |
| "xxx"           | "x"     | "" (empty string)                           |
| ""              | "abc"   | ""                                          |
| "hello"         | ""      | "hello"                                     |
| "aaabaac"       | "ac"    | "b"                                         |
| "hello world"   | "helo " | "world" → "world" (removes 'h','e','l','l','o' and spaces from ends) |

---
### ft_split
---
#### Explanation
`ft_split(s, c)` allocates memory using malloc and returns a dynamically allocated array of strings (char **) obtained by splitting the input string `s` using the character `c` as a delimiter.

Consecutive occurrences of c are treated as a single delimiter (i.e., empty substrings between delimiters are ignored).
Leading or trailing delimiters do not produce empty strings.
The returned array is null-terminated (last element is NULL).
Each substring in the array is null-terminated.
If allocation fails at any point, the function must free all previously allocated memory and return NULL.
If s is NULL, behavior is typically undefined (no check required in strict 42 libft).

#### Pseudo Code
```C
 ft_split(s, c):
    if s == NULL:
        return NULL  // optional, not required by subject

    // First pass: count the number of words
    word_count = 0
    i = 0
    in_word = false

    while s[i] != '\0':
        if s[i] == c:
            in_word = false
        else:
            if in_word == false:
                word_count += 1
                in_word = true
        i += 1

    // Allocate array for word_count + 1 (for NULL terminator)
    result = malloc((word_count + 1) * sizeof(char *))
    if result == NULL:
        return NULL

    // Second pass: extract each word
    index = 0
    i = 0
    while s[i] != '\0':
        // Skip delimiters
        while s[i] == c:
            i += 1
        if s[i] == '\0':
            break

        // Find start of word
        start = i
        while s[i] != '\0' and s[i] != c:
            i += 1
        end = i  // points to delimiter or '\0'

        // Length of current word
        word_len = end - start

        // Allocate memory for the word + '\0'
        result[index] = malloc(word_len + 1)
        if result[index] == NULL:
            // Free everything allocated so far
            for j from 0 to index - 1:
                free(result[j])
            free(result)
            return NULL

        // Copy the word
        for k from 0 to word_len - 1:
            result[index][k] = s[start + k]
        result[index][word_len] = '\0'

        index += 1

    // Null-terminate the array
    result[word_count] = NULL

    return result
```
#### Edge Cases

- s == NULL: Undefined behavior (crash if accessed). Most evaluators expect no check.
- c appears nowhere in s: Returns an array with one string (copy of s), plus NULL.
- s is empty (""): Returns array with single NULL pointer: {NULL}.
- Only delimiters (e.g., "///", c='/'): Returns {NULL}.
- Leading delimiters (e.g., ",,,abc", c=','): Skips them → {"abc", NULL}.
- Trailing delimiters (e.g., "abc,,,"): Skips them → {"abc", NULL}.
- Consecutive delimiters (e.g., "a,,b,c"): → {"a", "b", "c", NULL} (no empty strings).
- c is '\0': Should not happen (delimiter is a char), but would split on nulls — avoid.
- Allocation failure:
- On array allocation → return NULL.
- On any word allocation → free all previous words and the array, then return NULL.

- Very long string or many words: Risk of multiple malloc failures — must clean up properly.

### Example Behaviors

| s                  | c | Result (array content)                  |
|--------------------|---|----------------------------------------|
| "hello world"      | " " | {"hello", "world", NULL}                |
| " split this "     | " " | {"split", "this", NULL}                 |
| "abc"              | " " | {"abc", NULL}                           |
| ""                 | " " | {NULL}                                  |
| ",abc,,def,"       | "," | {"abc", "def", NULL}                    |
| "one,two,three"    | "," | {"one", "two", "three", NULL}           |
| "no_delim_here"    | "/" | {"no_delim_here", NULL}                 |


**Note:** In the 42 libft project, correct memory management on failure is crucial. Many students fail evaluation because they leak memory when a malloc fails midway. Always free everything allocated before returning NULL. Also, do not create empty strings between delimiters — this is a common mistake.

---
### ft_itoa
---
#### Explanation
`ft_itoa(n)` allocates memory using malloc and returns a null-terminated string representing the integer `n`.
The function must correctly handle:

- Positive numbers
- Negative numbers (including the sign -)
- The special case of INT_MIN (-2147483648), which is tricky because its absolute value (2147483648) cannot be represented as a positive int (overflows INT_MAX = 2147483647)

If allocation fails, the function returns NULL.
#### Pseudo Code
```C
 ft_itoa(n):
    // Special case for INT_MIN
    if n == -2147483648:
        return duplicate string "-2147483648"  // or handle manually

    // Determine sign and work with absolute value
    if n < 0:
        sign = true
        n = -n
    else:
        sign = false

    // Count digits needed
    temp = n
    digit_count = 0
    if temp == 0:
        digit_count = 1
    while temp > 0:
        digit_count += 1
        temp = temp / 10

    // Total length: digits + optional sign + '\0'
    total_len = digit_count + (sign ? 1 : 0)

    // Allocate memory
    str = malloc(total_len + 1)
    if str == NULL:
        return NULL

    // Fill string from right to left
    i = total_len - 1
    str[i + 1] = '\0'  // null terminator

    if n == 0:
        str[0] = '0'
        return str

    while n > 0:
        str[i] = (n % 10) + '0'
        n = n / 10
        i -= 1

    // Add sign if negative
    if sign:
        str[i] = '-'

    return str
```
Alternative Approach (Handles INT_MIN without special case)
A common and clean method used in many libft implementations:
```C
 ft_itoa(n):
    if n == 0:
        return strdup("0")

    // Handle negative
    is_negative = (n < 0)
    if is_negative:
        n = -n  // careful: if n was INT_MIN, this is undefined in C!
        // So better to avoid negation on INT_MIN

    // Safer way: count digits and build string
    // First, count digits using unsigned or long
    long_nb = (long)n
    if is_negative:
        long_nb = -long_nb

    digit_count = 0
    temp = long_nb
    repeat:
        digit_count += 1
        temp /= 10
    until temp == 0

    total_len = digit_count + (is_negative ? 1 : 0)
    str = malloc(total_len + 1)
    if str == NULL:
        return NULL

    str[total_len] = '\0'

    // Fill digits
    i = total_len - 1
    while long_nb > 0:
        str[i] = (long_nb % 10) + '0'
        long_nb /= 10
        i -= 1

    if is_negative:
        str[i] = '-'
    else if digit_count == 0:  // n was 0, already handled above

    return str
```
Most robust version (recommended for 42 libft):
```C
 ft_itoa(int n):
    char *str
    int len = 0
    int temp = n

    // Handle zero early
    if n == 0:
        str = malloc(2)
        if !str: return NULL
        str[0] = '0'
        str[1] = '\0'
        return str

    // Count digits (and handle negative for counting)
    if n < 0:
        len++  // for '-'
        if n == INT_MIN:
            // Handle later
        else:
            temp = -n

    temp = n < 0 ? -n : n
    while temp > 0:
        len++
        temp /= 10

    str = malloc(len + 1)
    if !str: return NULL
    str[len] = '\0'

    // Handle INT_MIN separately
    if n == INT_MIN:
        str[--len] = '8'
        n = 214748364  // now safe

    // Extract digits
    if n < 0:
        n = -n

    while n > 0:
        str[--len] = (n % 10) + '0'
        n /= 10

    if str[len] != '8':  // if not already set by INT_MIN
        if original_n < 0:
            str[--len] = '-'

    return str
```
#### Edge Cases

- n == 0: Should return "0".
- n == INT_MIN (-2147483648): Cannot negate safely → must be handled specially.
- Negative numbers: Must include the - sign.
- Positive numbers: No sign.
- Allocation failure: Return NULL.
- n == INT_MAX (2147483647): Should return "2147483647".

---
### ft_strmapi
---
#### Explanation
`ft_strmapi(s, f)` creates and returns a new string by applying the function `f` to each character of the input string `s`.

The function `f` receives two arguments:
`unsigned int`: the index of the current character in the string (starting from 0).
`char`: the current character itself.

The returned character from f is placed in the corresponding position in the new string.
The new string is null-terminated.
Memory for the new string is allocated using malloc.
If s is NULL or allocation fails, the function returns NULL.
The original string s is not modified.

#### Pseudo Code
```C
 ft_strmapi(s, f):
    if s == NULL or f == NULL:
        return NULL  // optional strict check; many implementations assume valid inputs

    len = strlen(s)

    // Allocate memory for the new string (+1 for '\0')
    result = malloc(len + 1)
    if result == NULL:
        return NULL

    i = 0
    while s[i] != '\0':
        result[i] = f(i, s[i])  // apply function with index and char
        i += 1

    result[len] = '\0'

    return result
```
#### Edge Cases

- s == NULL: In strict 42/libft, behavior is undefined (likely crash). Most evaluators expect no NULL check — assume s is valid.
- f == NULL: Undefined behavior if called (crash). Again, no check required.
- Empty string "": Should return a new empty string (malloc(1) with '\0').
- f returns the same character (identity function): Result should be an exact copy of s.
- f modifies based on index (e.g., adds index to char): Must correctly pass the index.
- Allocation failure: Must return NULL.
- Very long string: Risk of malloc failure — handle by returning NULL.

---
### ft_striteri
---
#### Explanation
`ft_striteri(s, f)` applies the function `f` to each character of the string `s` in place.

The function f receives two arguments:
`unsigned int`: the index of the current character (starting from 0).
`char*`: a pointer to the current character in the string (allowing modification).

The character can be modified directly through the pointer if desired.
The function returns void (nothing).
The string s is modified directly if f changes the characters.
No memory allocation is performed (no malloc).
If s is NULL or f is NULL, behavior is typically undefined (no checks required in 42 libft).

#### Pseudo Code
```C
 ft_striteri(s, f):
    if s == NULL or f == NULL:
        return  // optional; usually no check in libft

    i = 0
    while s[i] != '\0':
        f(i, &s[i])  // call f with index and address of character
        i += 1
```
#### Edge Cases

- s == NULL: Undefined behavior (likely crash). Do not add a NULL check — evaluators expect none.
- f == NULL: Undefined behavior if called. Again, no check required.
- Empty string "": The loop does nothing — safe and correct.
- f modifies the character: The original string s should reflect the changes.
- f does nothing: String remains unchanged.
- Very long string: Must iterate until '\0' without overflow.

#### Key Points for 42 libft

- No return value → just void.
- No malloc → no need to handle allocation failure.
- Pass the address of the character: &s[i], not s[i].
- Do not check for s == NULL or f == NULL — the subject assumes valid input.
- The function must continue until the null terminator ('\0'), but does not apply f to the '\0' itself.

Common mistake: Passing s[i] (the char value) instead of &s[i] (the pointer). This prevents modification and fails tests that expect in-place changes.
Correct call inside loop: f(i, &s[i])

---
### ft_putchar_fd
---
#### Explanation
`ft_putchar_fd(c, fd)` writes a single character `c` to the given file descriptor `fd`.

It uses the write system call from <unistd.h> to perform the output.
Common file descriptors:

1: standard output (stdout)

2: standard error (stderr)

0: standard input (stdin) – rarely used for writing
Others: opened files or pipes

The function returns void (nothing).

No memory allocation is involved.

If fd is invalid, write will fail silently (returns -1), but the function does not need to check or handle the return value according to the classic 42 libft subject.

#### Pseudo Code
```C
 ft_putchar_fd(c, fd):
    write(fd, &c, 1)
```
#### Edge Cases

- Invalid fd (e.g., negative, closed, or out of range): write returns -1 and sets errno, but the function does not need to handle this – it should still call write.
- fd refers to a read-only descriptor: write fails silently.
- Writing to stdout (fd = 1): Normal character output.
- Writing to stderr (fd = 2): Useful for error messages.
- Non-printable characters (e.g., \n, \t, \0): Should be written as-is.
- No NULL checks needed: c is a char, fd is an int – both passed by value.

---
### ft_putstr_fd
---
#### Explanation
`ft_putstr_fd(s, fd)` writes the null-terminated string `s` to the given file descriptor `fd`.

It uses the write system call from <unistd.h> to output the characters.
The string is written without the terminating '\0' (null character).
If s is NULL, behavior is typically undefined according to the classic 42 libft subject.

The function returns void.

No memory allocation is involved.

Common use: fd = 1 for stdout, fd = 2 for stderr.

#### Pseudo Code
```C
 ft_putstr_fd(s, fd):
    if s == NULL:
        return  // optional; usually NOT done in libft

    i = 0
    while s[i] != '\0':
        i += 1

    write(fd, s, i)  // write the exact length of the string
```
Alternatively (more efficient, single write call):
```C
 ft_putstr_fd(s, fd):
    write(fd, s, strlen(s))
```
Or character-by-character (less efficient but sometimes seen):
```C
texti = 0
while s[i] != '\0':
    write(fd, &s[i], 1)
    i += 1
```
#### Edge Cases

- s == NULL: Undefined behavior if accessed. Do not add a NULL check unless you are certain your evaluator accepts it — many strict versions mark it as incorrect or unnecessary.
- Empty string "": Writes 0 bytes — does nothing (safe).
- Very long string: write may not write all bytes atomically on some systems, but for libft this is acceptable (no need to loop on partial writes).
- Invalid fd: write returns -1, but the function does not need to check or handle errors.
- Non-printable characters or newlines in s: Written as-is.

---
### ft_putendl_fd
---
#### Explanation
`ft_putendl_fd(s, fd)` writes the null-terminated string `s` to the given file descriptor `fd`, followed by a newline character `'\n'`.

It uses the write system call from <unistd.h>.

The output consists of:

All characters of s up to (but not including) the terminating '\0'.
A final '\n'.

The function returns void.

No memory allocation is involved.

If s is NULL, behavior is typically undefined — most 42 evaluators expect no NULL check.

Common usage: fd = 1 (stdout) or fd = 2 (stderr).


#### Pseudo Code
```C
 ft_putendl_fd(s, fd):
    // Optional: if s == NULL return  (usually NOT done in strict libft)

    // First, write the string itself
    if s != empty:
        len = 0
        while s[len] != '\0':
            len += 1
        write(fd, s, len)

    // Then write the newline
    write(fd, "\n", 1)
```
More efficient versions combine both writes, often using ft_putstr_fd internally if already implemented:
```C
textft_putstr_fd(s, fd)
write(fd, "\n", 1)
```
#### Edge Cases

- s == NULL: Undefined behavior (likely crash if dereferenced). Do not add if (!s) return; — many evaluators reject it.
- Empty string "": Writes only a newline (\n).
- String already ending with \n: Will output two newlines.
- Invalid fd: write fails silently (returns -1), but no error handling required.
- Non-printable characters: Written as-is.

---
### ft_putnbr_fd
---
#### Explanation
`ft_putnbr_fd(n, fd)` writes the integer `n` as a string to the given file descriptor `fd`.

It uses only the write system call (from <unistd.h>).

The function must handle:

Positive numbers

Negative numbers (including the - sign)

The special value INT_MIN (-2147483648)

Zero


No memory allocation is allowed (no malloc).

The function returns void.

If fd is invalid, write will fail, but no error checking is required.

According to classic 42 libft rules, n is assumed valid — no special handling beyond correct output.

#### Pseudo Code
```C
 ft_putnbr_fd(n, fd):
    if n == -2147483648:  // INT_MIN
        write(fd, "-", 1)
        write(fd, "2147483648", 10)
        return

    if n < 0:
        write(fd, "-", 1)
        n = -n

    if n >= 10:
        ft_putnbr_fd(n / 10, fd)  // recursive call for higher digits

    char digit = (n % 10) + '0'
    write(fd, &digit, 1)
```
Non-recursive version (often preferred to avoid stack overflow on very deep recursion, though not an issue for int):
```C
 ft_putnbr_fd(n, fd):
    char buffer[12]  // enough for -2147483648 + '\0'
    int i = 0
    int is_negative = 0

    if n == 0:
        write(fd, "0", 1)
        return

    handle sign first
    if n < 0:
        write(fd, "-", 1)
        if n == -2147483648:
            write(fd, "2147483648", 10)
            return
        n = -n

    // Now extract digits into buffer backwards
    i = 0
    while n > 0:
        buffer[i++] = (n % 10) + '0'
        n = n / 10

    // Write digits in reverse order
    while i > 0:
        i -= 1
        write(fd, &buffer[i], 1)
```
#### Edge Cases

- n == 0: Must output "0".
- n == INT_MIN (-2147483648): Cannot safely do -n (undefined behavior). Must be handled specially.
- Negative numbers: Print - then the absolute value.
- Positive large numbers (e.g., 2147483647): Correct digit output.
- Invalid fd: No handling required.
- No buffer or malloc allowed: Must use recursion or small fixed buffer.

---

![linked list](https://swagosaure.com/blog/terminal_swag/terminal_swag.gif)

---
### ft_lstnew
---
#### Explanation
``ft_lstnew(content)`` allocates memory for a new linked list node and initializes it.

The node structure (typically defined in the header) is:
```C
typedef struct s_list
{
    void    *content;
    struct s_list *next;
}           t_list;
```
The function:
- Allocates memory for one t_list node using malloc.
- Sets the content member to the provided content parameter.
- Sets the next member to NULL.
- Returns a pointer to the newly created node.

- If allocation fails, the function returns NULL.

#### Pseudo Code
```C
 ft_lstnew(content):
    new_node = malloc(sizeof(t_list))
    if new_node == NULL:
        return NULL

    new_node->content = content
    new_node->next = NULL

    return new_node
```
#### Edge Cases

- content == NULL: Perfectly valid — the node can store a NULL pointer as content. Must be handled correctly (i.e., just assign it).
- Allocation failure: malloc returns NULL → function must return NULL.
- Large content (e.g., big struct): No issue — content is just a void*, no copying occurs.
- The caller is responsible for managing (freeing) the memory pointed to by content if necessary.

---
### ft_lstadd_front
---
#### Explanation
`ft_lstadd_front(lst, new)` adds the node `new` to the beginning (front) of the linked list pointed to by `*lst`.

lst is a pointer to the current head of the list (i.e., t_list **), allowing the function to modify the head pointer itself.

new is the already-allocated node (typically created with ft_lstnew) that will become the new first element.

After the operation:

- new->next points to the former first node (old *lst).

- *lst now points to new.


The function returns void.

No memory allocation is performed inside this function.

The list can be empty (*lst == NULL), in which case new becomes the only node.

#### Pseudo Code
```C
 ft_lstadd_front(lst, new):
    if new == NULL:
        return  // optional; usually no check in libft bonus

    new->next = *lst
    *lst = new
```
#### Edge Cases

- *lst == NULL (empty list): The function correctly sets *lst = new, and new->next = NULL (already set by ft_lstnew).
- new == NULL: Behavior is undefined (likely crash if dereferenced). Do not add a NULL check for new — evaluators typically expect none. Some add if (!new) return;, but strict versions omit it.
- lst == NULL: Undefined behavior (dereferencing NULL pointer). Assume lst is valid.
- List with one or more nodes: new becomes the new head, old head becomes second node.
- Adding the same node multiple times: Possible, but creates cycles or issues — not handled here.

#### Key Points

- Parameter lst is t_list **: double pointer to modify the head.
- Parameter new is t_list *: single pointer to the new node.

Only two assignments needed:
- new->next = *lst;
- *lst = new;

Order matters — set next first, then update the head.

---
### ft_lstsize
---
#### Explanation
`ft_lstsize(lst)` returns the number of nodes in the singly linked list starting from `lst`.

The function traverses the list by following the next pointers until it reaches NULL.

It counts each node encountered.

An empty list (lst == NULL) has a length of 0.

The function does not modify the list.

No memory allocation or external functions are needed.


#### Pseudo Code
```C
 ft_lstsize(lst):
    count = 0
    current = lst
    while current != NULL:
        count += 1
        current = current->next
    return count
```
#### Edge Cases

- lst == NULL: Should return 0 (empty list).
- List with one node: Returns 1.
- List with multiple nodes: Correctly counts all.
- Very long list: As long as memory allows, it will count correctly (no overflow concern for int in libft context).
- content being NULL: Irrelevant — we only follow next pointers.

#### Key Points

- Parameter is t_list *lst (single pointer) — we do not need ** because we don't modify the head.
- Must handle lst == NULL by returning 0 (no crash).
- Do not use recursion (although possible, iteration is preferred and avoids stack overflow).
- Simple loop is sufficient and expected.
- No need to access content — only traverse next.

---
### ft_lstlast
---
#### Explanation
`ft_lstlast(lst)` returns a pointer to the last node of the singly linked list starting from `lst`.

The function traverses the list by following the next pointers until it reaches a node whose next is NULL.

That node is the last one and is returned.

If the list is empty (lst == NULL), the function returns NULL.

The function does not modify the list.

No memory allocation or external functions are needed.


#### Pseudo Code
```C
 ft_lstlast(lst):
    if lst == NULL:
        return NULL

    current = lst
    while current->next != NULL:
        current = current->next
    return current
```
#### Edge Cases

- lst == NULL (empty list): Returns NULL.
- List with only one node (lst->next == NULL): Returns lst itself.
- List with multiple nodes: Returns the final node (where next == NULL).
- Very long list: Traverses correctly until the end.

---
### ft_lstadd_back
---
#### Explanation
`ft_lstadd_back(lst, new)` adds the node `new` to the end (back) of the linked list whose head is pointed to by `*lst`.

lst is a pointer to the head pointer (t_list **), allowing the function to modify the head if the list is empty.

new is the already-allocated node (usually from ft_lstnew) to append.

After the operation:
- If the list was empty (*lst == NULL), *lst now points to new.
- Otherwise, the last node's next points to new, and new->next remains NULL.

The function returns void.

No memory allocation is performed.

This function typically uses ft_lstlast (or implements the same logic) to find the last node.

#### Pseudo Code
```C
 ft_lstadd_back(lst, new):
    if new == NULL:
        return  // optional; usually no check

    if *lst == NULL:
        *lst = new
        return

    last = ft_lstlast(*lst)  // find the last node
    last->next = new
```
#### Edge Cases

- *lst == NULL (empty list): The function sets *lst = new.
- new == NULL: Behavior is undefined if dereferenced. Most evaluators expect no check — assume new is valid.
- lst == NULL: Undefined (dereferencing NULL). Assume valid pointer.
- List with one node: The original node becomes the second-to-last, new becomes last.
- List with multiple nodes: new is correctly appended at the end.

---
### ft_lstdelone
---
#### Explanation
`ft_lstdelone(lst, del)` frees the memory of a single linked list node `lst`.

It first uses the provided function del to free (or clean up) the memory pointed to by lst->content (if necessary).

Then it frees the node lst itself using free.

It does not touch lst->next — the next node remains untouched (caller is responsible for handling the rest of the list).

The function returns void.

No memory allocation is performed.

The del function is mandatory — it must be called on the content before freeing the node.

#### Pseudo Code
```C
 ft_lstdelone(lst, del):
    if lst == NULL or del == NULL:
        return  // optional; many implementations skip checks

    del(lst->content)  // free or clean the content
    free(lst)          // free the node itself
```
#### Edge Cases

- lst == NULL: Undefined behavior if dereferenced. Most evaluators expect no check — assume lst is valid.
- del == NULL: Calling it would crash. No check required — assume valid deleter function.
- lst->content == NULL: The del function must handle this safely (e.g., a simple free wrapper should check, but in libft, del is often just free or a custom function).
- lst->next is not NULL: It is not followed or freed — correct behavior.
- Content is dynamically allocated: del should free it properly.
- Content is static or stack-allocated: del should do nothing (e.g., a no-op function).

---
### ft_lstclear
---
#### Explanation
`ft_lstclear(lst, del)` deletes and frees all nodes in the linked list starting from `*lst`, including the first node and every subsequent node.

It uses the provided del function to free the content of each node.

It then frees the node itself using free.

After clearing the entire list, it sets the head pointer *lst to NULL to indicate an empty list.

The function returns void.

This function relies on ft_lstdelone (or implements similar logic iteratively).

If *lst == NULL, the function should do nothing (safe no-op).

#### Pseudo Code
```C
 ft_lstclear(lst, del):
    if lst == NULL or del == NULL:
        return  // optional; many skip checks

    current = *lst
    while current != NULL:
        next_node = current->next
        del(current->content)
        free(current)
        current = next_node

    *lst = NULL  // crucial: set the head to NULL
```
#### Edge Cases

- *lst == NULL (empty list): Function should do nothing and leave *lst as NULL.
- Single node list: Frees the node and its content, sets *lst = NULL.
- Multiple nodes: Frees all nodes and contents in order, no memory leaks.
- del == NULL: Undefined behavior (crash on call). No check required.
- lst == NULL: Undefined (dereference). Assume valid pointer.
- content == NULL in some nodes: del must handle it safely.
- Cyclic list (bug elsewhere): Would cause infinite loop — not handled here.

---
### ft_lstiter
---
#### Explanation
`ft_lstiter(lst, f)` iterates over the linked list starting from `lst` and applies the function `f` to the content of each node.

The function f takes a single argument: void * (the pointer to the node's content).

f can read or modify the content (since it receives the actual pointer stored in content).

The list structure itself (the nodes and next pointers) is not modified by ft_lstiter.

The function returns void.

No memory allocation or freeing is performed.

If lst == NULL, the function does nothing (safe no-op).

If f == NULL, behavior is undefined — assume valid function pointer.

#### Pseudo Code
```C
 ft_lstiter(lst, f):
    current = lst
    while current != NULL:
        f(current->content)  // apply f to the content
        current = current->next
```
#### Edge Cases

- lst == NULL: Loop does nothing — safe and correct.
- f == NULL: Undefined behavior (crash when called). No check required — assume valid f.
- Empty list: No calls to f.
- Single node: f called once on its content.
- Multiple nodes: f called exactly once per node, in order from head to tail.
- content == NULL in some nodes: f must handle NULL safely if needed.
- f modifies the content: Changes are reflected because content is passed directly.

---
### ft_lstmap
---
#### Explanation
`ft_lstmap(lst, f, del)` creates a new linked list by applying the function `f` to the content of each node in the original list `lst`.

For each node in lst:
- f is applied to its content, producing a new content value.
- A new node is created (using malloc) with the resulting content.
- This new node is added to the new list.

If any allocation fails (for a new node or implicitly inside f), the function must:
- Free all already-created nodes in the new list.
- Use the provided del function to free their contents.
- Return NULL.

The original list lst is not modified.

If lst == NULL, the function returns NULL (empty input → empty output).

The returned list is null-terminated (last node's next == NULL).

#### Pseudo Code
```C
 ft_lstmap(lst, f, del):
    if lst == NULL or f == NULL or del == NULL:
        return NULL  // optional strict checks; many skip them

    new_list_head = NULL
    current_new = NULL
    current_old = lst

    while current_old != NULL:
        // Apply f to content
        new_content = f(current_old->content)

        // Create new node
        new_node = ft_lstnew(new_content)
        if new_node == NULL:
            // Allocation failed → clean up new list
            if new_content != NULL:  // only if f allocated something
                del(new_content)
            ft_lstclear(&new_list_head, del)
            return NULL

        // Add to new list
        if new_list_head == NULL:
            new_list_head = new_node
        else:
            current_new->next = new_node
        current_new = new_node

        current_old = current_old->next

    return new_list_head
```
#### Edge Cases

- lst == NULL: Returns NULL (no new list).
- f == NULL or del == NULL: Undefined behavior. Most evaluators expect no checks.
- Empty list: Returns NULL.
- f returns NULL: New node still created with content = NULL (valid).
- Allocation fails on first node: Returns NULL (nothing to clear).
- Allocation fails midway: All previously created nodes and their contents must be freed using del, then return NULL.
- f allocates memory (e.g., strdup): The returned pointer is owned by the new list → del must be able to free it later.
- Single or multiple nodes: New list has same length, with transformed contents.

---
## Makefile
In the 42 curriculum, the Makefile is a crucial part of every project starting from libft. It must follow strict rules to pass evaluation (moulinette) and the Norm (no wildcards like * in dependencies, specific structure, no relinking, etc.).

Mandatory Requirements from the 42 Subject/Norm

Compile with flags: `-Wall -Wextra -Werror`

Use `cc` (or gcc — both accepted, but cc is standard on macOS/Linux at 42)

Rules: `all`, `clean`, `fclean`, `re` (and bonus if bonus part exists)

For libft: Output file must be `libft.a`

**No relinking**: Running make twice (or make bonus repeatedly) should not recompile/archive if nothing changed.

No wildcards in prerequisites (e.g., no `*.c` directly — list sources explicitly or use variables carefully).

`.PHONY` for pseudo-targets (all clean fclean re bonus).

Include the 42 header comment at the top.

#### Recommended Structure & Best Practices

Use Variables for readability and maintenance:

- NAME → library/executable name
- SRCS → list of mandatory .c files
- OBJS → ${SRCS:.c=.o}
- BONUS_SRCS, BONUS_OBJS for bonus
- CC, CFLAGS, AR (ar for libraries), RM

Handle Bonus Correctly (common pitfall):

- Create OBJS_BONUS from bonus sources.
- bonus rule depends on both mandatory + bonus objects.
- Archive with all objects in one ar call to avoid relinking.

Object Files:

- Use a pattern rule: `%.o: %.c` (allowed and efficient).
- Optionally create an `obj/` directory for cleaner builds.

Silent Output (nice to have):

- Use `@` before commands to hide output.
- Add colorful echoes or progress indicators (many advanced Makefiles do this).

No Unnecessary Recompilation:

- Headers as dependencies (e.g., in object rule or separately).

For Libraries (libft):

- Use `ar -rcs` (or `ar rcs`) to create/update the `.a` file.

![Important concepts](https://user-images.githubusercontent.com/30084738/232452938-06de4ce6-343d-44de-85d9-5f0c99ab4f27.gif)

## Important Concepts Learned from the 42 Libft Project

The libft project is one of the most foundational projects in the 42 curriculum. It forces you to reimplement core C functions from scratch, giving you a deep understanding of low-level programming.

Below are the key concepts you learn, grouped by theme, with explanations of their importance.

### 1. Memory Management in C
- **Manual allocation/deallocation**: Using `malloc`, `free`, and `calloc`. You learn to allocate exact amounts of memory and always free what you allocate.
- **Handling allocation failures**: Every `malloc` call must be checked for `NULL` in functions that return allocated memory (e.g., `ft_strdup`, `ft_substr`, `ft_strjoin`, `ft_itoa`, list functions).
- **Zero-initialized memory**: `ft_calloc` teaches the difference between `malloc + memset` and proper overflow-safe allocation.
- **Memory leaks prevention**: In functions like `ft_lstmap` and `ft_split`, partial failures require cleaning up already-allocated memory.

### 2. Pointer Manipulation and Addressing
- **Pointers to pointers**: Crucial for functions that modify the head of a list (`ft_lstadd_front`, `ft_lstadd_back`, `ft_lstclear`).
- **Passing by reference vs value**: Understanding why `char *` vs `char **` is needed to modify strings or list heads.
- **Pointer arithmetic**: Used extensively in string/memory functions (`ft_memcpy`, `ft_strchr`, traversal in lists).

### 3. String Handling in C
- **Null-terminated strings**: Every string operation must respect the `'\0'` terminator.
- **Safe vs unsafe functions**: Learning why `strncpy`/`strncat` are dangerous and why BSD's `strlcpy`/`strlcat` are safer (always null-terminate, return actual length).
- **Substring operations**: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split` teach dynamic string building and edge cases (start beyond length, empty strings, truncation).
- **String parsing**: `ft_atoi` teaches robust conversion (skip whitespace, handle signs, stop at invalid chars).

### 4. Character Classification and Transformation
- **ctype.h functions**: Implementing `ft_isalpha`, `ft_isdigit`, etc., teaches ASCII ranges and locale-independent checks.
- **Case conversion**: `ft_toupper`/`ft_tolower` show simple arithmetic on char values.

### 5. Memory vs String Functions
- **Difference between string and memory ops**: `str*` functions stop at `'\0'`, while `mem*` operate on raw bytes for fixed sizes.
- **Overlapping memory**: `ft_memmove` must handle overlap safely (unlike `memcpy`).

### 6. Linked Data Structures
- **Singly linked lists**: The bonus part introduces dynamic lists with `t_list`.
- **Node creation and linking**: `ft_lstnew`, `ft_lstadd_front/back`.
- **Traversal and size**: `ft_lstsize`, `ft_lstlast`.
- **Memory safety in lists**: `ft_lstdelone`, `ft_lstclear` teach proper cleanup using a deleter function.
- **Higher-order functions on lists**: `ft_lstiter` (imperative) and `ft_lstmap` (functional transformation with cleanup on failure).

### 7. Function Pointers
- **Using callbacks**: `del` in list cleanup functions, `f` in `ft_strmapi`, `ft_striteri`, `ft_lstiter`, `ft_lstmap`.
- **Generic programming**: Passing behavior as data allows reusable code (e.g., same `ft_lstclear` works for any content type).

### 8. Edge Cases and Robustness
- **NULL inputs**: Many functions must handle `NULL` gracefully or assume valid input (as per subject).
- **Extreme values**: `INT_MIN` in `ft_itoa` and `ft_putnbr_fd` (cannot negate safely).
- **Empty inputs**: Empty strings, zero length, lists with 0 nodes.
- **Truncation and limits**: `strlcpy`/`strlcat`, `ft_substr` with insufficient length.

### 9. Input/Output with File Descriptors
- **Low-level I/O**: Using `write` directly in `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`.
- **No buffering**: Understanding that `write` is unbuffered compared to `printf`.

### 10. Project Structure and Build Process
- **Creating a static library (.a)** with `ar`.
- **Writing a robust Makefile**: Variables, pattern rules, bonus handling, no relinking, proper cleaning.
- **Header guards and prototypes**: Correct `libft.h` with all function declarations.

### 11. Defensive Programming and Norm Compliance
- **No undefined behavior**: Avoiding crashes on edge cases.
- **42 Norm**: Max 25 lines per function, 80 columns, specific naming, no `for` loops in some cases (while preferred), etc.
- **Code readability**: Clear variable names, consistent style.

### Overall Takeaway
Libft teaches you to think like the standard library. You stop treating functions like `strlen` or `strdup` as black boxes and understand exactly how they work under the hood.

This foundation is essential for all future 42 projects (minishell, philosophers, ft_printf, etc.), where you'll constantly manipulate memory, strings, and data structures at a low level.

By the end of libft, you gain confidence in C pointers, memory management, and writing clean, efficient, and safe code — skills that are critical for systems programming.

![to remember](https://i.pinimg.com/originals/f7/81/2e/f7812e1249081221bb80abb048698308.gif)

## Things to Remember from Libft for Future 42 Projects

The libft project is foundational—everything you learn here will be reused constantly in the Common Core. Here are the most important takeaways to keep in mind for future projects:

### 1. Memory Management is Everything
- Always check the return value of `malloc`/`calloc`. If it’s `NULL`, handle it gracefully (usually return `NULL` or free partial allocations).
- Free **everything** you allocate. Memory leaks will kill you in later projects (valgrind/moulinette checks them strictly).
- When a function fails midway (e.g., `ft_split`, `ft_lstmap`), clean up everything already allocated before returning `NULL`.
- Never forget to free the content of linked lists using a proper `del` function.

### 2. Edge Cases Are Mandatory
- Always test:
  - `NULL` inputs (even if the subject says “assume valid”—moulinette often tests them).
  - Empty strings (`""`).
  - Extreme integer values (`INT_MIN`, `INT_MAX`, `0`).
  - Very long strings or huge allocations.
  - Overflows (e.g., start beyond string length in `ft_substr`).
- `INT_MIN` is special: you cannot safely do `-INT_MIN` → always handle it separately in `ft_itoa` and `ft_putnbr_fd`.

### 3. Pointers and Pointer-to-Pointers
- Use `**` when you need to modify a pointer itself (list head in `ft_lstadd_front/back`, `ft_lstclear`).
- Pass addresses correctly in `ft_striteri` (&`s[i]`) and list deleters.
- Never dereference potentially `NULL` pointers without checking (or know the subject allows assuming valid input).

### 4. Norm Compliance
- Max 25 lines per function, 5 parameters max, no `for` loops in some campuses (use `while`), no ternary in declarations, etc.
- Variable names must be clear (no `a`, `b`, `tmp` overuse).
- One declaration per line, no declaration after code.
- These habits will save you from norm errors in every future project.

### 5. Makefile Mastery
- Always include: `all`, `clean`, `fclean`, `re`, `bonus` (if applicable).
- No relinking: running `make` twice should do nothing.
- Use variables (`SRCS`, `OBJS`, `CFLAGS = -Wall -Wextra -Werror`).
- Handle bonus correctly (same library with bonus objects included).
- `.PHONY` for pseudo-targets.

### 6. Linked Lists Will Appear Everywhere
- Master the bonus functions—they are reused in almost every later project (minishell env, philosophers, cub3D textures, etc.).
- Always set `next = NULL` in new nodes.
- Use temporary pointers (`next = current->next`) when deleting nodes to avoid losing the chain.

### 7. Low-Level I/O
- `write` is your friend for output functions. Never use `printf` in libft (forbidden).
- Understand file descriptors (`0`, `1`, `2` = stdin, stdout, stderr) — critical for pipes and redirections later.

### 8. Function Pointers Are Powerful
- Get comfortable passing functions as arguments (`del`, `f` in list/string iterators/mappers).
- This pattern appears again in get_next_line (buffer management), ft_printf (format handlers), and many graphic projects.

### 9. Testing is Crucial
- Write your own `main` tests for every function.
- Use tools like:
  - Tripouille’s libft tester
  - libft-unit-test
  - War Machine
  - Your own edge-case mains
- Test with `valgrind` for leaks.

### 10. General Mindset
- Never trust standard functions blindly—now you know how they work internally.
- Write defensive code when possible, but respect the subject (sometimes no `NULL` checks are expected).
- Comment your code sparingly but clearly (Norm allows minimal comments).
- Reuse your libft in every future project—it’s allowed and encouraged.

### Final Thought
Libft teaches you to be paranoid about memory, precise with pointers, and rigorous with edge cases. These habits will carry you through the entire 42 curriculum.

Keep your libft clean, tested, and up-to-date—you’ll link it to almost every project until you write your own `malloc`.

**You’ve built your own toolbox. Use it wisely in everything that comes next!**

![ciao](https://i.gifer.com/RQsu.gif)
