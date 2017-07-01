#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
/**
*Calculates BInteger to the power of BigInteger power
*This function can only calculate positive powers, since were
*	working with integers
*
*The result is saved in BInteger
*/
void to_the_power_of ( struct BigInteger * BInteger , struct BigInteger * power )
{
	/**
	*index - used as an index in the multiplication step
	*temp_mul - used as the multiplicative element, which has a
	*	value of BInteger
	*two - defines a BigInteger of value 2
	*one - defines a BigInteger of value 1
	*zero - defines a BigInteger of value 0
	*compare - saves the result of the cmp function
	*/
	struct BigInteger * index = NULL ;
	struct BigInteger * temp_mul = NULL ;
	struct BigInteger * two = NULL ;
	struct BigInteger * one = NULL ;
	struct BigInteger * zero = NULL ;
	byte compare ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || power == NULL ) return ;

	/**
	*Powers can only be positive
	*Check if that's the case
	*
	*Create the zero BigInteger
	*/
	zero = create ( "0" ) ;
	compare = cmp ( power , one ) ;

	if ( compare == 2 ) return ;

	/**
	*If power is of value 0, then the result
	*	is a BigInteger of value 1 with any
	*	BigInteger
	*
	*Create the one BigInteger
	*/
	one = create ( "1" ) ;
	if ( compare == 3 )
	{
		delete_list ( BInteger ) ;
		copy_list ( BInteger , one ) ;
		delete ( one ) ;
		delete ( zero ) ;
		return ;
	}

	/**
	*BInteger can be negative
	*If power is even, then the result will be positive
	*Otherwise, the result is negative
	*/
	if ( BInteger -> sign == true )
	{
		/**
		*Create the two BigInteger
		*/
		two = create ( "2" ) ;
		temp_mul = copy ( power ) ;
		remainder ( temp_mul , two ) ;
		compare = cmp ( temp_mul , zero ) ;
		/**
		*The power is even, so the result will be positive
		*/
		if ( compare == 3 )
		{
			delete ( two ) ;
			delete ( one ) ;
			delete ( zero ) ;
			delete ( temp_mul ) ;
			BInteger -> sign = false ;
			to_the_power_of ( BInteger , power ) ;
			return ;
		}
		else
		{
			/**
			*The power is odd, so the result will stay negative
			*/
			delete ( two ) ;
			delete ( one ) ;
			delete ( zero ) ;
			delete ( temp_mul ) ;
			BInteger -> sign = false ;
			to_the_power_of ( BInteger , power ) ;
			BInteger -> sign = true ;
			return ;
		}
	}

	/**
	*Set the pointers for the multiplication step
	*
	*Delete zero
	*Delete temp_mul and reset it's value
	*/
	delete ( zero ) ;
	delete ( temp_mul ) ;
	index = copy ( power ) ;
	temp_mul = copy ( BInteger ) ;

	for ( ; ; )
	{
		if ( cmp ( index , one ) == 3 ) break ;
		multiply ( BInteger , temp_mul ) ;
		subtract ( index , one ) ;
	}

	delete ( index ) ;
	delete ( one ) ;
	delete ( temp_mul ) ;

	return ;
}
/**
*Calculate factorial of BigInteger BInteger
*
*The result is saved in BInteger
*/
void factorial ( struct BigInteger * BInteger )
{
	/**
	*temp - temporary biginteger used in the
	*	multiplication process
	*/
	struct BigInteger * temp = NULL ;
	struct BigInteger * zero = NULL ;
	struct BigInteger * one = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL ) return ;

	/**
	*Negative integer factorials require floating point
	*	numbers, so we can't calculate them ( Although it depends 
	*	on what interpretation is used )
	*/
	if ( BInteger -> sign == true ) return ;

	/**
	*If BInteger is zero, then the factorial is equal to
	*	1:
	*		0! = 1
	*
	*Create the zero and one BigIntegers
	*/
	zero = create ( "0" ) ;
	one = create ( "1" ) ;

	if ( cmp ( BInteger , zero ) == 3 )
	{
		delete ( zero ) ;
		delete_list ( BInteger ) ;
		copy_list ( BInteger , one ) ;
		delete ( one ) ;
		return ;
	}

	/**
	*Begin the multiplication process
	*
	*Create the temp, one BigIntegers and delete the zero
	*	BigInteger
	*/
	delete ( zero ) ;
	one = create ( "1" ) ;
	temp = copy ( BInteger ) ;

	for ( ; ; )
	{
		if ( cmp ( BInteger , one ) == 3 ) break ;
		subtract ( BInteger , one ) ;
		multiply ( temp , BInteger ) ;
	}

	/**
	*Cleanup and set BInteger's value
	*/
	delete ( one ) ;
	delete_list ( BInteger ) ;
	copy_list ( BInteger , temp ) ;
	delete ( temp ) ;

	return ;
}