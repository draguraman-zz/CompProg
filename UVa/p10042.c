#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#define FIND 70000

char notprime[FIND];
int primes[FIND];
int nprimes;
int cp[FIND];

typedef long long ll;

int calc(ll n) // calc sum of digits
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
        cp[i] = calc(i);
        primes[nprimes++]=i;
        
        for (j=i*2; j < sizeof(notprime);j+=i){
            notprime[j]=1;
            int j2=j;
            while (j2 % i==0){ j2/=i; cp[j] += cp[i];}
        }
    }
}

int calcprime(ll n, int depth)
{
    int i;
   ll n2= n;
   int sum=0;


   for (i=0;i<nprimes;i++){ int pp =primes[i];
       if (n2 < FIND) {sum += cp[n2];n2=1; break;}
        if (n2 %  pp) continue;
        int cnt = 0;
        while (n2%pp==0){ cnt++; n2/=pp; }
        sum += cp[pp] *cnt; 
   }

    if (n2 == n ) return depth ?  calc(n2) : 0;
    if (n2 != 1) return sum+calcprime(n2, depth+1);
    return sum;
}

int is(ll n){
    
    if (n < sizeof(notprime)&&!notprime[n])return 0;
   
    return calcprime(n,0)  == calc(n);
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
