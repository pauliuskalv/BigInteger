#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max(a, b)  (((a)>(b))?(a):(b))
#define Min(a, b)  (((a)>(b))?(b):(a))
#define bool char
#define false 0
#define true 1
#define byte char
struct BigInteger
{
	bool sign ;
	struct BigIntegerNode * head ;
	struct BigIntegerNode * tail ;
} ;
struct BigIntegerNode
{
	byte digit ;
	struct BigIntegerNode * next ;
	struct BigIntegerNode * previous ;
} ;
void add ( struct BigInteger * BInteger , struct BigInteger * to_add ) ;
void subtract ( struct BigInteger * BInteger , struct BigInteger * to_sub ) ;
/**
*Used as an internal function only!
*
*Deletes the doubly linked list of a
*	BigInteger, but leaves the BigInteger
*	itself intact and sets the head ant tail
*	pointers to NULL
*/
void delete_list ( struct BigInteger * BInteger )
{
	/**
	*temp - meant for going through the doubly
	*	linked list
	*/
	struct BigIntegerNode * temp = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL ) return ;

	temp = BInteger -> tail ;

	while ( 1 )
	{
		if ( temp == BInteger -> head ) break ;

		temp = temp -> previous ;
		free ( temp -> next ) ;
	}

	free ( temp ) ;

	BInteger -> head = NULL ;
	BInteger -> tail = NULL ;
	BInteger -> sign = false ;

	return ;
}
/**
*Used as an internal function only!
*
*Copy the doubly linked list of to_copy to BInteger
*/
void copy_list ( struct BigInteger * BInteger , struct BigInteger * to_copy )
{
	/**
	*temp, temp_copy - used for going through and creating
	*	doubly linked lists
	*/
	struct BigIntegerNode * temp = NULL ;
	struct BigIntegerNode * temp_copy = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || to_copy == NULL ) return ;

	/**
	*Start copy process
	*/
	temp_copy = to_copy -> head ;
	temp = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
	temp -> previous = NULL ;
	BInteger -> head = temp ;

	/**
	*Repeat the creation process until there are no more digits
	*	to copy from BigInteger to_copy
	*/
	for ( ; ; )
	{
		temp -> digit = temp_copy -> digit ;

		if ( temp_copy -> next == NULL )
		{
			temp -> next = NULL ;
			BInteger -> tail = temp ;
			break ;
		}
		else
		{
			temp -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
			temp -> next -> previous = temp ;
			temp = temp -> next ;
			temp_copy = temp_copy -> next ;
		}
	}

	return ;
}
/**
*Prints the BigInteger
*/
void println ( struct BigInteger * BInteger )
{
	/**
	*temp - pointer meant for going through the
	*	doubly linked list
	*/
	struct BigIntegerNode * temp = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL ) return ;

	/**
	*A BigInteger can be undefined. Check if that is the case
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL )
	{
		printf ( "Undefined\n" ) ;
		return ;
	}
	
	temp = BInteger -> tail ;

	/**
	*Print out the negative sign if necessary
	*/
	if ( BInteger -> sign == true ) printf ( "-" ) ;

	/**
	*Print out the digits, starting from the tail and ending
	*	at the head of the doubly linked list
	*/
	while ( temp != NULL )
	{
		printf ( "%d" , temp -> digit ) ;
		temp = temp -> previous ;
	}
	printf ( "\n" ) ;
}
/**
*Get the current quantity of digits in a
*	BigInteger
*
*Return - variable of size_t defining the length of
*	the BigInteger
*/
size_t length ( struct BigInteger * BInteger )
{
	/**
	*length - the length, which is to be defined
	*temp - used for going through the doubly linked list
	*/
	size_t length = 0 ;
	struct BigIntegerNode * temp = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL ) return length ;

	temp = BInteger -> head ;

	/**
	*Increment length while there are digits
	*/
	while ( temp != NULL )
	{
		length ++ ;
		temp = temp -> next ;
	}

	return length ;
}
/**
*Creates a BigInteger from a string
*
*Return - a data structure defining the BigInteger
*	from a specific string
*Return if error - a NULL pointer
*/
struct BigInteger * create ( char * str )
{
	/**
	*i - The main index used for the calculations
	*length - used to define the length of the string
	*BInteger - the main BigInteger pointer
	*temp - used for filling up the BigInteger's doubly linked list
	*/
	size_t i = 0 ;
	size_t length = 0 ;
	struct BigInteger * BInteger = NULL ;
	struct BigIntegerNode * temp = NULL ;

	/**
	*Start of preliminary checks
	*/
	if ( str == NULL ) return NULL ;

	length = strlen ( str ) ;
	if ( ! length ) return NULL ;

	/**
	*Check the string for faults
	*/
	for ( i = 0 ; i < length ; i ++ )
	{
		switch ( str [ i ] )
		{
			case '0' : continue ;
			case '1' : continue ;
			case '2' : continue ;
			case '3' : continue ;
			case '4' : continue ;
			case '5' : continue ;
			case '6' : continue ;
			case '7' : continue ;
			case '8' : continue ;
			case '9' : continue ;
			case '-' :
			{
				if ( i == 0 ) continue ;
				else
					return NULL ;
			}
			default : return NULL ;
		}
	}

	/**
	*Start the creation process
	*/
	BInteger = ( struct BigInteger * ) malloc ( sizeof ( struct BigInteger ) ) ;

	/**
	*Set the sign flag
	*/
	if ( str [ 0 ] == '-' ) BInteger -> sign = true ;
	else
		BInteger -> sign = false ;

	BInteger -> head = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
	temp = BInteger -> head ;
	temp -> previous = NULL ;

	for ( i = length - 1 ; i >= 0 ; i -- )
	{
		if ( str [ i ] == '-' ) break ;

		temp -> digit = str [ i ] - 48 ;

		/**
		*Check if it the last digit
		*If it isn't, allocate space for a new digit and continue
		*Else, stop the loop and end the creation process
		*/
		if ( i != 0 && str [ i - 1 ] != '-' )
		{
			temp -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
			temp -> next -> previous = temp ;
			temp = temp -> next ;
		}
		else
		{
			temp -> next = NULL ;
			BInteger -> tail = temp ;
			break ;
		}
	}

	return ( struct BigInteger * ) BInteger ;
}
/**
*Compare 2 different BigInteger data structures
*
*Return 0 - BInteger_1 or BInteger_2 is a NULL pointer
*Return 1 - BInteger_1 is bigger than BInteger_2
*Return 2 - BInteger_2 is bigger than BInteger_1
*Return 3 - BInteger_1 and BInteger_2 are equal
*/
byte cmp ( struct BigInteger * BInteger_1 , struct BigInteger * BInteger_2 )
{
	/*
	*temp_1, temp_2 - pointers for going through the doubly linked list
	*/
	struct BigIntegerNode * temp_1 = NULL ;
	struct BigIntegerNode * temp_2 = NULL ;

	/**
	*Preliminary checks
	*/
	if ( BInteger_1 == NULL || BInteger_2 == NULL ) return 0 ;

	/**
	*If both of the BigIntegers are negative BigIntegers, then
	*	to simplify the process, we compare them as if they're
	*	positive ones
	*If the result is 1, then return 2
	*If the result if 2, then return 1
	*If the result is 3, then return 3
	*/
	if ( BInteger_1 -> sign == true && BInteger_2 -> sign == true )
	{
		BInteger_1 -> sign = false ;
		BInteger_2 -> sign = false ;
		switch ( cmp ( BInteger_1 , BInteger_2 ) )
		{
			case 1 :
			{
				BInteger_1 -> sign = true ;
				BInteger_2 -> sign = true ;
				return 2 ;
			}
			case 2 :
			{
				BInteger_1 -> sign = true ;
				BInteger_2 -> sign = true ;
				return 1 ;
			}
			case 3 :
			{
				BInteger_1 -> sign = true ;
				BInteger_2 -> sign = true ;
				return 3 ;
			}
		}
	}

	/*
	*Every positive integer is bigger than every negative integer
	*/
	if ( BInteger_1 -> sign == false && BInteger_2 -> sign == true ) return 1 ;
	if ( BInteger_2 -> sign == false && BInteger_1 -> sign == true ) return 2 ;

	/**
	*Set the pointers
	*/
	temp_1 = BInteger_1 -> head ;
	temp_2 = BInteger_2 -> head ;

	if ( BInteger_1 -> sign == false && BInteger_2 -> sign == false )
	{
		for ( ; ; )
		{
			if ( temp_1 -> next == NULL && temp_2 -> next == NULL ) break ;
			if ( temp_1 -> next != NULL && temp_2 -> next == NULL ) return 1 ;
			if ( temp_1 -> next == NULL && temp_2 -> next != NULL ) return 2 ;

			temp_1 = temp_1 -> next ;
			temp_2 = temp_2 -> next ;
		}

		for ( ; ; )
		{
			if ( temp_1 -> digit > temp_2 -> digit ) return 1 ;
			if ( temp_1 -> digit < temp_2 -> digit ) return 2 ;
			if ( temp_1 -> previous == NULL && temp_2 -> previous == NULL ) return 3 ;

			temp_1 = temp_1 -> previous ;
			temp_2 = temp_2 -> previous ;
		}
	}

	return 0 ;
}
/**
*Create a copy from an already existing BigInteger
*
*Return NULL if error
*Return BigInteger pointer otherwise
*/
struct BigInteger * copy ( struct BigInteger * to_copy )
{
	/**
	*BInteger, temp, temp_copy - pointers, which are used in the construction
	*	of BigInteger to_copy clone
	*/
	struct BigInteger * BInteger = NULL ;
	struct BigIntegerNode * temp = NULL ;
	struct BigIntegerNode * temp_copy = NULL ;

	/**
	*Preliminary checks
	*/
	if ( to_copy == NULL ) return NULL ;

	/**
	*Check if the BigInteger is undefined
	*/
	if ( to_copy -> head == NULL && to_copy -> tail == NULL )
	{
		BInteger = ( struct BigInteger * ) malloc ( sizeof ( struct BigInteger ) ) ;
		BInteger -> head = NULL ;
		BInteger -> tail = NULL ;
		BInteger -> sign = false ;
		return ( struct BigInteger * ) BInteger ;
	}

	/**
	*Start the creation process
	*
	*Set and create pointers
	*/
	BInteger = ( struct BigInteger * ) malloc ( sizeof ( struct BigInteger ) ) ;
	BInteger -> sign = to_copy -> sign ;
	BInteger -> head = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
	temp = BInteger -> head ;
	temp -> previous = NULL ;

	temp_copy = to_copy -> head ;

	/**
	*Repeat the copy process until there are no more digits
	*	to copy in BigInteger to_copy
	*/
	for ( ; ; )
	{
		temp -> digit = temp_copy -> digit ;

		if ( temp_copy -> next == NULL )
		{
			temp -> next = NULL ;
			BInteger -> tail = temp ;
			break ;
		}
		else
		{
			temp -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
			temp -> next -> previous = temp ;
			temp = temp -> next ;
			temp_copy = temp_copy -> next ;
		}
	}

	return ( struct BigInteger * ) BInteger ;
}
/**
*Delete an already existing BigInteger
*
*Does nothing if to_delete is a NULL pointer
*/
void delete ( struct BigInteger * to_delete )
{
	/**
	*Preliminary checks
	*/
	if ( to_delete == NULL ) return ;

	/**
	*Check if it is an undefined BigInteger
	*/
	if ( to_delete -> head == NULL && to_delete -> tail == NULL )
	{
		free ( to_delete ) ;
		return ;
	}

	/**
	*Start the deletion process
	*/
	delete_list ( to_delete ) ;

	free ( to_delete ) ;

	return ;
}
/**
*Defines the addition mechanism for the BigInteger data structure
*
*The result is saved in BInteger
*/
void add ( struct BigInteger * BInteger , struct BigInteger * to_add )
{
	/**
	*temp_main, temp_add - pointers for going through the doubly
	*	linked lists
	*compare - saves the result of the cmp function
	*/
	struct BigIntegerNode * temp_main = NULL ;
	struct BigIntegerNode * temp_add = NULL ;
	byte compare ;

	/**
	*Preliminary check
	*/
	if ( BInteger == NULL || to_add == NULL ) return ;

	/**
	*Check if it's an undefined BigInteger
	*If it is, any operation with an undefined BigInteger results
	*	in an undefined BigInteger
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL ) return ;

	/**
	*Do the same for to_add
	*If it is undefined, then the result will be undefined
	*/
	if ( to_add -> head == NULL && to_add -> tail == NULL )
	{
		delete_list ( BInteger ) ;
		return ;
	}
	/**
	*If BInteger's sign is false and to_add sign is true, then
	*	the result is the same as subtraction, minus the sign
	*	flag on to_add:
	*		a + ( - b ) = a - b
	*			where:
	*				a - BInteger
	*				b - to_add
	*/
	if ( BInteger -> sign == false && to_add -> sign == true )
	{
		to_add -> sign = false ;
		subtract ( BInteger , to_add ) ;
		to_add -> sign = true ;
		return ;
	}

	/**
	*If both BigIntegers are negative BigIntegers, then the result
	*	is the same as adding the two BigIntegers together, minus
	*	the sign flags:
	*		- a + ( - b ) = - ( a + b )
	*			where:
	*				a - BInteger
	*				b - to_add
	*/
	if ( BInteger -> sign == true && to_add -> sign == true )
	{
		BInteger -> sign = false ;
		to_add -> sign = false ;
		add ( BInteger , to_add ) ;
		BInteger -> sign = true ;
		to_add -> sign = true ;
		return ;
	}

	/**
	*If BInteger is a negative BigInteger and to_add is a positive
	*	one, then there might be two different scenarios:
	*
	*		- a + b might yield a positive BigInteger. If that is the
	*			case, create a copy of b and use it in subtraction:
	*		- a + b = - ( b - a )
	*			where:
	*				a - BInteger
	*				b - to_add
	*
	*		Otherwise, a subtraction takes place, but a will remain a
	*			negative BigInteger
	*/
	if ( BInteger -> sign == true && to_add -> sign == false )
	{
		BInteger -> sign = false ;
		compare = cmp ( BInteger , to_add ) ;
		BInteger -> sign = true ;

		if ( compare == 3 )
		{
			struct BigInteger * temp = create ( "0" ) ;
			delete_list ( BInteger ) ;
			copy_list ( BInteger , temp ) ;
			BInteger -> sign = false ;
			delete ( temp ) ;
			return ;
		}

		if ( compare == 2 )
		{
			struct BigInteger * temp = copy ( to_add ) ;
			subtract ( temp , BInteger ) ;
			delete_list ( BInteger ) ;
			BInteger -> sign = false ;
			copy_list ( BInteger , temp ) ;
			delete ( temp ) ;
			return ;
		}
		else
		{
			BInteger -> sign = false ;
			subtract ( BInteger , to_add ) ;
			BInteger -> sign = true ;
			return ;
		}
	}

	/**
	*Set the pointers
	*/
	temp_main = BInteger -> head ;
	temp_add = to_add -> head ;

	for ( ; ; )
	{
		/**
		*Save the temp_main pointer in case the carry
		*	operation changes it
		*/
		struct BigIntegerNode * temp = temp_main ;

		temp_main -> digit += temp_add -> digit ;

		/**
		*Check if decimal format is held
		*	0 <= a < 10
		*	where:
		*		a - BInteger's digit
		*/
		if ( temp_main -> digit >= 10 )
		{
			temp_main -> digit -= 10 ;

			/**
			*Start the carry operation
			*/
			for ( ; ; )
			{
				/**
				*Search for a digit to add the carry to and consistently
				*	check if the decimal format is held. If it isn't, repeat
				*	the carry operation until it is
				*
				*If there are not enough digits for the carry operation,
				*	create new ones at the front and end the carry operation
				*/
				if ( temp_main -> next == NULL )
				{
					temp_main -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
					temp_main -> next -> previous = temp_main ;
					temp_main -> next -> digit = 1 ;
					temp_main = temp_main -> next ;
					temp_main -> next = NULL ;
					BInteger -> tail = temp_main ;
					break ;
				}
				else
				{
					temp_main -> next -> digit += 1 ;
					if ( temp_main -> next -> digit >= 10 )
					{
						temp_main -> next -> digit -= 10 ;
						temp_main = temp_main -> next ;
					}
					else
						break ;
				}
			}
		}

		/**
		*If BigInteger to_add is bigger than BigInteger BInteger,
		*	allocate space for a new digit at the front
		*Else, move to the next digit and continue addition
		*/
		temp_main = temp ;
		if ( temp_main -> next == NULL && temp_add -> next != NULL )
		{
			temp_main -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
			temp_main -> next -> previous = temp_main ;
			temp_main = temp_main -> next ;
			temp_main -> next = NULL ;
			temp_main -> digit = 0 ;
			BInteger -> tail = temp_main ;
		}
		else
			temp_main = temp_main -> next ;

		temp_add = temp_add -> next ;
		if ( temp_add == NULL ) break ;
	}

	return ;
}
/**
*Defines the subtraction mechanism for the BigInteger data structure
*
*The result is saved in BInteger
*/
void subtract ( struct BigInteger * BInteger , struct BigInteger * to_sub )
{
	/**
	*temp_main, temp_sub - pointers for going through the doubly
	*	linked lists
	*compare - saves the result of the cmp function
	*/
	struct BigIntegerNode * temp_main = NULL ;
	struct BigIntegerNode * temp_sub = NULL ;
	byte compare ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || to_sub == NULL ) return ;

	/**
	*Check if it's an undefined BigInteger
	*If it is, any operation with an undefined BigInteger results
	*	in an undefined BigInteger
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL ) return ;

	/**
	*Do the same for to_sub
	*If it is undefined, then the result will be undefined
	*/
	if ( to_sub -> head == NULL && to_sub -> tail == NULL )
	{
		delete_list ( BInteger ) ;
		return ;
	}

	/**
	*If BInteger is a positive BigInteger and to_sub a negative one, then
	*	an addition takes place, minus the flag sign on to_sub:
	*		a - ( - b ) = a + b
	*			where:
	*				a - BInteger
	*				b - to_sub
	*/
	if ( BInteger -> sign == false && to_sub -> sign == true )
	{
		to_sub -> sign = false ;
		add ( BInteger , to_sub ) ;
		to_sub -> sign = true ;
		return ;
	}

	/**
	*If BInteger is a negative BigInteger and to_sub is a positive
	*	one, then addition takes place:
	*		- a - b = - ( a + b )
	*			where:
	*				a - BInteger
	*				b - to_sub
	*/
	if ( BInteger -> sign == true && to_sub -> sign == false )
	{
		BInteger -> sign = false ;
		add ( BInteger , to_sub ) ;
		BInteger -> sign = true ;
		return ;
	}

	/**
	*If BInteger is a negative BigInteger and to_sub is also a
	*	negative BigInteger, then the result is addition with
	*	a negative BigInteger:
	*		- a - ( - b ) = - a + b
	*			where:
	*				a - BInteger
	*				b - to_sub
	*
	*The result can be a positive BigInteger, so we have to check
	*	in advance
	*/
	if ( BInteger -> sign == true && to_sub -> sign == true )
	{
		BInteger -> sign = false ;
		to_sub -> sign = false ;
		compare = cmp ( BInteger , to_sub ) ;
		BInteger -> sign = true ;
		to_sub -> sign = true ;

		/**
		*If the result is a positive BigInteger, then rearrange order
		*	of BigInteger as follows:
		*		- a + b = b - a
		*			where:
		*				a - BInteger
		*				b - to_sub
		*/
		if ( compare == 2 )
		{
			struct BigInteger * temp = copy ( to_sub ) ;
			temp -> sign = false ;
			BInteger -> sign = false ;
			subtract ( temp , BInteger ) ;
			delete_list ( BInteger ) ;
			copy_list ( BInteger , temp ) ;
			delete ( temp ) ;
			return ;
		}
		else
		{
			BInteger -> sign = false ;
			to_sub -> sign = false ;
			subtract ( BInteger , to_sub ) ;
			BInteger -> sign = true ;
			to_sub -> sign = true ;
			return ;
		}
	}

	/**
	*BInteger can become a negative BigInteger after subtraction,
	*	so we'll check if that is the case
	*If it is, rearrange the order of BigIntegers:
	*	a - b = - ( b - a )
	*		where:
	*			a - BInteger
	*			b - to_sub
	*/
	compare = cmp ( BInteger , to_sub ) ;
	if ( compare == 2 )
	{
		struct BigInteger * temp = copy ( to_sub ) ;
		subtract ( temp , BInteger ) ;
		delete_list ( BInteger ) ;
		BInteger -> sign = true ;
		copy_list ( BInteger , temp ) ;
		delete ( temp ) ;
		return ;
	}

	/**
	*If they are both equal, we can skip the
	*	calculations and just give it a value of 0
	*/
	if ( compare == 3 )
	{
		struct BigInteger * temp = create ( "0" ) ;
		delete_list ( BInteger ) ;
		copy_list ( BInteger , temp ) ;
		BInteger -> sign = false ;
		delete ( temp ) ;
		return ;
	}

	/**
	*Set the pointers
	*/
	temp_main = BInteger -> head ;
	temp_sub = to_sub -> head ;

	for ( ; ; )
	{
		/**
		*Save temp_main in case the reverse carry
		*	operation changes it
		*/
		struct BigIntegerNode * temp = temp_main ;

		if ( temp_sub == NULL ) break ;

		temp_main -> digit -= temp_sub -> digit ;

		/**
		*Check if the decimal format is held:
		*	0 <= a < 10
		*	where:
		*		a - BInteger's digit
		*/
		if ( temp_main -> digit < 0 )
		{
			temp_main -> digit += 10 ;

			temp_main = temp_main -> next ;

			/**
			*Repeat the reverse carry operation until
			*	it satisfies the decimal format
			*/
			for ( ; ; )
			{
				temp_main -> digit -- ;

				if ( temp_main -> digit < 0 )
				{
					temp_main -> digit += 10 ;
					temp_main = temp_main -> next ;
				}
				else
					break ;
			}
		}

		temp_main = temp ;
		temp_main = temp_main -> next ;
		temp_sub = temp_sub -> next ;
	}

	/**
	*Zeroes can appear at the front of the list
	*If that is the case, remove the aproappriate ones
	*	and fix the tail pointer as well
	*/
	temp_main = BInteger -> tail ;
	for ( ; ; )
	{
		if ( temp_main -> digit == 0 && temp_main != BInteger -> head )
		{
			temp_main = temp_main -> previous ;
			free ( temp_main -> next ) ;
			temp_main -> next = NULL ;
			BInteger -> tail = temp_main ;
		}
		else
			break ;
	}

	return ;
}
/**
*Defines the multiplication mechanism for the BigInteger
*	data structure
*
*The result is saved in BInteger
*/
void multiply ( struct BigInteger * BInteger , struct BigInteger * to_mul )
{
	/**
	*temp_mul - saves the BInteger's value for use in multiplication
	*one - defines a BigInteger of value 1
	*zero - defines a BigInteger of value 0
	*index - used as an index for the multiplication process
	*compare - saves the result of the cmp function
	*/
	struct BigInteger * temp_main = NULL ;
	struct BigIntegerNode * temp_mul = NULL ;
	struct BigInteger * mul = NULL ;
	struct BigIntegerNode * mul_temp = NULL ;
	struct BigInteger * zero = NULL ;
	byte compare ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || to_mul == NULL ) return ;

	/**
	*Check if it's an undefined BigInteger
	*If it is, any operation with an undefined BigInteger results
	*	in an undefined BigInteger
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL ) return ;

	/**
	*Do the same for to_mul
	*If it is undefined, then the result will be undefined
	*/
	if ( to_mul -> head == NULL && to_mul -> tail == NULL )
	{
		delete_list ( BInteger ) ;
		return ;
	}

	/**
	*to_mul can be a zero. If that is the case, then the multiplication
	*	will always result in a zero:
	*		a * 0 = 0
	*			where:
	*				a - BInteger
	*
	*Create the BigInteger zero
	*/
	zero = create ( "0" ) ;

	compare = cmp ( to_mul , zero ) ;
	if ( compare == 3 )
	{
		delete_list ( BInteger ) ;
		BInteger -> sign = false ;
		copy_list ( BInteger , zero ) ;
		delete ( zero ) ;
		return ;
	}

	/**
	*If BInteger is zero, then multiplication with to_mul
	*	of any value will be zero:
	*		0 * b = 0
	*			where:
	*				b - to_mul
	*/
	compare = cmp ( BInteger , zero ) ;
	if ( compare == 3 )
	{
		delete ( zero ) ;
		return ;
	}

	/**
	*If BInteger and to_mul are negative BigIntegers, then
	*	the result of the multiplication is a positive BigInteger:
	*		( - a ) * ( - b ) = a * b
	*			where:
	*				a - BInteger
	*				b - to_mul
	*/
	if ( BInteger -> sign == true && to_mul -> sign == true )
	{
		BInteger -> sign = false ;
		to_mul -> sign = false ;
		multiply ( BInteger , to_mul ) ;
		to_mul -> sign = true ;
		return ;
	}

	/**
	*If BInteger is a negative BigInteger and to_mul is a positive
	*	one, then the result of the multiplication is a negative
	*	BigInteger:
	*		( - a ) * b = - ( a * b )
	*			where:
	*				a - BInteger
	*				b - to_mul
	*/
	if ( BInteger -> sign == true && to_mul -> sign == false )
	{
		BInteger -> sign = false ;
		multiply ( BInteger , to_mul ) ;
		BInteger -> sign = true ;
		return ;
	}

	/**
	*If BInteger is a positive BigInteger and to_mul is a negative
	*	one, then the result of the multiplication is a negative
	*	BigInteger:
	*		a * ( - b ) = - ( a * b )
	*			where:
	*				a - BInteger
	*				b - to_mul
	*/
	if ( BInteger -> sign == false && to_mul -> sign == true )
	{
		to_mul -> sign = false ;
		multiply ( BInteger , to_mul ) ;
		to_mul -> sign = true ;
		BInteger -> sign = true ;
		return ;
	}

	/**
	*Start the multiplication process
	*
	*Set the pointers
	*/
	temp_mul = to_mul -> head ;
	mul = copy ( BInteger ) ;
	delete_list ( BInteger ) ;
	copy_list ( BInteger , zero ) ;
	delete ( zero ) ;
	temp_main = copy ( mul ) ;
	mul_temp = temp_main -> head ;	

	/**
	*The multiplication works essentialy the same as multiplicating
	*	numbers on paper
	*/
	for ( ; ; )
	{
		/**
		*Save the temp_main pointer in case it changes
		*/
		byte carry = 0 ;

		/**
		*Calculate the number by multiplicating using only one digit
		*	from BigInteger and add carry as necessary to adjacent digits
		*/
		for ( ; ; )
		{
			mul_temp -> digit *= temp_mul -> digit ;
			mul_temp -> digit += carry ;
			carry = 0 ;

			if ( mul_temp -> digit >= 10 )
			{
				for ( ; ; )
				{
					carry ++ ;
					mul_temp -> digit -= 10 ;
					if ( mul_temp -> digit < 10 ) break ;
				}
			}

			/**
			*Check if it's the last digit which we need to multiplicate
			*/
			if ( mul_temp -> next == NULL )
			{
				/**
				*If there is leftover carry, but there are not enough digits
				*	to add it to, create an extra digit at the front and add
				*	the carry to it
				*/
				if ( carry != 0 )
				{
					mul_temp -> next = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
					mul_temp -> next -> previous = mul_temp ;
					mul_temp -> next -> next = NULL ;
					mul_temp -> next -> digit = carry ;
					temp_main -> tail = mul_temp -> next ;
				}
				break ;
			}
			else
				mul_temp = mul_temp -> next ;
		}

		/**
		*Add the result from one-digit multiplication to a buffer
		*	BigInteger
		*/
		add ( BInteger , temp_main ) ;

		/**
		*Multiplicate the number by 10 and repeat the multiplication
		*	process as necessary
		*/
		if ( temp_mul -> next != NULL )
		{
			size_t i ;
			delete ( temp_main ) ;
			temp_main = copy ( mul ) ;

			for ( i = 0 ; i < 9 ; i ++ ) add ( mul , temp_main ) ;

			delete ( temp_main ) ;
			temp_main = copy ( mul ) ;
		}
		else
			break ;

		mul_temp = temp_main -> head ;
		temp_mul = temp_mul -> next ;
	}

	/**
	*Cleanup
	*/
	delete ( temp_main ) ;
	delete ( mul ) ;

	return ;
}
/**
*Defines the division mechanism for the
*	BigInteger data structure
*
*The result is saved in BInteger
*/
void divide ( struct BigInteger * BInteger , struct BigInteger * to_div )
{
	/**
	*result - used to save the result of the division in a BigInteger
	*	form
	*divisor - a copy of to_div used in the division process
	*one - a BigInteger of value 1
	*zero - a BigInteger of value 0
	*compare - saves the result of the cmp function
	*/
	struct BigInteger * result = NULL ;
	struct BigInteger * to_add = NULL ;
	struct BigInteger * divisor = NULL ;
	struct BigInteger * divisor_copy = NULL ;
	struct BigInteger * one = NULL ;
	struct BigInteger * zero = NULL ;
	byte compare ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || to_div == NULL ) return ;

	/**
	*Check if it's an undefined BigInteger
	*If it is, any operation with an undefined BigInteger results
	*	in an undefined BigInteger
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL ) return ;

	/**
	*Do the same for to_div
	*If it is undefined, then the result will be undefined
	*/
	if ( to_div -> head == NULL && to_div -> tail == NULL )
	{
		delete_list ( BInteger ) ;
		return ;
	}

	/**
	*Check if to_div is a zero
	*If it is zero, then the result of the
	*	division is undefined
	*
	*Create the zero pointer
	*/
	zero = create ( "0" ) ;
	compare = cmp ( to_div , zero ) ;

	if ( compare == 3 )
	{
		delete ( zero ) ;
		delete_list ( BInteger ) ;
		BInteger -> sign = false ;
		return ;
	}

	/**
	*If to_div is a negative BigInteger and BInteger is a
	*	negative BigInteger, then the result of the division
	*	is a positive one:
	*		( - a ) / ( - b ) = a / b
	*			where:
	*				a - BInteger
	*				b - to_div
	*/
	if ( BInteger -> sign == true && to_div -> sign == true )
	{
		delete ( zero ) ;
		BInteger -> sign = false ;
		to_div -> sign = false ;
		divide ( BInteger , to_div ) ;
		to_div -> sign = true ;
		return ;
	}

	/**
	*If to_div is a negative BigInteger and BInteger is a
	*	positive BigInteger, then the result of the division
	*	is a negative one:
	*		a / ( - b ) = - ( a / b )
	*			where:
	*				a - BInteger
	*				b - to_div
	*/
	if ( BInteger -> sign == false && to_div -> sign == true )
	{
		delete ( zero ) ;
		to_div -> sign = false ;
		divide ( BInteger , to_div ) ;
		BInteger -> sign = true ;
		to_div -> sign = true ;
		return ;
	}

	/**
	*If to_div is a positive BigInteger, but BInteger is a
	*	negative BigInteger, then it will remain a negative
	*	BigInteger after the division:
	*		( - a ) / b = - ( a / b )
	*			where:
	*				a - BInteger
	*				b - to_div
	*/
	if ( BInteger -> sign == true && to_div -> sign == false )
	{
		delete ( zero ) ;
		BInteger -> sign = false ;
		divide ( BInteger , to_div ) ;
		BInteger -> sign = true ;
		return ;
	}

	/**
	*to_div can be bigger than BInteger.
	*If that is the case, the result of the division
	*	is zero, because were working with integers
	*/
	compare = cmp ( BInteger , to_div ) ;
	if ( compare == 2 )
	{
		delete_list ( BInteger ) ;
		copy_list ( BInteger , zero ) ;
		delete ( zero ) ;
		return ;
	}

	/**
	*Set the pointers
	*
	*Delete zero
	*/
	delete ( one ) ;
	delete ( zero ) ;
	result = create ( "0" ) ;
	divisor_copy = copy ( to_div ) ;

	/**
	*The division algorithm works by trying to predict the best possible
	*	divisor to minimize calculation time and skip monotonous subtraction
	*
	*The division, written below, works like this:
	*
	*	1.) Check if divisor is bigger than BInteger
	*		1.a) If it's bigger and to_add is 1, stop the division and cleanup
	*		1.b) if it's bigger and to_add isn't equal to 1, break the for loop
	*			and proceed to step 2
	*		1.c) If it's equal to BInteger, add to_add to the result, stop the
	*			division and cleanup
	*	2.) Subtract divisor from BInteger while it's bigger than BInteger and add to_add
	*		to the result
	*	3.) Goto step 1
	*/
	for ( ; ; )
	{
		/**
		*Save the divisor in case it changes in the prediction step
		*
		*Set the to_add BigInteger
		*/
		divisor = copy ( divisor_copy ) ;
		to_add = create ( "1" ) ;

		for ( ; ; )
		{
			compare = cmp ( BInteger , divisor ) ;
			if ( compare == 1 )
			{
				/**
				*Multiply divisor and to_add by ten
				*
				*We can skip the multiplication process by just adding a
				*	zero at the front
				*/
				struct BigIntegerNode * temp = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
				temp -> previous = NULL ;
				temp -> next = divisor -> head ;
				temp -> digit = 0 ;
				temp -> next -> previous = temp ;
				divisor -> head = temp ;
				temp = ( struct BigIntegerNode * ) malloc ( sizeof ( struct BigIntegerNode ) ) ;
				temp -> previous = NULL ;
				temp -> next = to_add -> head ;
				temp -> digit = 0 ;
				temp -> next -> previous = temp ;
				to_add -> head = temp ;
				continue ;
			}
			if ( compare == 2 )
			{
				/**
				*If to_add if bigger than BInteger, then there are 2 scenarios:
				*	a.) If to_add is equal to one, then that means that the division is
				*		done, so we cleanup and end the division process
				*	b.) If to_add is not equal to one, then divide to_add and divisor by
				*		10 and continue to the subtraction process
				*
				*To save on calculations, we divide by 10 by simply removing the zero at the
				*	front of the list
				*/
				if ( to_add -> head == to_add -> tail )
				{
					delete ( to_add ) ;
					delete ( divisor ) ;
					to_add = NULL ;
					break ;
				}
				divisor -> head = divisor -> head -> next ;
				free ( divisor -> head -> previous ) ;
				divisor -> head -> previous = NULL ;
				to_add -> head = to_add -> head -> next ;
				free ( to_add -> head -> previous ) ;
				to_add -> head -> previous = NULL ;
				break ;
			}
			if ( compare == 3 )
			{
				/**
				*We know that they're equal, so we add to_add to the result, cleanup
				*	and end the division process
				*/
				add ( result , to_add ) ;
				delete ( divisor ) ;
				delete ( to_add ) ;
				to_add = NULL ;
				break ;
			}
		}

		if ( to_add == NULL ) break ;

		for ( ; ; )
		{
			subtract ( BInteger , divisor ) ;
			add ( result , to_add ) ;
			if ( cmp ( BInteger , divisor ) == 2 ) break ;
		}
		delete ( divisor ) ;
		delete ( to_add ) ;
	}

	delete_list ( BInteger ) ;
	copy_list ( BInteger , result ) ;
	delete ( result ) ;
	delete ( divisor_copy ) ;

	return ;
}
/**
*Calculates the remainder of the division
*
*The result is saved in BInteger
*/
void remainder ( struct BigInteger * BInteger , struct BigInteger * to_div )
{
	/**
	*temp - used to get the division result of BInteger and to_div
	*zero - a BigInteger of value zero
	*compare - saves the result of the cmp function
	*/
	struct BigInteger * temp = NULL ;
	struct BigInteger * zero = NULL ;
	byte compare ;

	/**
	*Preliminary checks
	*/
	if ( BInteger == NULL || to_div == NULL ) return ;

	/**
	*Check if it's an undefined BigInteger
	*If it is, any operation with an undefined BigInteger results
	*	in an undefined BigInteger
	*/
	if ( BInteger -> head == NULL && BInteger -> tail == NULL ) return ;

	/**
	*Do the same for to_div
	*If it is undefined, then the result will be undefined
	*/
	if ( to_div -> head == NULL && to_div -> tail == NULL )
	{
		delete_list ( BInteger ) ;
		return ;
	}

	/**
	*Check if to_div is zero
	*If it is, the remainder is undefined
	*
	*Create zero
	*/
	zero = create ( "0" ) ;
	compare = cmp ( to_div , zero ) ;

	if ( compare == 3 )
	{
		delete_list ( BInteger ) ;
		delete ( zero ) ;
		return ;
	}

	/**
	*Check if BInteger is zero
	*If it is, the remainder is zero
	*/
	compare = cmp ( BInteger , zero ) ;

	if ( compare == 3 )
	{
		/**
		*BInteger is already zero, so there's nothing
		*	to do but delete zero
		*/
		delete ( zero ) ;
		return ;
	}

	/**
	*The BigIntegers can be both negative
	*If that is the case, the remainder will be positive
	*/
	if ( BInteger -> sign == true && to_div -> sign == true )
	{
		BInteger -> sign = false ;
		to_div -> sign = false ;
		remainder ( BInteger , to_div ) ;
		to_div -> sign = true ;
		return ;
	}

	/**
	*to_div can be a negative BigInteger
	*If that is the case, the remainder will be negative
	*/
	if ( BInteger -> sign == false && to_div -> sign == true )
	{
		to_div -> sign = false ;
		remainder ( BInteger , to_div ) ;
		BInteger -> sign = true ;
		to_div -> sign = true ;
		return ;
	}

	/**
	*BInteger can be a negative BigInteger
	*If that is the case, the remainder will be negative
	*/
	if ( BInteger -> sign == true && to_div -> sign == false )
	{
		BInteger -> sign = false ;
		remainder ( BInteger , to_div ) ;
		BInteger -> sign = true ;
		return ;
	}

	/**
	*to_div can be bigger than BInteger
	*If that is the case, the remainder is BInteger
	*	itself
	*
	*Delete zero
	*/
	compare = cmp ( BInteger , to_div ) ;

	if ( compare == 2 ) return ;

	/**
	*Start the division process
	*
	*Set the pointers
	*/
	temp = copy ( BInteger ) ;
	divide ( temp , to_div ) ;
	
	for ( ; ; )
	{
		subtract ( BInteger , temp ) ;

		if ( cmp ( BInteger , temp ) == 2 ) break ;
	}

	/**
	*Cleanup
	*/
	delete ( zero ) ;
	delete ( temp ) ;

	return ;
}