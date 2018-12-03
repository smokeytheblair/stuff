// compute prime numbers using the Sieve algorithm
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <locale.h>

void print_usage(const char* szName)
{
  printf("%s <max prime>\n This app will compute all the prime nubmers from 0 to <max prime>.\n", szName);
}

void create_number_list(long max, unsigned char ** numbers)
{
  *numbers = (unsigned char*)malloc(sizeof(unsigned char) * max/2);

  long length = (long)max/2;

  // everything is assumed prime until the algorithm determines otherwise
  memset((void*)*numbers, 0x01, sizeof(unsigned char) * max/2);
} 

void zero_multiples_of_prime(long prime_index, unsigned char* numbers, long max)
{
  //only processing for odd numbers
  long prime = (prime_index * 2) - 1;

  //printf("Removing multiples of %ld: ", prime);

  long length = (long)max/2;

  for (long i=prime_index+prime; i<length; i+=prime)
  {
    //printf("numbers[%ld] = %ld, ", i, (i*2)-1);
    numbers[i] = 0;
  }
  //printf("\n");
}

int compute_primes(long max)
{
 // printf("Computing primes from 0 to %ld\n", max);

  unsigned char * numbers = NULL;

  clock_t start = clock();
  
  create_number_list(max, &numbers);

  //loop on the primes and call zero_multipls...
  // only walk half of the array, because multiples
  // will start to be off the end of the array
  //

  long length = (long)(max/2);
  long half_length = (long)length/2;

  for(long idx = 2; idx<half_length; idx++)
  {
    if ( 0 < numbers[idx])
    {
      zero_multiples_of_prime(idx, numbers, max);
    }
  } 

  // print out/count primes
  long count_primes = 0;
  for (long i=1; i<length; i++)
  {
    if (numbers[i] > 0)
    {
      ++count_primes;
      //printf("%ld, ", (i*2)-1);
    }
  }

  clock_t finish = clock();

  printf("Found %'ld prime numbers out of %'ld\n", count_primes, max);
  printf("Compute time: %f seconds\n", ((double) finish - start)/CLOCKS_PER_SEC);

  // clean up
  if (NULL != numbers)
  {
    free(numbers);
    numbers = NULL;
  }

  return (0);
}

int main(int argc, char* argv[])
{
  if (1<argc)
  {
    setlocale(LC_NUMERIC, "");
    compute_primes(atol(argv[1]));
  }
  else
  {
    print_usage(argv[0]);
  }

  return (0);
}
