#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long a[100002];
long long k,c;
int n;

int comp(const void *a, const void * b)
{
    long long k= *(long long*) a - *(long long*) b;
    if (k<0) return -1;
    if (k >0) return 1;
    return 0;
}

int main()
{
    int nu;
    int casen = 1;
        scanf("%d",&nu);
        while (nu--)
        {
            scanf("%lld%lld%d%lld", &k, &c, &n, &a[0]);
            k %= 1000007;
            c %= 1000007;
            
            int i;
            long long ts = a[0];
            for (i=1; i < n;i++){
                a[i] =  ((k * a[i-1] )% 1000007+ c) % 1000007;
                ts += a[i];
            }
            
                qsort( a,n,sizeof(long long), comp );
                
            long long sum = 0;
            for (i=0;i<n;i++){
                ts -= a[i];
                sum += ts - a[i]*(n-i-1);               
            }

            printf("Case %d: %lld\n", casen, sum);
            casen++;
        }

    return 0;
}


