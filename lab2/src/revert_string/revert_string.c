#include "revert_string.h"

void RevertString(char *str)
{
	int len, i;
    char *beg, *end, temp;

    i = 0; 
    while( *(str+i) != '\0' )
       i++;
    len = i;

    beg = str;
    end = str + len - 1;

    for ( i = 0 ; i < len/2 ; i++ )
    {
       temp = *end;
       *end = *beg;
       *beg = temp;

       beg++;
       end--;
    }
}

