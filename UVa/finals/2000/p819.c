
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<float.h>
typedef double dbl;

#define PI ((dbl)3.141592653589793238462383)
int x[200];
int y[200];
int n;
dbl xx[200];
dbl yy[200];
int casen=1;

inline dbl abs(dbl x){return x>=0 ? x:-x;}

#define PP \
    dbl xmax = DBL_MIN;\
    dbl xmin = DBL_MAX;\
    dbl ymax = DBL_MIN;\
    dbl ymin = DBL_MAX;\
        for (i=0;i<n;i++){\
            dbl s = sin(a);\
            dbl c = cos(a);\
            dbl x2 = x[i]*c - y[i]*s;\
            dbl y2 = x[i]*s + y[i]*c; \
            if (x2 < xmin) xmin = x2;\
            else if (x2 > xmax) xmax = x2;\
            if (y2 < ymin) ymin = y2;\
            else if (y2 > ymax) ymax = y2;\
        }\
        dbl aa = (xmax - xmin)*(ymax-ymin);\
        if (aa > max) {max =aa;amax = a;}\
        else if (aa < min) {min = aa;amin=a;}

void doit(){
    dbl incre =PI / 20000.0;
    dbl a = 0;
    dbl min = DBL_MAX;
    dbl max = DBL_MIN;
    dbl amin = DBL_MAX;
    dbl amax = 0;
    while (a <= 2*PI){
        int i,j;
        a+=incre;
        PP
    }

    incre = PI/2000000.0;
    a = amin;
    dbl prevA = -1;
    while (a >= 0){
        int i,j;
        a-=incre;
        PP
        if (prevA >= 0 && prevA < aa)break;
        prevA = aa;
    
    }
    a = amin;
     prevA = -1;
    while (a <= 2*PI){
        int i,j;
        a+=incre;
        PP
        if (prevA >= 0 && prevA < aa)break;
        prevA = aa;
    }

    a=amax;
     prevA = -1;
    while (a >=0){
        int i,j;
        a-=incre;
        PP
        if (prevA >= 0 && prevA > aa)break;
        prevA = aa;
    }
    a=amax;
     prevA = -1;
    while (a <= 2*PI){
        int i,j;
        a+=incre;
        PP
        if (prevA >= 0 && prevA > aa)break;
        prevA = aa;
    }

    printf("Gift %d:\n",casen);
    printf("Minimum area = %.3lf\n", min);
    printf("Maximum area = %.3lf\n\n", max);
    casen++;
}

int main()
{
    while(1){
        scanf("%d",&n);
        if (n==0) break;
        int i,j,k;
        scanf("%d%d",&x[0], &y[0]);
        for (i=1;i<n;i++){
            scanf("%d%d",&x[i],&y[i]);
            x[i]-=x[0]; y[i]-=y[0];
        }
        x[0]=y[0]=0;
        doit();
    }
}

