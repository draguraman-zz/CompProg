#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cache[2000001];
int depthc[2000001];
char notprime[2000001];
int primes[1500000];
int nprimes;

int gcd(int m, int n){

    while (1){
    if (n==0||m==0) return n+m;
      int a = m;
      m = n%m;
      n = a;
    }
}

int phi(int v){
    if (cache[v]) return cache[v];
    if (!notprime[v]) return v-1;

    int i,j;

    for(i=0;i<nprimes;i++){
        if (0== v % primes[i]) break;
    }

    int d =gcd(primes[i], v/primes[i]);
  int aa=  cache[v/primes[i]]= phi(v/primes[i]) ;
 int bb=   cache[primes[i]] = phi(primes[i]) ;
 int cc =  cache[d] = phi(d);

 return aa*bb*d/cc;

/*
    int ret= 1;
    int v2 = v;
    
    for (i=0;i< nprimes;i++){
        int p = primes[i];
        if ( v2 < p) break;
        if (v2 % p) continue;
        int c = 0;
        int add = 1;
        while (v2 %p==0){add*= p;v2/=p;c++;}
        ret *= add-add/p;
    }
    return cache[v]=ret;
    */
}

void init()
{
    cache[1]=1;
    int i,j;
    for (i=2; i < sizeof(notprime);i++){
        if (notprime[i]) continue;
        primes[nprimes++]=i;
        for (j= i*2; j< sizeof(notprime); j+=i){
            notprime[j] = 1;
        }
    }
}

int depth(int n){
    if (depthc[n])return depthc[n];
    int p = phi(n);
    int d = 1;
    while (p > 1){
        if (depthc[p])return d+ depthc[p];
        p = phi(p); d++;
    }
    return depthc[n]=d;
}

int main()
{
    init();
    int nu;scanf("%d", &nu);
    while (nu--){
        int a,b;
        scanf("%d%d",&a,&b);
long long d=0;
        int i,j;
        if (a >b){ int t = a; a = b; b = t;}
        for (i=a; i <= b;i++){
          d += depth(i);
        }
        printf("%lld\n",d);
    }
}


