#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "confgen.h"

/* load the config file, first ./pppoe,
 * then /usr/share/CMUG/pppoe 
 * read the file line by line
 * and change the User and password variable
 * file --> pppoe
 * */

FILE * read_config(char * file)
{
	FILE * fp = NULL;

	if ((fp = fopen(strcat(get_curpath(), file), "r")) == NULL)
	{
		fprintf(stderr, "can't open the config file %s", strcat(get_curpath(), file));
		if ((fp = fopen(SYSCONFIG, "r")) == NULL)
		{
			fprintf(stderr, "can't open file %s", SYSCONFIG);
			exit (0);
		}
	}
	return fp;
}

int ch_settings(char * username, char * passwd, 
								char * interface, FILE * fp, FILE * fout)
{
	char * new = NULL;
	char buffer[256];
	while (fgets(buffer, 255, fp) != NULL)
	{
		str_sub(buffer, "user", username);
		str_sub(buffer, "passwd", passwd);
		if (interface != NULL)
			str_sub(buffer, "eth0", interface);
		fputs(buffer, fout);
	}
	return 0;
}

int str_sub(char * str, const char * from, const char * to)
{
	char buffer[1024];
	char * p = strstr(str, from);
	if ( p == NULL)
		return str;
	strncpy(buffer, str, p - str);
	buffer[p-str] = '\0';
	sprintf(buffer + (p - str), "%s%s", to, p + strlen(from));
	strcpy(str, buffer);
	return 0;
}
char * get_curpath(void)
{
	char sysfile[15] = "/proc/self/exe";
	static char curfilename[256];
	int i, len;
	memset(curfilename, 0, 256);
	if (readlink(sysfile, curfilename, 256) 
			!= -1)
	{
		len = strlen(curfilename);
		for (i = len;i >= 1;i--)
			if (curfilename[i] == '/')
			{
				curfilename[i+1] = '\0';
				break;
			}
	}
	return curfilename;
}
/*
int parse_opt(int opt)
{
	switch(opt)
	{
		case 'U':
		case 'u':config->username = strdup(optarg);
						 break;
		case 'P':
		case 'p':config->password = strdup(optarg);
						 break;
		case 'I':
		case 'i':config->interface = strdup(optarg);
						 break;
	}
}
*/
/*
int main(int argc, char *argv[])
{
	int opt;
	int option_index = 0;
	char * optstring = "u:p:i:h";
	FILE * fp;
	FILE * fout;
	static const struct option opts[] = 
	{
		{"user", required_argument, 0, 'U'},
		{"passwd", required_argument, 0, 'P'},
		{"interface", required_argument, 0, 'I'},
		{"help", no_argument, 0, 'H'},
		{0, 0, 0, 0}
	};
	while((opt = getopt_long(argc, argv, optstring, opts, &option_index)) != -1) {
		if(opt == 0) {
			continue;
		} else if(opt == '?') {
			return 1;
		}
		parse_opt(opt);
	}
	
	puts(get_curpath());
	printf("User: %s\n"
				 "Password: %s\n"
				 "Interface:%s\n",
				 config->username, config->password, config->interface);
}
*/
