#if !defined(BINTREEHEADER_H)
/*
  Header for file realBinTree.cpp
 */
#define BINTREEHEADER_H

#include <iostream>
#include <cassert>
#define NAME_LEN 500

int mystrlen(char* source)
{
    //return len of string
    char* p = source;
    while (*p != '\0') ++p;
    return p - source;
}

void mystrcpy(char* dest, const char* source)
{
    //copy all symbols from one string to another.
    int i = 0;
    while ((*(dest + i) = *(source + i)) != '\0') ++i;
}

int getline(char dest[])
{
    int c, i;
    for (i = 0; i < NAME_LEN - 1 && (c = getchar()) != EOF && c != '\n'; ++i)  *(dest + i) = c;
    if (c == '\n')
        *(dest + i) = '\0';
    return i;
}

int mystrcmp(const char* str_1, const char* str_2)
{
    /*compare two strings, if the same return 0,
      return value < 0 if str_1 < str_2
      return value > 0 if str_1 > str_2
     */
    int i;
    for (i = 0; *(str_1 + i) == *(str_2 + i); ++i)
        if (*(str_1 + i) == '\0')
            return 0;
    return *(str_1 + i) - *(str_2 + i);
}

//Allocator of memory.
char* alloc(char* fullN)
{
    char* tmp;
    tmp = (char*)malloc(mystrlen(fullN) + 1);
    mystrcpy(tmp, fullN);
    return tmp;
}

#endif

