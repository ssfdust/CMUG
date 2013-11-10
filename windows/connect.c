#include <stdio.h>
#include <windows.h>
#define STRLEN 20
#define PASSWD 8
#define GENLEN 70

typedef struct _user {
    char username[STRLEN];
    int school;
    char passwd[PASSWD];
    char gen[GENLEN];
} user;

int main(int argc, char *argv[])
{
    FILE * fp, * flog;
    user newuser;
    char cmd[90];
    if ((flog = fopen("log.txt", "a")) == NULL)
    {
        fprintf(stderr, "Can't open file %s", "log.txt");
        exit(1);
    }
    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(flog, "Can't open file %s", argv[1]);
        exit(1);
    }
    fread(&newuser, sizeof(user), 1, fp);
    sprintf(cmd, "rasdial \"CMCC\" %s %s", newuser.gen, newuser.passwd);
    system(cmd);
    fclose(flog);
    fclose(fp);
    return 0;
}
