#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define SYSCONFIG "/usr/share/CMUG/pppoe"
#define SYNUSR ""

typedef struct config_new {
	char username[80];
	char password[15];
	char interface[15];
} config_t;


FILE * read_config(char *);
int str_sub(char * str, const char * from, const char * to);
char * get_curpath(void);
int ch_settings(char * username, char * passwd, 
								char * interface, FILE * fp, FILE * fout);
