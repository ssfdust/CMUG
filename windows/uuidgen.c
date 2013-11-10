/*
uuidgen.c
2007-09-15 Last created by cheungmine.
Partly rights reserved by cheungmine.
Copy and modifiy from
http://blog.csdn.net/cheungmine/article/details/1787891
by cheungmine

Modified by ssfdust
*/

#include <stdio.h>
#include <string.h>

#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "cdatatype.h"
#include "uuidgen.h"


#define UUID_LEN        36

/* microsecond per second. 1s=1000000us=1000000000ns*/
#define NSec100_Per_Sec        10000000
#define USec_Per_Sec        1000000
#define USec_Per_MSec        1000
#define NSec_Since_1582        ((uint64)(0x01B21DD213814000))


/*========================================================================================
                            Private Functions
========================================================================================*/
static BOOL isbigendian()
{
    int c = 1;
    return ( *((unsigned char *) &c) == 1 )? FALSE: TRUE;
};

static void swap_word( int size_bytes, void * ptr_word )
{
    int        i;
    unsigned char       temp;
    for( i=0; i < size_bytes/2; i++ )
    {
        temp = ((unsigned char *) ptr_word)[i];
        ((unsigned char *) ptr_word)[i] = ((unsigned char *) ptr_word)[size_bytes-i-1];
        ((unsigned char *) ptr_word)[size_bytes-i-1] = temp;
    }
};

static void write_word( unsigned char* stream, word_t val )
{
    memcpy(stream, &val, 2);
    if( isbigendian() ) swap_word( 2, stream );
};

static void write_dword( unsigned char* stream, dword_t val )
{
    memcpy(stream, &val, 4);
    if( isbigendian() ) swap_word( 4, stream );
};

static void  read_word( const unsigned char* stream, word_t* val )
{
    memcpy( val, stream, 2 );
    if( isbigendian() )    swap_word( 2, val );
};

static void  read_dword( const unsigned char* stream, dword_t* val )
{
    memcpy( val, stream, 4 );
    if( isbigendian() )    swap_word( 4, val );
};

static BOOL is_xdigit(char c)
{
    /* isxdigit returns a non-zero value if c is a hexadecimal digit (A ¨C F, a ¨C f, or 0 ¨C 9). */
    return ((c>='A'&&c<='F')||(c>='a'&&c<='f')||(c>='0'&&c<='9'))? TRUE : FALSE;
};


/* make a pseudorandom numbel based on current time*/
static int pseudo_rand()
{
#ifdef _USE_32BIT_TIME_T
    assert(0);
#endif

    struct _timeb  timebuf;

#pragma warning(push)    /* C4996 */
#pragma warning( disable : 4996 )
    _ftime64(&timebuf);
#pragma warning(pop)    /* C4996 */

    srand((uint32) ((((uint32)timebuf.time&0xFFFF)+(uint32)timebuf.millitm)^(uint32)timebuf.millitm));

    return rand();
};


/*========================================================================================
                            Public Functions
========================================================================================*/


/**
 * internal
 * ingroup uuid
 * The thread synchronization lock used to guarantee UUID uniqueness
 * for all the threads running within a process.
 */
void uuid_create(uuid_t* u)
{
    static BOOL        initialized = FALSE;
    static int64    timestamp;
    static uint32    advance;
    static uint16    clockseq;
    static uint16    node_high;
    static uint32    node_low;
    int64            time;    /* unit of 100ns */
    uint16            nowseq;
    int                r;

    #ifdef _USE_32BIT_TIME_T
        assert(0);
    #endif

    struct _timeb  tv;

    assert(u);

#pragma warning(push)    /* C4996 */
#pragma warning( disable : 4996 )
    _ftime64(&tv);
#pragma warning(pop)    /* C4996 */

    /* time is counter of 100ns time interval since Oct.15, 1582 (NOT 1852) */
    time = ((uint64) tv.time) * USec_Per_Sec + ((uint64) tv.millitm*USec_Per_MSec);
    time = time * 10 + NSec_Since_1582;

    if (!initialized)
    {
        timestamp = time;
        advance = 0;

        r = pseudo_rand();

        clockseq = r >> 16;
        node_high = r | 0x0100;

        node_low = pseudo_rand();

        initialized = TRUE;
    }
    else if (time < timestamp)
    {
        timestamp = time;
        advance = 0;
        clockseq++;
    }
    else if (time == timestamp)
    {
        advance++;
        time += advance;
    }
    else
    {
        timestamp = time;
        advance = 0;
    }
    nowseq = clockseq;

    assert(u);
    u->data1 = (dword_t) time;
    u->data2 = (word_t) ((time >> 32) & 0xffff);
    u->data3 = (word_t) (((time >> 48) & 0x0ffff) | 0x1000);
    write_word(&(u->data4[6]), (word_t) ((nowseq & 0x3fff) | 0x8000));
    write_word(&(u->data4[4]), (word_t) (node_high));
    write_dword(&(u->data4[0]), (dword_t) (node_low));
}

/**
 * internal
 * ingroup uuid
 * The thread synchronization lock used to guarantee UUID uniqueness
 * for all the threads running within a process.
 */


char *uuid_to_string(const uuid_t*  u)
{
    static char uuid_str[UUID_LEN+1];
    ushort a,b;
    uint32  c;
    read_word(&(u->data4[6]), &a);
    read_word(&(u->data4[4]), &b);
    read_dword(&(u->data4[0]), &c);

#pragma warning(push)    /* C4996 */
#pragma warning( disable : 4996 )
    sprintf(uuid_str, "%08lx%04x%04x%04x%04x%08lx",
                u->data1,
                u->data2,
                u->data3,
                a, b, c);
#pragma warning(pop)    /* C4996 */
    return uuid_str;
}









