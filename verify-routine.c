#include "verify-routine.h"

//ret = 1 means reg passed
//ret = 0 means not passed
int vr_main(
        char *lpstrscanhtml, 
        char *lpstrpattern, 
        int nbias, 
        char *lpstrgethtml, 
        char *lpstrcreatapihtml, 
        char *lpstrauth, 
        char *lpstrrule
        )
{
    if (check_reg())
        return 1;

    if(nreg(
                lpstrscanhtml,
                lpstrpattern,
                nbias,
                lpstrgethtml,
                lpstrcreatapihtml,
                lpstrauth,
                lpstrrule
           ))
        return 0;

    //if (nreg(
    //            (char*)"http://www.csdn.net/sansna/p/5287820.html",
    //            (char*)"live:",
    //            8,
    //            (char*)"https://api.github.com/users/user/repos",
    //            (char*)"https://api.github.com/user/repos",
    //            (char*)"user:passwd",
    //            (char*)"imhqt"
    //        ))
    //    return 0;

    reg_file();

    return 1;
}
