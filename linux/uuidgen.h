#ifndef UUIDGEN_H_INCLUDED
#define UUIDGEN_H_INCLUDED
/*
   2007-09-15 Last created by cheungmine.
   Partly rights reserved by cheungmine.
*/
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <memory.h>

#include "cdatatype.h"

typedef struct _timestamp_t
{
    BYTE    tm_sec;                /* Seconds after minute (0 每 59). */
    BYTE    tm_min;                /* Minutes after hour (0 每 59). */
    BYTE    tm_hour;            /* Hours after midnight (0 每 23). */
    BYTE    tm_mday;            /* Day of month (1 每 31). */
    BYTE    tm_mon;                /* Month (0 每 11; January = 0). */
    BYTE    tm_wday;            /* Day of week (0 每 6; Sunday = 0). */
    short    tm_year;            /* Year (current year minus 1900). */
    short    tm_yday;            /* Day of year (0 每 365; January 1 = 0). */
    long    tm_fraction;        /* Fraction little than 1 second */
} timestamp_t;

typedef struct _uuid_t
{
    unsigned long    data1;
    unsigned short    data2;
    unsigned short    data3;
    unsigned char    data4[8];
} uuid_t;


/**
 * Checks whether the given string matches the UUID format.
 *    params:
 *     [in] uuid - the potential UUID string
 *    return
 *     TRUE if the given string is a UUID, FALSE otherwise
 **/
BOOL is_uuid_string(const char *uuid);

/**
 * Generates a new UUID. The UUID is a time-based time 1 UUID.
 * A random per-process node identifier is used to avoid keeping global
 * state and maintaining inter-process synchronization.
 **/
void uuid_create(uuid_t* uuid);



/**
 * Translate a uuid_t to a uuid string
 *  return UUID string
 **/
char *uuid_to_string(const uuid_t* uuid);


#endif // UUIDGEN_H_INCLUDED
