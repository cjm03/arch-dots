// str.h
// ███████╗████████╗██████╗ ██╗███╗   ██╗ ██████╗ 
// ██╔════╝╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝ 
// ███████╗   ██║   ██████╔╝██║██╔██╗ ██║██║  ███╗
// ╚════██║   ██║   ██╔══██╗██║██║╚██╗██║██║   ██║
// ███████║   ██║   ██║  ██║██║██║ ╚████║╚██████╔╝
// ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ 
//
// Headerfile for str.c, a custom library for simpler management, control, and customization
// of strings in C.
//
// Charlie Moye
// 11-12-2025

#ifndef STR_H
#define STR_H

#include <stddef.h>
#include "../include/mem.h"

// structure holding the string and its length minus the NULL term
typedef struct String {
    char* str;
    size_t size;
} String;


// ###
// ### ONLY STDLIB MALLOC
// ###

/**
 * My strndup, don't forget to free.
 * char * buffer: String to be copied.
 * int n: Size of the string.
 */
char* Strndup(char* buffer, size_t n);

/**
 * Return ptr to substring.
 * char * str: The source of the substring.
 * int idx1: Index of first character of the substring.
 * int idx2: Index of the last character of the substring.
 */
char* SubstringReturn(char* str, int idx1, int idx2);

/** 
 * Replace str with substring.
 * char * str: The source of the substring, and the destination once found.
 * int idx1: Index of first character of the substring.
 * int idx2: Index of the last character of the substring.
 */
void SubstringReplace(char* str, int idx1, int idx2);

/**
 * Make all chars uppercase.
 * char * str: The string to be uppercased.
 * size_t n: The amount of chars to try and uppercase.
 */
void StringUppercase(char* str, size_t n);

/**
 * Make all chars lowercase.
 * char * str: The string to be lowercased.
 * size_t n: The amount of chars to try and lowercase.
 */
void StringLowercase(char* str, size_t n);

// ###
// ### STRING STRUCT + STDLIB MALLOC
// ###

/**
 *  Allocate memory and create a new String*.
 *  char* string: The string to allocate for and store.
 *  Return: Pointer to the String structure containing the string
 */
String* CreateString(char* string);

/**
 *  Slice a string and store it as a new string.
 *  String* s: The original string structure containing the string to be sliced.
 *  size_t start_idx: The starting index to slice. (Will be included in new string)
 *  size_t end_idx: The ending index to slice. (Will be included in new string)
 *  Return: Pointer to the new String structure containing the sliced string.
 */
String* CreateSlicedString(String* s, size_t start_idx, size_t end_idx);

/**
 *  Slice a string in place.
 *  String* s: The string structure to be sliced.
 *  size_t start_idx: The starting index to slice. (Will be included in sliced string)
 *  size_t end_idx: The ending index to slice. (Will be included in sliced string)
 *  Return: no return.
 */
void SliceString(String* s, size_t start_idx, size_t end_idx);

/**
 *  Create a duplicate of a string.
 *  String* s: The string structure to be duplicated.
 *  Return: Pointer to the duplicated string structure.
 */
String* DuplicateString(String* s);

/**
 *  Get the string stored in the structure.
 *  String* s: The string structure of the desired string.
 *  Return: An allocated char pointer storing a new copy of the string. Must be freed!
 */
char* GetStringData(String* s);

/**
 *  Print the string in the struct.
 *  String* s: The structure containing the string to be printed.
 *  Return: no return val
 */
void PrintString(String* s);

/**
 *  Get the string size from the struct.
 *  String* s: The structure containing the desired string's size.
 *  Return: size_t integer representing the length of the string
 */
size_t GetStringSize(String* s);

/**
 *  Erase the contents of an allocated string.
 *  String* s: The structure containing the string to be cleared.
 *  Return: no return val.
 */
void ClearString(String* s);

/**
 *  Release a string's memory.
 *  String* s: The structure to be freed.
 *  Return: no return val.
 */
void DeleteString(String* s);


// ###
// ### STRING STRUCT + MEMORY ARENA
// ###

/**
 *
 */
String M_CreateString(M_Arena* arena, char* string);

/**
 *
 */
String M_CreateSlicedString(M_Arena* arena, String* s, size_t start_idx, size_t end_idx);

/**
 *
 */
char* M_GetStringData(M_Arena* arena, String* s);

#endif // STR_H
