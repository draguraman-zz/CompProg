#include <stdio.h>
#include<stdlib.h>
#include<string.h>

// 
// this solution is currently WRONG
//
int main()
{
	while (1){
char s[100];		
int k=scanf("%s", s);
if (k!=1) break;
	int len = strlen(s);
int i;
	for 	(i=1; i < 34 ;i++){

		long long p = ((long long)1) << i; char ss[1000];
		sprintf( ss, "%lld", p);
		if (strncmp(ss, s, len)==0){
			printf ("%d\n", i);
			i = -1; break;
		}
	}

if (i>0) printf("no power of 2\n");
	 
	}
}
