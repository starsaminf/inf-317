#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>

int main()
{

    char *str[] = {"tres", "tristes", "tigres", "trigaban", "trigo", "por", "culpa", "del", "bolivar"};
    int length = sizeof(str) / sizeof(str[0]);
    char *out1[length];
    char *out2[length];

    memset(out1, 0, sizeof(out1));
    memset(out2, 0, sizeof(out2));

    #pragma omp parallel for shared(out1, out2)
    for (int i = 0; i < length; i++)
    {
        if (i % 2 == 0)
        {
            out1[i / 2] = str[i];
        }
        else
        {
            out2[i / 2] = str[i];
        }
    }

     for (int i = 0; out1[i] != NULL; i++)
     {
         printf("%s ", out1[i]);
     }
    
     printf("\n");
    
     for (int i = 0; out2[i] != NULL; i++)
     {
         printf("%s ", out2[i]);
     }
     printf("\n");
    return 0;
}