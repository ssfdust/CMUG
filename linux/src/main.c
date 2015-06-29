#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "uuidgen.h"
#include "gen.h"
#include "confgen.h"
#define STRLEN 45
#define PASSWD 8
/* global config struct */ config_t * config; 
int main(int argc, char *argv[])
{
    char *uid;
    char * s;
    uuid_t temp;
    user newuser = {"", "", 0};
    FILE * fdata, * fo;
		FILE * fp;
		FILE * fout;
    size_t _size = sizeof(user);
    char *menu[CHOICE] = {
                    "1. 淮师文通学院",
                    "2. 南林南方学院",
                    "3. 食品学院",
                    "4. 淮工大学城校区",
                    "5. 财经学院",
                    "6 .淮师王营校区"
    };
    int ct; 
		config = (config_t *)malloc(sizeof(config_t));

		parse_options(argc, argv, &newuser);
    if ((fdata = fopen(strcat(get_curpath(), "user.dat"), "rb")) == NULL)
    {
			if (strcmp(newuser.username, "") == 0)
			{
        puts("请输入用户名：");
        scanf("%s", &newuser.username);
			}
			if (strcmp(newuser.passwd, "") == 0)
			{
        puts("请输入密码：");
        scanf("%s", &newuser.passwd);
			}
			while (newuser->school > 6
					|| newuser->school < 1)
			{
        puts("选择校区(1-6)");
        for (ct = 0;ct < CHOICE;ct++)
            puts(menu[ct]);
        scanf("%d", &newuser.school);
			}
    }
    else
    {
        fread(&newuser, _size, 1, fdata);
        fclose(fdata);
    }

    if ((fdata = fopen(strcat(get_curpath(), "user.dat"), "wb")) == NULL)
    {
        fprintf(stderr, "write error");
        exit (2);
    }
    if (fwrite(&newuser, _size, 1, fdata) != 1)
    {
        fprintf(stderr, "write error.\n");
        exit (2);
    }
    if ((fo = fopen(strcat(get_curpath(), "encode.txt"),"w")) == NULL)
    {
        fprintf (stderr, "不能建立user.dat，检查是否有足够的权限");
        exit (2);
    }
    /*
     * generate a uuid
     * convert uuid to string
     */
		
    uuid_create(&temp);
    uid = uuid_to_string(&temp);
		s = encodeUsername(uid, newuser.school, newuser);
    strcpy(config->username, s);
		strcpy(config->password, newuser.passwd);

		printf("%s %s\n", config->username, config->password); 
    fprintf(fo, "User %s\nPassword %s", config->username, newuser.passwd);
		
		fp = read_config("pppoe");
		if ((fout = fopen(strcat(get_curpath(), "pppoe.conf"), "w")) == NULL)
			fprintf(stderr, "can't open the file");
		ch_settings(config->username, config->password, config->interface, fp, fout);
		fclose(fp);
		fclose(fout);
		free(config);
    fclose(fdata);
    fclose(fo);

    return 0;
}

int parse_options(int argc, char * argv[], user * newuser)
{
	int opt;
	int option_index = 0;
	char * optstring = "u:p:i:ns:h";
	static const struct option opts[] = 
	{
		{"user", required_argument, 0, 'U'},
		{"passwd", required_argument, 0, 'P'},
		{"interface", required_argument, 0, 'I'},
		{"new", no_argument, 0, 'N'},
		{"schoolnum", required_argument, 0, 'S'},
		{"help", no_argument, 0, 'H'},
		{0, 0, 0, 0}
	};
	while((opt = getopt_long(argc, argv, optstring, opts, &option_index)) != -1) {
		if(opt == 0) {
			continue;
		} else if(opt == '?') {
			usage();
			exit(2);
		}
		parse_opt(opt, newuser);
	}
	return 0;
}
int parse_opt(int opt, user * newuser)
{
	switch(opt)
	{
		case 'U':
		case 'u':strcpy(newuser->username, strdup(optarg));
						 break;
		case 'P':
		case 'p':strcpy(newuser->passwd, strdup(optarg));
						 break;
		case 'I':
		case 'i':strcpy(config->interface, strdup(optarg));
						 break;
		case 'N':
		case 'n':remove(strcat(get_curpath(), "user.dat"));
						 break;
		case 'S':
		case 's':newuser->school = aoti(optarg);
						 break;
		case 'H':
		case 'h':usage();
						 exit(2);
						 break;
	}
}


void usage(void)
{
	printf("Usage:  cmug [OPTION]...\n" );
	printf("     -u, --username[=USERNAME] %-20s\n","set your USERNAME");
	printf("     -p, --passwd[=PASSWORD] %-20s\n","set your PASSWORD");
	printf("     -i, --interface[=INTERFACE] %-20s\n","set your network INTERFACE,default eth0");
	printf("     -n, --new %-s\n","create new user");
	printf("     -h, --help %-s\n","print the help message");
}
