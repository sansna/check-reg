#include "nreg.h"
#include "check.h"

int reg_file()
{
    int ncount = 0;
    FILE *pFile = NULL;
    system("getmac > __review");
    ncount = cr_fcountLines((char *)"__review");
    if (NULL == (pFile = fopen("\%userprofile\%/__review","w")))
    {
        perror("error");
        exit(0);
    }
    fprintf(pFile,"%d",ncount);
    fclose(pFile);

#ifdef _WIN32
    system("del __review");
#elif defined(_LINUX)
    system("rm -f __review");
#endif
    return 0;
}

int check_reg()
{
    FILE *pFile = NULL;
    int ncount = 0;
    int n = 0;
    system("getmac > __review");
    ncount = cr_fcountLines((char *)"__review");
    if (NULL == (pFile = fopen("\%userprofile\%/__review","r")))
    {
        perror("error");
        exit(0);
    }
    fscanf(pFile,"%d",&n);
    fclose(pFile);

    if (n == ncount)
        return 1;

    return 0;
}

int nreg(char *lpstrrule)
{
    int ret = 0;
    ret = cr_nabletoReg(lpstrrule);
    if (!ret)
        exit(0);
    cr_ncreatRecord(
            (char *)"https://api.github.com/user/repos",
            (char *)"softinstall:passwd",
            lpstrrule,
            ret+1
            );
    return 0;
}
