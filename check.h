#ifndef _CHECK_H
#define _CHECK_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)
#ifndef _WIN32
#define _WIN32
#endif

#define END_OF_LPSTR(EXPR) \
    (EXPR + strlen(EXPR))
#ifdef _WIN32
#define snprintf _snprintf
#endif

int cr_nscanf(char *lpstrurl,char *lpstrfind, int nbias, char *lpstrnorm, void *p);
int cr_fcountLines(char *lpstrfileName);
int cr_ncountMatches(char *lpstrurl, char *lpstrrule);
char *cr_itoa(int n);
int cr_ncreatRecord(char *lpstrurl,char *lpstrauth,char *lpstrpattern, int nprev);
int cr_nabletoReg( char *lpstrscanhtml, char *lpstrpattern, int nbias, char *lpstrgethtml, char *lpstrmatchpattern);

#endif
