#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define END_OF_LPSTR(EXPR) \
    (EXPR + strlen(EXPR))

int cr_nscanf(char *lpstrurl,char *lpstrfind, int nbias, char *lpstrnorm, void *p);
int cr_fcountLines(char *lpstrfileName);
int cr_ncountMatches(char *lpstrurl, char *lpstrrule);
char *itoa(int n);
int cr_ncreatRecord(char *lpstrurl,char *lpstrauth,char *lpstrpattern, int nprev);
int cr_nabletoReg(char *lpstrrule);

