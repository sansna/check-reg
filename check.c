#include "check.h"

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

char *itoa(int n)
{
    char *buf = (char *)malloc(12);
    snprintf(buf,11,"%d",n);
    return buf;
}

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

int cr_nabletoReg(char *lpstrrule)
{
    int *pn = (int *)malloc(sizeof(int));
    char *lpstrreponame = (char *)malloc(20);
    int ncount = 0;
    cr_nscanf(
            (char *)"http://www.cnblogs.com/sansna/p/5287820.html",
            (char *)"live:",
            8,
            (char *)"\"\%d\"",
            pn
            );
    strcpy(lpstrreponame,"\\\"name\\\":\\\"");
    strcpy(END_OF_LPSTR(lpstrreponame),lpstrrule);
    ncount = cr_ncountMatches(
            (char *)"https://api.github.com/users/softinstall/repos",
            lpstrreponame
            );
    if (ncount < *pn)
        return ncount;
    return 0;
}
