#include <stdio.h>
#include <string.h>


#define IS_a_TO_Z 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'i': case 'j': case 'k': \
                  case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': \
                  case 'v': case 'w': case 'x': case 'y': case 'z': case 'A': case 'B': case 'C': case 'D': case 'E': \
                  case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': \
                  case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': \
                  case 'Z'

#define IS_NUM '0': case '1': case '2': case '3': case '4': \
               case '5': case '6': case '7': case '8': case '9'


void check_current_char(char c)
{
  switch( c )
  {
    case IS_a_TO_Z:
      printf("%c is ALPHA\n", c);
      break;
    case IS_NUM:
      printf("%c is NUM\n", c);
      break;
    default:
      printf("%c is SPECIAL\n", c);
  }
}

void check_string(const char* szString)
{
  int length = strlen(szString);

  for ( int i=0; i<length; i++)
  {
    check_current_char(szString[i]);
  }
}

int main (int argc, const char* argv[])
{
  if ( 1 < argc )
  {
    check_string(argv[1]);
  }
}
