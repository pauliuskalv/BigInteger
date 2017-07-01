#ifndef BIGINTEGERALGORITHMS_H_INCLUDED
#define BIGINTEGERALGORITHMS_H_INCLUDED
/**
*Calculate BigInteger BInteger to the power of BigInteger power
*
*The result is saved in BInteger
*/
void to_the_power_of ( struct BigInteger * BInteger , struct BigInteger * power ) ;
/**
*Calculate factorial of BigInteger BInteger
*
*The result is saved in BInteger
*/
void factorial ( struct BigInteger * BInteger ) ;
#endif