#ifndef _VERIFY_ROUTINE_H
#define _VERIFY_ROUTINE_H

#include "check.h"
#include "nreg.h"
#ifndef _WIN32
#define _WIN32
#endif

int vr_main( char *lpstrscanhtml, char *lpstrpattern, int nbias, char *lpstrgethtml, char *lpstrcreatapihtml, char *lpstrauth, char *lpstrrule);

#endif
