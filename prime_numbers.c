#include <stdlib.h>
#include <stdio.h>

void print_usage(const char* szName)
{
  printf("%s <max prime>\n This app will compute all the prime nubmers from 0 to <max prime>.\n", szName);
}

void create_number_list(long max, long ** numbers)
{
  *numbers = (long*)malloc(sizeof(long) * max/2);

  for (long idx = 1; idx <= (long)(max/2); idx++)
  {
    (*numbers)[idx-1] = (idx*2) - 1;
  }

  //printf("created list of numbers: %ld \n", (long)(max/2));
  for(long idx = 0; idx < max/2; idx++)
  {
    //printf("%ld, ", (*numbers)[idx]);
  }
  //printf("\n");

} 

void zero_multiples_of_prime(long prime_index, long* numbers, long max)
{
  long prime = numbers[prime_index];

  //printf("Removing multiples of %ld: ", prime);

  for (long i=prime_index+prime; i<(long)(max/2); i+=prime)
  {
    //printf("numbers[%ld] = %ld, ", i, numbers[i]);
    numbers[i] = 0;
  }
  //printf("\n");
}

int compute_primes(long max)
{
  long * numbers = NULL;

  create_number_list(max, &numbers);

  //loop on the primes and call zero_multipls...
  //
  for(long idx = 1; idx<(long)(max/2); idx++)
  {
    if ( 0 < numbers[idx])
    {
      zero_multiples_of_prime(idx, numbers, max);
    }
  } 

  // print out/count primes
  long count_primes = 0;
  for (long i=0; i<(long)(max/2); i++)
  {
    if (numbers[i] > 0)
    {
      ++count_primes;
      //printf("%ld, ", numbers[i]);
    }
  }

  printf("\nFound %ld prime numbers out of %ld\n", count_primes, max);

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
    compute_primes(atol(argv[1]));
  }
  else
  {
    print_usage(argv[0]);
  }

  return (0);
}
