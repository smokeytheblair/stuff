#include <stdlib.h> // atoi
#include <string.h> // strlen
#include <stdbool.h> // bool
#include <iostream>

void print_usage(const char *szAppName)
{
  std::cout << "Usage: " << szAppName << " <credit card number to test>" << std::endl;
  std::cout << "\tWill test the submitted number to see if it is a valid CC number." << std::endl;
}


bool checkLuhn(const char *pNumber)
{
  int nSum       = 0;
  int nDigits    = strlen(pNumber);
  int nParity    = (nDigits-1) % 2;
  char cDigit[2] = "\0";
  for (int i = nDigits; i > 0 ; i--)
  {
    cDigit[0]  = pNumber[i-1];
    int nDigit = atoi(cDigit);

    if (nParity == i % 2)
      nDigit = nDigit * 2;

    nSum += nDigit/10;
    nSum += nDigit%10;
  }
  return 0 == nSum % 10;
}


int main(int argc, char* argv[])
{
  if (1 < argc)
  {
    if (true == checkLuhn(argv[1]))
    {
      std::cout << " this is a valid CC number." << std::endl;
    }
    else
    {
      std::cout << "this is NOT a valid CC number." << std::endl;
    }

  }
  else
  {
    print_usage(argv[0]);
  }

  return 0;
}
