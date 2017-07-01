#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "BigInteger.h"
#include "BigIntegerAlgorithms.h"

int main ( )
{
	BigInteger BInteger = create ( "100" ) ;
	/**
	*Calculates 100! as an example
	*/
	factorial ( BInteger ) ;
	println ( BInteger ) ;
	return 1 ;
}