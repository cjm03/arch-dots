// stdstr.h
//
// Headerfile for stdstr.c, which is a collection of string-related functions to be used
// with barebones C, and do not require custom structures or memory implementations. Make 
// sure to figure out what needs to be freed!!!
//
// Charlie Moye 
// 11-12-2025

#ifndef STDSTR_H
#define STDSTR_H

#include <stddef.h>

/* 
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

#endif // STDSTR_H
