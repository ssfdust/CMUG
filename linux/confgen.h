#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define SYSCONFIG "/usr/share/CMUG/pppoe"
#define SYNUSR ""
Interface=eth0
Connection=pppoe
User='example@yourprovider.com'
Password='very secret'

FILE * read_config(char *);
struct config_new {
	char * username;
	char * password;
	char * interface;
} config_t;


