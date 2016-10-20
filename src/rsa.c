/*
** rsa.c for RSA in /home/ksa28/Kent/RSA/src
** 
** Made by Kevin Almansa
** Login   <ksa28>
** 
** Started on  Mon Jan 18 18:51:07 2016 Kevin Almansa
** Last update Tue Jan 19 01:31:30 2016 Kevin Almansa
*/

/******************************************************************************
	RSA Algorithm
	Reminder: ((m**e)**d) % n = m
	e: encryption, d: decryption
	Encryption: ciphertext = message**e	% n
	Decryption: (c**d == (m**e)**d == m )	% n

	RSA Key Generation
	p and q, two distrinct prime numbers
	n = pq
	fi is Euler's Totient Function
	fi(n) = fi(p) * fi(q) = (p - 1) * (q - 1) = n - (p + q - 1)

	chose e, the public key:
		- 1 < e < fi(n)
		- gcd(e, fi(n)) == 1 (i.e. e and fi(n) are coprime
	chose d, the private key:
		- d == e**-1 (mod fi(n))
		-> d is the modular multiplicative inverse of e (modulo(fi(n)))
*******************************************************************************/

#include "modulars.h"
#include "primes.h"
#include "rsa.h"

static long	pick_e(long fi)
{
  //Ensure a list of pirmes has been generated
  //if length is 0, user didn't pass paramaters, use defined limit
  if (g_prime_list.length == 0)
    sieve_of_eratosthenes(RSA_SIEVE_LIMIT);

  for (long i = 0; i < g_prime_list.length; i++)
    {
      //This will simply pick the first, not a great idea,
      //but simple to understand algo
      if (g_prime_list.primes[i] % fi != 0 && gcd(g_prime_list.primes[i], fi) == 1)
	return g_prime_list.primes[i];
    }

  //Value must be greater than 1, so this is sufficent to indicate failure
  return 0;
}

long		rsa_encrypt(long msg, long e, long n)
{
  return right_to_left(msg, e, n);
}

long		rsa_decrypt(long cyphertext, long d, long n)
{
  return right_to_left(cyphertext, d, n);
}

t_rsa		rsa_keygen(long p, long q)
{
  t_rsa		ret = { 0 };

  //Ensure that n >= 2**b where b is the number of bits per block
  //Example if encrypting a char, 2**8 = 256, thus n >= 256
  ret.n = p * q;
  ret.fi = (p - 1) * (q - 1);
  ret.e = pick_e(ret.fi);
  ret.d = modular_inverse(ret.e, ret.fi);
  return ret;
}
