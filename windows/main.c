#include <stdio.h>
#include <stdlib.h>
#include "uuidgen.h"
#include "gen.h"
#define PASSWD 8

int main()
{
    char *uid;
    char * s;
    uuid_t temp;
    user newuser = {"", "", 0, ""};
    FILE * fdata, * fo;
    size_t _size = sizeof(user);
    char *menu[CHOICE] = {
                    "1. ��ʦ��ͨѧԺ",
                    "2. �����Ϸ�ѧԺ",
                    "3. ʳƷѧԺ",
                    "4. ������ѧ��У��",
                    "5. �ƾ�ѧԺ",
                    "6 .��ʦ��ӪУ��"
    };
    int ct;

    if ((fdata = fopen("user.dat", "rb")) == NULL)
    {

        puts("�������û�����");
        gets(newuser.username);
        puts("���������룺");
        gets(newuser.passwd);
        puts("ѡ��У��(1-6)");
        for (ct = 0;ct < CHOICE;ct++)
            puts(menu[ct]);
        scanf("%d", &newuser.school);
    }
    else
    {
        fread(&newuser, _size, 1, fdata);
        fclose(fdata);
    }

    fclose(fdata);
    if ((fdata = fopen("user.dat", "wb")) == NULL)
    {
        fprintf(stderr, "write error");
        exit (2);
    }
    if ((fo = fopen("encode.txt","w")) == NULL)
    {
        fprintf (stderr, "���ܽ���encode.txt������Ƿ����㹻��Ȩ��");
        exit (2);
    }
    /*
     * generate a uuid
     * convert uuid to string
     */
    uuid_create(&temp);
    uid = uuid_to_string(&temp);
    s = encodeUsername(uid, newuser.school, newuser);
    strncpy(newuser.gen, s, GENLEN - 2);
    newuser.gen[GENLEN - 1] = '\0';

    if (fwrite(&newuser, _size, 1, fdata) != 1)
    {
        fprintf(stderr, "write error.\n");
        exit (2);
    }

    fprintf(fo, "�û���:%s\n����:%s", s, newuser.passwd);
    fclose(fdata);
    fclose(fo);

    return 0;
}
