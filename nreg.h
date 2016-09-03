#ifndef _NREG_H
#define _NREG_H
#include <stdlib.h>
#include <stdio.h>
#include "check.h"

#ifndef _WIN32
#define _WIN32
#endif

int reg_file();
int check_reg();
int nreg(char *lpstrscanhtml, char *lpstrpattern, int nbias, char *lpstrgethtml, char *lpstrcreatapihtml, char *lpstrauth, char *lpstrrule);

#endif
