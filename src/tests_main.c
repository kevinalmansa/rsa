/*
** tests_main.c for RSA in /home/ksa28/Kent/RSA/src
** 
** Made by Kevin Almansa
** Login   <ksa28>
** 
** Started on  Mon Jan 18 18:50:59 2016 Kevin Almansa
** Last update Tue Jan 19 01:36:17 2016 Kevin Almansa
*/
#include <stdio.h>
#include <stdlib.h>
#include "primes.h"
#include "modulars.h"
#include "rsa.h"

//Test main for modular_exponents.c
int		main_modular_exponents(int ac, char **av, char **env)
{
  long		result_simple;
  long		result_right_to_left;
  long		result_inv;
  
  result_simple = modular_exponent_simple(atol(av[1]), atol(av[2]), atol(av[3]));
  printf("Modular_exp_simple: b = %ld, exp = %ld, mod = %ld\nc = %ld \n",
	 atol(av[1]), atol(av[2]), atol(av[3]), result_simple);

  result_right_to_left = right_to_left(atol(av[1]), atol(av[2]), atol(av[3]));
  printf("Right_To_Left: b = %ld, exp = %ld, mod = %ld\nc = %ld \n",
	 atol(av[1]), atol(av[2]), atol(av[3]), result_right_to_left);

  result_inv = modular_inverse(17, 3120);
  printf("Modular Inverse Check - e: %ld, fi: %ld, result: %ld, expected: %ld\n",
	 17, 3120, result_inv, 2753);
  if (result_simple == result_right_to_left && result_inv == 2753)
    return 1; //true
  return 0; //false
}

//Test main for primes.c
int		main_primes(int ac, char **av, char **env)
{
  //easiest to visually verify this
  sieve_of_eratosthenes(255);
  printf("Limit used: %ld, Primes Found: %ld\n", g_prime_list.limit_used, g_prime_list.length);
  for (long i = 0; i < g_prime_list.length; i++)
    printf("%ld, ", g_prime_list.primes[i]);
  printf("\n");
  for (long i = 0; i < g_prime_list.length; i++)
    {
      if (!is_prime(g_prime_list.primes[i]))
	{
	  printf("is_prime detected non prime: %ld\n", g_prime_list.primes[i]);
	  return 0;
	}
    }
  return 1;
}

int		main_rsa(int ac, char **av, char **env)
{
  t_rsa		results = rsa_keygen(61, 53);

  printf("RSA Keygen Controled Test\np: %ld, q: %ld\n", 61, 53);
  printf("N: %ld, fi: %ld, Chosen e: %ld, d: %ld\n",
	 results.n, results.fi, results.e, results.d);

  char		*msg = "message";
  long		ctxt[7];
  int		i = 0;
  while (msg[i] != '\0')
    {
      ctxt[i] = rsa_encrypt(msg[i], results.e, results.n);
      ++i;
    }

  i = 0;
  char		dec[8];
  while (i < 7)
    {
      dec[i] = (char) rsa_decrypt(ctxt[i], results.d, results.n); //never do this, i know what i am doing, this is baaaaaaadddd
      ++i;
    }
  dec[i] = '\0';

  
  printf("Msg: %s\n", msg, (char*)ctxt, dec);
  printf("Ciphertext: [ ");
  for (i = 0; i < 7; i++)
    printf("%ld ", ctxt[i]);
  printf("]\nDecrypted message: %s\n", dec);
  return 0;
}

int		main(int ac, char **av, char **env)
{
  if (ac < 4)
    {
      printf("Missing paramaters, try: 4 13 497\n");
      return 1;
    }
  printf("Tests Starting...\n\n");

  if (main_modular_exponents(ac, av, env))
    puts("Success!\n");
  else
    puts("Failed\n");

  if (main_primes(ac, av, env))
    puts("Success!\n");
  else
    puts("Failed\n");

  main_rsa(ac, av, env);
  
  printf("Done\n\n");
  return 0;
}
