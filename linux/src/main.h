#define STRLEN 45
#define PASSWD 8
#define CHOICE 6
typedef struct nuser {
    char username[STRLEN];
    int school = 0;
    char passwd[PASSWD];
} user;

int parse_opt(int, user *);
int parse_options(int argc, char * argv[], user * newuser);
void usage(void);
/*
 * Collect user information
 * Username
 * Passwd
 * and school
 */
