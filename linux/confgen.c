#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "confgen.h"

/* global config struct */
config_t * config;
/* load the config file, first ./pppoe,
 * then /usr/share/CMUG/pppoe 
 * read the file line by line
 * and change the User and password variable
 * file --> pppoe
 * */

FILE * read_config(char * file)
{
	FILE * fp = NULL;
	char * absolute_path = NULL;

	absolute_path = (char *)malloc ((strlen(getcwd(NULL, 0))
			 	+ strlen(p)) * sizeof(char));
	sprintf(absolute_path, "%s/%s", getcwd(NULL, 0), file);
	if ((fp = fopen(absolute_path, "r")) == NULL)
	{
		fprintf(stderr, "can't open the config file %s", absolute_path);
		if ((fp = fopen(SYSCONFIG, "r")) == NULL)
		{
			fprintf(stderr, "can't open file %s", SYSCONFIG);
			free(absolute_path);
			exit (0);
		}
	}
	free(absolute_path);
	return fp;
}

int ch_settings(char * username, char * passwd, 
								char * interface, FILE * fp)
{
	char * p;
	return 0;
}


int main(int argc, char *argv[])
{
	int opt;
	char * optstring = "u:p:i:h";
	int option_index;
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
			/* unknown option, getopt printed an error */
			return 1;
		}
	}
}

int parse_opt(int opt)
{
	switch(opt)
	{
		case 'U':config->
