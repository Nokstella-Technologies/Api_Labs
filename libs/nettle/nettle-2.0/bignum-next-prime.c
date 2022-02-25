/* bignum-next-prime.c
 *
 */

/* nettle, low-level cryptographics library
 *
 * Copyright (C) 2002 Niels M�ller
 *  
 * The nettle library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 * 
 * The nettle library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with the nettle library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#if HAVE_CONFIG_H
# include "config.h"
#endif

#include <limits.h>

#include "bignum.h"

#include "nettle-internal.h"

/* From gmp.h */
/* Test for gcc >= maj.min, as per __GNUC_PREREQ in glibc */
#if defined (__GNUC__) && defined (__GNUC_MINOR__)
#define GNUC_PREREQ(maj, min) \
  ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define GNUC_PREREQ(maj, min)  0
#endif

#if GNUC_PREREQ (3,0)
# define UNLIKELY(cond) __builtin_expect ((cond) != 0, 0)
#else
# define UNLIKELY(cond) cond
#endif

/* From some benchmarking using the examples nextprime(200!) and
   nextprime(240!), it seems that it pays off to use a prime list up
   to around 5000--10000 primes. There are 6541 odd primes less than
   2^16. */
static const uint16_t primes[] = {
  /* Generated by

     ./examples/eratosthenes 65535 \
     | awk '{ if (NR % 10 == 2) printf ("\n"); if (NR > 1) printf("%d, ", $1); }
            END { printf("\n"); }' > prime-list.h
  */
  #include "prime-list.h"
};

#define NUMBER_OF_PRIMES (sizeof(primes) / sizeof(primes[0]))

#ifdef mpz_millerrabin
# define PRIME_P mpz_millerrabin
#else
# define PRIME_P mpz_probab_prime_p
#endif

/* NOTE: The mpz_nextprime in current GMP is unoptimized. */
void
nettle_next_prime(mpz_t p, mpz_t n, unsigned count, unsigned prime_limit,
		  void *progress_ctx, nettle_progress_func progress)
{
  mpz_t tmp;
  TMP_DECL(moduli, unsigned, NUMBER_OF_PRIMES);
  
  unsigned difference;

  if (prime_limit > NUMBER_OF_PRIMES)
    prime_limit = NUMBER_OF_PRIMES;
  
  /* First handle tiny numbers */
  if (mpz_cmp_ui(n, 2) <= 0)
    {
      mpz_set_ui(p, 2);
      return;
    }
  mpz_set(p, n);
  mpz_setbit(p, 0);

  if (mpz_cmp_ui(p, 8) < 0)
    return;

  mpz_init(tmp);

  if (mpz_cmp_ui(p, primes[prime_limit-1]) <= 0)
    /* Use only 3, 5 and 7 */
    /* FIXME: Could do binary search in the table. */
    prime_limit = 3;
  
  /* Compute residues modulo small odd primes */
  /* FIXME: Could be sped up by collecting limb-sized products of the
     primes, to reduce the calls to mpz_fdiv_ui */

  /* FIXME: Could also handle the first few primes separately; compute
     the residue mod 15015 = 3 * 7 * 11 * 13, and tabulate the steps
     between the 5760 odd numbers in this interval that have no factor
     in common with 15015.
   */
  TMP_ALLOC(moduli, prime_limit);
  {
    unsigned i;
    for (i = 0; i < prime_limit; i++)
      moduli[i] = mpz_fdiv_ui(p, primes[i]);
  }
  
  for (difference = 0; ; difference += 2)
    {
      int composite = 0;
      unsigned i;
      
      if (difference >= UINT_MAX - 10)
	{ /* Should not happen, at least not very often... */
	  mpz_add_ui(p, p, difference);
	  difference = 0;
	}

      /* First check residues */
      for (i = 0; i < prime_limit; i++)
	{
	  if (moduli[i] == 0)
	    composite = 1;

	  moduli[i] += 2;
	  if (UNLIKELY(moduli[i] >= primes[i]))
	    moduli[i] -= primes[i];
	}
      if (composite)
	continue;
      
      mpz_add_ui(p, p, difference);
      difference = 0;

      if (progress)
	progress(progress_ctx, '.');

      /* Miller-Rabin test */
      if (PRIME_P(p, count))
	break;

#if 0
      if (progress)
	progress(progress_ctx, '*');
#endif
    }
  mpz_clear(tmp);
}