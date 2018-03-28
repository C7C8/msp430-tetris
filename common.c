#include "common.h"

void swDelay(int loops)
{
    volatile unsigned int i,j;
    for (j = 0; j < loops; j++)
    {
        i = 30000 ;
        while (i > 0)
           i--;
    }
}
