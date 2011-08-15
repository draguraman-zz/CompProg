#include<stdio.h>
#include<string.h>
#include<math.h>
typedef  long double dbl;
dbl cf[20];
dbl cfp[20];
int t;


inline dbl fp(dbl x){
    int  i,j;
    dbl sum  = 0;
    dbl m = 1.0/(1+x);
    for (i=1;i <=t;i++){
        m *= m;
        sum -= cfp[i] * m;
    }return sum;
}

inline dbl f(dbl x){
    int i,j;
    dbl sum = cf[0];
    dbl m = 1.0/(1+x);
    for (i=1;i<= t ;i++){
        sum += cf[i] *m;
        m*=m;
    }return sum;
}

dbl doit(dbl init){

 int i,j;
  dbl x = init;
  int iter = 0;
  while (9){
      dbl y = f(x);
    dbl newx = x -  y/fp(x);
    if (iter ++ > 1000) return -1000;
    if (fabs(newx - x)<0.0000001  ) break;
    x = newx;
  }
  if (fabs(f(x) )> 0.001 || x <= -1) return -100;
  return x;
}

int main(){
    while (9){
        scanf("%d", &t);if (t==0)break;
        int i,j;
        for (i=0;i<=t;i++){
            scanf("%llf", & cf[i]);
            cfp[i] = cf[i] * (i);
        }
        dbl prevx = -1;
        dbl prevy = f(-1);
        dbl y,x;
        for ( x= -0.99; ; x += 0.01){
             y = f(x);
            if ( prevy > 0 && y <= 0){
                break;
            }
            prevx = x;
            prevy = y;
        }

        dbl low = prevx;
        dbl upp = x;
        while (1){
            if (low < -1) low = -1;
            dbl min =fabs(low+1)<0.00001 ? 99999 : fabs( f(low));
            dbl oldmin = min;
            dbl r = (upp-low)/1000;
            dbl cur = low;
            while (cur < upp+2*r){
                cur += r;
                dbl y = f(cur);
                if (fabs(y) < min){ min=fabs(y);low = cur-r; upp=cur+r; }

            }
            if (fabs(low-upp) < 0.00000000001 && 
                    (min) < 0.00000000001) break;
        }

        //if (fabs(low) < 0.005) low=0;
        if (low > -1)printf("%.2llf\n", (low));
        else printf("No\n");
        
        /*continue;
        dbl sec =-100;
dbl first = -100;
        for (dbl p = -0.999;p<10 ; p += 0.1){
            sec=doit(p);
            if (sec>-1) break;
        }
        //printf("%lf \n ",sec);

        if (first <= -1 && sec <= -1) printf("No\n");
        else if (first > -1 && sec <= -1) printf("%.2lf\n", first);
        else if (sec >-1 && first <= -1) printf("%.2lf\n",sec);
       else if (fabs(first-sec) >0.00001) printf("Too many\n");
        else printf("%.2lf\n",first);*/
    }
}
