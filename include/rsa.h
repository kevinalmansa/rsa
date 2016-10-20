/*
** rsa.h for RSA in /home/ksa28/Kent/RSA/include
** 
** Made by Kevin Almansa
** Login   <ksa28>
** 
** Started on  Mon Jan 18 18:52:01 2016 Kevin Almansa
** Last update Mon Jan 18 18:52:03 2016 Kevin Almansa
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

#ifndef __RSA__
# define __RSA__

/**
   Limit to be used for call to sieve_of_eratosthenes by pick_e if not called prior
   to rsa_keygen.

   You can safely modify this value, it MUST be positive and greater than 3
   The higher the better, but it will consume more memory.
 **/
# define	RSA_SIEVE_LIMIT 255

typedef struct	s_rsa {
  long		n;
  long		fi;
  long		e;
  long		d;
} t_rsa;

t_rsa		rsa_keygen(long p, long q);

long		rsa_encrypt(long msg, long e, long n);
long		rsa_decrypt(long cyphertext, long d, long n);

#endif
