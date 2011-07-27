#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef double dbl;
#include<float.h>
dbl p,q,r,s,t,u;

inline dbl eqn(dbl x)
{
    return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}
inline int sgn(dbl x){
    return x < 0 ? -1 : 1;
}
inline dbl min(dbl x, dbl y){ return x<y ? x : y; }
inline dbl max(dbl x, dbl y){ return x>y ? x : y; }
inline dbl abs(dbl x){ return x>0? x : -x; }
void doit()
{
    dbl l = 0;
    dbl r = 1;
    while (1)
    {
        l = max(0,l);
        r = min(1,r);
        dbl incre = (r-l)/200;
        dbl oldl = l;
        dbl oldr = r;
        dbl mindiff = DBL_MAX;
        dbl v = l;
        dbl oldrv = eqn(r);
        dbl stop = min(1,oldr+2*incre);
        while (v <= stop){
            v += incre;
            dbl val = eqn(v);
            dbl diff = abs(val);
            if (diff < mindiff){mindiff = diff; 
            l=v-incre;
            r=v+incre;}
        }
        if (abs(r-l) < 0.000001 && abs(eqn(r)-oldrv)<0.00001) break;
    }
    
    if (abs(eqn(r))<0.0001){
        printf("%.4lf\n", r);
        }
        else printf("No solution\n");
}

int main()
{
    while (1){
        int k =scanf("%lf %lf %lf %lf %lf %lf", &p,&q,&r,&s,&t,&u);
if (k!=6)break;
        doit();
    }
}
