/*
** modulars.c for RSA in /home/ksa28/Kent/RSA/src
** 
** Made by Kevin Almansa
** Login   <ksa28>
** 
** Started on  Mon Jan 18 18:51:21 2016 Kevin Almansa
** Last update Mon Jan 18 18:51:23 2016 Kevin Almansa
*/

/*********************************************************************************
	Modular Exponentiation and Modular Inverse used for RSA
	Note that although this can be efficently done with more bits
	I constrained myself to sizeof(long) for simplicity

	Constraints: These functions assume positivie numbers are used
	and not negative.

	References: I used the links bellow to form an understanding about these
	topics, and to write the bellow C implementations.

	To understand more about these algorithms please consult the links bellow

https://en.wikipedia.org/wiki/Modular_exponentiation
https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/modular-inverses
**********************************************************************************/

#include "modulars.h"

/**
  Used by RSA for solving c = (x**p) mod m
  Uses the fact that: 
	c mod m = (a * b) mod m
  is equivilant to
	c mod m = [(a mod m) * (b mod m)] mod m

  Uses repeated multiplication with the modulo to obtain a result
  without having to store an abnormally large number for the modulo universe
 **/
long	modular_exponent_simple(long b, long exp, long mod)
{
  long	c = 1;

  if (mod == 1)
    return 0;
  for (long exp_prime = 1; exp_prime <= exp; exp_prime++)
    c = (c * b) % mod;
  return c;
}

/**
  Optimized version of the above using Right to Left binary method
  Careful of overflows (I do not check for them)
 **/
long	right_to_left(long b, long exp, long mod)
{
  long	ret = 1;

  if (mod == 1)
    return 0;
  b = b % mod;
  while (exp > 0)
    {
      if (exp % 2 == 1) // if odd number
	ret = (ret * b) % mod;
      exp = exp >> 1;
      b = (b * b) % mod;
    }
  return ret;
}

/**
  Khan Academy:
  A number multiplied by its inverse = 1
  In modulo arithmetic, the modular inverse exists
	A % C == A**-1
   
  Only numbers coprime to C (share no prime factors with C)
  have a modular inverse (mod C)

  Can be optimized by using the Euclidean Algorithm
 **/
long	modular_inverse(long a, long c)
{
  a %= c;
  for (long i = 1; i < c; i++)
    {
      if ((a * i) % c == 1)
	return i;
    }
  return 0;
}
