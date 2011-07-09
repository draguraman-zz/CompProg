/*
ID:tbhtan31
LANG:C
TASK:concom
*/

// THIS IS INCOMPLETE YET

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int percent[101][101];
int version[101];

void update(int a, int b,int c, int v)
{

    int i,j;
    int *arrB = &percent[b][0];
    int *arrA = &percent[a][0];
    
    int old = arrA[b];
    arrA[b] += c;

    if (old <= 50 && arrA[b]>50)
    {
        for (i=1;i<=100;i++)
        {
            if (i != a && arrB[i])
                update(a,i,arrB[i],v);
        }
    }
    
    version[a] = 1;
    for (i = 1; i <= 100;i++)
    {
        if (i!=a && percent[i][a] > 50 && !version[i]){
            version[i] = 1;
            update(i,b,c,v);
            version[i] = 0;
        }
    }
    version[a] = 0;
}

int main()
{
    FILE *in = fopen("concom.in", "r");
    FILE*out = fopen("concom.out", "w");
    
    int n = 0;
    int p = fscanf (in, "%d", &n);
        int i,j;
        
    for (i=0;i<n;i++)
        {int a,b,c;
            p=fscanf(in, "%d%d%d", &a, &b,&c);
            update(a,b,c,i);
        }
   
    for (i=1; i <= 100;i++)
    {
        for (j = 1; j <= 100;j++)
        {
            if (i!=j&&percent[i][j] > 50) fprintf(out,"%d %d\n",i,j);
        }
    }
    
    return 0;
}
