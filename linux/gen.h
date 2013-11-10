#ifndef GEN_H_INCLUDED
#define GEN_H_INCLUDED
#define STRLEN 45
#define PASSWD 8
#define CHOICE 6
typedef struct _user {
    char username[STRLEN];
    int school;
    char passwd[PASSWD];
} user;

/*
 * Collect user information
 * Username
 * Passwd
 * and school
 */

char * encodeUsername(const char *, int, const user);

/*
 * Format uuid drop '-'
 * to pure string with only numbers and characters
 */
#endif // GEN_H_INCLUDED
