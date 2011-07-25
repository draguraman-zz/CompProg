#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
char notprime[70000];
int primes[70000];
int nprimes;
int cp[70000];

typedef long long ll;

ll calc(ll n) // calc sum of digits
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
void init(){
    int i,j;
    for (i=2; i <sizeof(notprime);i++){
        if (notprime[i])continue;
        cp[nprimes] = calc(i);
        primes[nprimes++]=i;
        
        for (j=i*2; j < sizeof(notprime);j+=i){
            notprime[j]=1;

        }
    }
}


int is(ll n){
    
    if (n < sizeof(notprime)&&!notprime[n])return 0;
   int i,j;
   ll n2= n;
   ll sum=0;
   for (i=0;i<nprimes;i++){ int pp =primes[i];
        if (n2 < pp) break;
        if (n2 %  pp) continue;
        int cnt = 0;
        while (n2%pp==0){ cnt++; n2/=pp; }
        sum += cp[i] *cnt; 
   }

    if (n2 != 1) return 0;

    return sum == calc(n);
}

int main()
{
    init();
    assert(calc(0)==0);
   assert(calc(1)==1);
   assert(calc(123)==6);
    int nu;scanf("%d", &nu);
    while (nu--){
        ll n;
        scanf("%lld", &n);
        ll i;
        for (i=n+1; ;i++){
           if (is(i)) {printf("%lld\n",i);break;}
        }
    }

}
