/*
** modulars.h for RSA in /home/ksa28/Kent/RSA/include
** 
** Made by Kevin Almansa
** Login   <ksa28>
** 
** Started on  Mon Jan 18 18:52:22 2016 Kevin Almansa
** Last update Mon Jan 18 18:52:24 2016 Kevin Almansa
*/

#ifndef __MATH_MODULAR_EXPONENT__
# define __MATH_MODULAR_EXPONENT__

/**
  Used by RSA for solving c = (x**p) mod m
  Uses the fact that: 
	c mod m = (a * b) mod m
  is equivilant to
	c mod m = [(a mod m) * (b mod m)] mod m

  Uses repeated multiplication with the modulo to obtain a result
  without having to store an abnormally large number for the modulo universe
 **/
long		modular_exponent_simple(long b, long exp, long mod);

/**
  Optimized version of the above using Right to Left binary method
  Careful of overflows (I do not check for them)
 **/
long		right_to_left(long b, long exp, long mod);

/**
  Khan Academy:
  A number multiplied by its inverse = 1
  In modulo arithmetic, the modular inverse exists
	A % C == A**-1
   
  Only numbers coprime to C (share no prime factors with C)
  have a modular inverse (mod C)

  Can be optimized by using the Euclidean Algorithm
 **/
long		modular_inverse(long e, long fi_n);

#endif
