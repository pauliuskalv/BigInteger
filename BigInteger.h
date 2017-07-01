#ifndef BIGINTEGER_H_INCLUDED
#define BIGINTEGER_H_INCLUDED
#define byte char
struct BigInteger ;
struct BigIntegerNode ;
typedef struct BigInteger * BigInteger ;
/**
*Add two BigIntegers together
*
*The result is saved in BInteger
*/
void add ( struct BigInteger * BInteger , struct BigInteger * to_add ) ;
/**
*Subtract to_sub from BInteger
*
*The result is saved in BInteger
*/
void subtract ( struct BigInteger * BInteger , struct BigInteger * to_sub ) ;
/**
*Print out the BigInteger
*/
void println ( struct BigInteger * BInteger ) ;
/**
*Get the number of digits in a BigInteger as an unsigned long integer
*/
size_t length ( struct BigInteger * BInteger ) ;
/**
*Create a BigInteger from a string:
*
*Return NULL if error
*Return BigInteger pointer if successful
*/
struct BigInteger * create ( char * str ) ;
/**
*Compare two BigIntegers:
*
*Return 0 if error
*Return 1 if BInteger_1 is bigger
*Return 2 if BInteger_2 is bigger
*Return 3 if equal
*/
byte cmp ( struct BigInteger * BInteger_1 , struct BigInteger * BInteger_2 ) ;
/**
*Create a copy from an already existing BigInteger
*
*Return NULL if error
*Return BigInteger pointer if successful
*/
struct BigInteger * copy ( struct BigInteger * to_copy ) ;
/**
*Delete an existing BigInteger
*/
void delete ( struct BigInteger * to_delete ) ;
/**
*Multiply two BigIntegers together
*
*The result is saved in BInteger
*/
void multiply ( struct BigInteger * BInteger , struct BigInteger * to_mul ) ;
/**
*Divide BInteger by to_div
*
*The result is saved in BInteger
*/
void divide ( struct BigInteger * BInteger , struct BigInteger * to_div ) ;
/**
*Get the remainder of a division
*
*The result is saved in BInteger
*/
void remainder ( struct BigInteger * BInteger , struct BigInteger * to_div ) ;
#endif
