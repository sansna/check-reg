#include "check.h"

//from lpstrurl find the lpstrfind line, through nbias chars find the *p through *lpstrnorm
int cr_nscanf(char *lpstrurl,char *lpstrfind, int nbias, char *lpstrnorm, void *p)
{
    char *lpstrCommand = (char *)malloc(1000);
    FILE *pFile = NULL;
    strcpy(lpstrCommand,"curl -i ");
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrurl);
#ifdef _WIN32
    strcpy(END_OF_LPSTR(lpstrCommand)," |findstr ");
#elif defined(_LINUX)
    strcpy(END_OF_LPSTR(lpstrCommand)," |grep ");
#endif
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrfind);
    strcpy(END_OF_LPSTR(lpstrCommand)," > __review");
    system(lpstrCommand);
    free(lpstrCommand);

    if ((pFile = fopen("__review","r")) == NULL)
    {
        perror("no file exist");
        exit(1);
    }
    fseek(pFile,nbias,SEEK_SET);
    fscanf(pFile,lpstrnorm,p);
    fclose(pFile);

#ifdef _WIN32
    system("del __review");
#elif defined(_LINUX)
    system("rm -f __review");
#endif
    return 0;
}

//from file lpstrfileName count the number of lines in it
int cr_fcountLines(char *lpstrfileName)
{
    FILE *pFile = NULL;
    char c = '0';
    int ncount = 0;
    if (NULL == (pFile = fopen(lpstrfileName,"r")))
    {
        perror("open file error");
        exit(0);
    }

    while (EOF != (int)(c = fgetc(pFile)))
    {
        if (c == '\r'||c == '\n')
        {
            fseek(pFile,1,SEEK_CUR);
            ncount ++;
        }
    }

    fclose(pFile);

    return ncount;
}

//from lpstrurl count matches of lpstrrule
int cr_ncountMatches(char *lpstrurl, char *lpstrrule)
{
    char *lpstrCommand = (char *)malloc(1000);
    FILE *pFile = NULL;
    int ncount = 0;
    strcpy(lpstrCommand,"curl ");
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrurl);
#ifdef _WIN32
    strcpy(END_OF_LPSTR(lpstrCommand)," |findstr ");
#elif defined(_LINUX)
    strcpy(END_OF_LPSTR(lpstrCommand)," |grep ");
#endif
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrrule);
    strcpy(END_OF_LPSTR(lpstrCommand)," > __review");

    ncount = cr_fcountLines((char *)"__review");

    fclose(pFile);
#ifdef _WIN32
    system("del __review");
#elif defined(_LINUX)
    system("rm -f __review");
#endif
    return ncount;
}

//linux ver of int to char
char *itoa(int n)
{
    char *buf = (char *)malloc(12);
    snprintf(buf,11,"%d",n);
    return buf;
}

//through api lpstrurl using lpstrauth, creating lpstrpatter+nprev repo
int cr_ncreatRecord(char *lpstrurl,char *lpstrauth,char *lpstrpattern, int nprev)
{
    char *lpstrCommand = (char *)malloc(1000);
    strcpy(lpstrCommand,"curl ");
    strcpy(END_OF_LPSTR(lpstrCommand),"-u ");
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrauth);
    strcpy(END_OF_LPSTR(lpstrCommand)," ");
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrurl);
    strcpy(END_OF_LPSTR(lpstrCommand)," -d \"{\\\"name\\\":\\\"");
    strcpy(END_OF_LPSTR(lpstrCommand),lpstrpattern);
    strcpy(END_OF_LPSTR(lpstrCommand),itoa(nprev));
    strcpy(END_OF_LPSTR(lpstrCommand),"\\\"}\"");

    return 0;
}

//from lpstrscanhtml get lpstrpattern line, moving nbias getting pn, 
//from lpstrgethtml matching lpstrmatchpattern count
//compare if still able to reg return = registed count >= 0
//else return = -1
int cr_nabletoReg(
        char *lpstrscanhtml,
        char *lpstrpattern, 
        int nbias, 
        char *lpstrgethtml, 
        char *lpstrmatchpattern
        )
{
    int *pn = (int *)malloc(sizeof(int));
    int ncount = 0;
    cr_nscanf(
            lpstrscanhtml,
            lpstrpattern,
            nbias,
            (char *)"\"\%d\"",
            pn
            );
    ncount = cr_ncountMatches(
            lpstrgethtml,
            lpstrmatchpattern
            );
    if (ncount < *pn)
        return ncount;
    return -1;
}
