#include <stdio.h>
#include "gen.h"
#include <string.h>



char * encodeUsername(const char * uuid,const int school, const user newuser)
{
    static char enName[80];
    char tempName[STRLEN];
    int num, num2;
    char *options[CHOICE] = {
        "sy.edu.ha",
        "nf.edu.ha",
        "sp.edu.ha",
        "gxy.edu.ha",
        "cj.edu.ha",
        "sy.edu.ha"
    };
    strcpy(tempName, newuser.username);
    num = uuid[0] + uuid[1] + uuid[2] +  tempName[0] + tempName[1] + tempName[2];
    num2 = ((0xb1 * num) + 0x142e) % 0x2710;
    sprintf(enName, "%s%04d01%s@%s", uuid, num2, tempName, options[school - 1]);
    return enName;
}





