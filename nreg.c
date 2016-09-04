#include "nreg.h"

//create a file for each computer under %userprofile% as registration
int reg_file()
{
    int ncount = 0;
    FILE *pFile = NULL;
    char *lpstrreviewPath = (char*)malloc(100);

    system("getmac > __review");
    ncount = cr_fcountLines((char *)"__review");
    strcpy(lpstrreviewPath,getenv("USERPROFILE"));
    strcpy(END_OF_LPSTR(lpstrreviewPath),"/__review");
    if (NULL == (pFile = fopen(lpstrreviewPath,"w")))
    {
        system("getmac > __error");
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

//ret=1 ok, otherwise ret=0. compare %userprofile%/__review
int check_reg()
{
    FILE *pFile = NULL;
    int ncount = 0;
    int n = 0;
    char *lpstrreviewPath = (char*)malloc(100);

    system("getmac > __review");
    ncount = cr_fcountLines((char *)"__review");
    strcpy(lpstrreviewPath,getenv("USERPROFILE"));
    strcpy(END_OF_LPSTR(lpstrreviewPath),"/__review");
    if (NULL == (pFile = fopen(lpstrreviewPath,"r")))
        return 0;

    fscanf(pFile,"%d",&n);
    fclose(pFile);
#ifdef _WIN32
    system("del __review");
#elif defined(_LINUX)
    system("rm -f __review");
#endif

    if (n == ncount)
        return 1;

    return 0;
}

//create new repo using name lpstrrule+count
//ret = 0 means ok.
//ret = 1 means cannot reg any more
int nreg(
        char *lpstrscanhtml,
        char *lpstrpattern, 
        int nbias, 
        char *lpstrgethtml, 
        char *lpstrcreatapihtml, 
        char *lpstrauth, 
        char *lpstrrule
        )
{
    int ret = 0;
    int ret2 = 0;
    char *lpstrcompare = (char *)malloc(100);
    strcpy(lpstrcompare,"\"\\\"name\\\":\"|findstr ");
    strcpy(END_OF_LPSTR(lpstrcompare),lpstrrule);
    ret = cr_nabletoReg(
            lpstrscanhtml,
            lpstrpattern,
            nbias,
            lpstrgethtml,
            lpstrcompare
            );
    //ret = cr_nabletoReg(
    //        (char *)"http://www.
    //        (char *)"l
    //        8,
    //        (char *)"https://api.github.com/
    //        lpstrcompare
    //        );
    if (ret == -1)
        return 1;
    cr_ncreatRecord(
            lpstrcreatapihtml,
            lpstrauth,
            lpstrrule,
            ret
            );
    ret2 = cr_nabletoReg(
            lpstrscanhtml,
            lpstrpattern,
            nbias,
            lpstrgethtml,
            lpstrcompare
            );
    if (ret=ret2)
        return 1;
    //cr_ncreatRecord(
    //        (char *)"https://api.github.com/user/repos",
    //        (char *)"s
    //        lpstrrule,
    //        ret
    //        );
    return 0;
}
