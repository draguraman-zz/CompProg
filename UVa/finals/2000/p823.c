/*
Simple trigo and geometry..

Argh, this doesn't work yet..

If someone can tell me what's the bug I would greatly appreciate it


*/
#include <math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//typedef long double dbl;
//#define double dbl

#define PI ((double)3.14159265358979323846264)


double big[3], sm[3]; // big & sm diameters
bool inv[3]; // whether inverted
double a,b,c; // lengths of tri
int casen = 1;

// assumes circle center at (0,0) with radiius r
// line segment is [x1,y1] - [x2,y2]
bool circleLineIntersect(
    double r, double x1, double y1, double x2, double y2
)
{
    double dx = x2-x1;
    double dy = y2-y1;
    double dr2 = (dx*dx+dy*dy);
    double D = x1*y2 - x2*y1;
    double det = r*r * dr2 - D*D;
    return det >= 0.0;
}

bool circleLineInter(
double x, double y, double r, double x1, double y1, double x2, double y2)
{
    return circleLineIntersect(
        r, x1-x, y1-y, x2-x, y2-y
    );
}

// circle 1 : radius r1 
// circle 2 : radius r2 
// distance dd squared between their centers
bool circlesIntersect(double r1, double r2, double dd)
{
    if(dd >= (r1+r2)*(r1+r2)) return false;
    return true;
}

bool cc(double*x, double*y,int i1,int i2){

    double dx = x[i1]-x[i2];
    double dy = y[i1]-y[i2];
    double dd = (dx*dx+dy*dy);

    double d1a=big[i1]/2, d2a=big[i2]/2;
    double d1b=sm[i1]/2, d2b=sm[i2]/2;
    
    if (inv[i1]){
        d1a = sm[i1]/2;
        d1b = big[i1]/2;
    }

    if (inv[i2]){
        d2a = sm[i2]/2;
        d2b = big[i2]/2;
    }

    return (circlesIntersect(d1a,d2a,dd) ||
            circlesIntersect(d1b,d2b,dd));
}

double cross(double a, double b, double c, double d)
{
    return a*d-b*c;
}

bool sameSide(
double p1x, double p1y, 
double p2x, double p2y,
double ax, double ay,
double bx,double by){

    double cp1 = cross(bx-ax, by-ay, p1x-ax,p1y-ay);    
    double cp2 = cross(bx-ax, by-ay, p2x-ax,p2y-ay);    
    if (cp1*cp2 >= 0.0) return true;
    return false;
}

bool inTri(
double x, double y,
double ax, double ay, 
double bx, double by,
double cx, double cy){
    
    if (
    sameSide(x,y,ax,ay,bx,by,cx,cy) &&
    sameSide(x,y,bx,by,ax,ay,cx,cy) &&
    sameSide(x,y,cx,cy,ax,ay,bx,by)) return true;
    return false;
}

/*
Triangle:
    /\
a  /  \ b
  /    \
 /______\
     c

Stopper 0 is at lower left, 1 at top, 2 at lower right
*/

bool test()
{
    double x[3], y[3]; // centers of circles
    y[0] = big[0]/2.0;
    double alpha = acos((a*a + c*c - b*b)/(2*a*c))/2;
    x[0] = y[0]/tan(alpha);

    double t2 = a*sin(alpha*2);
    double t1 = a*cos(alpha*2);

    // check inter with side b
    if (circleLineInter(x[0],y[0],y[0],t1,t2,
        c,0)) return false;

    double gamma = acos((a*a+b*b-c*c)/(2*a*b))/2;
    double e= PI/2 - 2*alpha - gamma;
    double h = big[1]/2 / sin(gamma);
    y[1] = a*sin(alpha*2) - h*cos(e);
    x[1] = a*cos(alpha*2) - h *sin(e);
    
    //check inter with side c
    if (circleLineInter(x[1],y[1],big[1]/2.0,0,0,
        c,0)) return false;

    if (cc(x,y,0,1)) return false;

    double beta = acos((c*c+b*b-a*a)/(2*c*b))/2;
    y[2] = big[2]/2;
    x[2] = c-y[2]/tan(beta);
    
    if (circleLineInter(x[2],y[2],big[2]/2.0,t1,t2,
        0,0)) return false;

    if (cc(x,y,1,2)) return false;
    if (cc(x,y,0,2)) return false;

    int i;
    for(i=0;i<3;i++){
        if (!inTri(x[i],y[i],
            0,0,t1,t2,c,0))return false;
    }

    return true;
}

// rotate array by one
void rot(double *a)
{
    double t = a[0];
    a[0] = a[1];
    a[1] = a[2];
    a[2] = t;
}

bool doit()
{
    int i = 0;
    for (i=0;i<4;i++){
        int j;
        for (j=0;j<=7;j++){
            inv[0] =( (j&1)!=0); 
            inv[1] = ((j&2)!=0); 
            inv[2] = ((j&4)!=0);
            bool ok = test();
            if (ok) return ok;
        }   
        
        rot(big); rot(sm);
    }
    
    return false;
}

int main()
{
    int f=0;
    while(1){
        int ia, ib, ic; 
        scanf("%d%d%d%lf%lf%lf%lf%lf%lf", &ia,&ib,&ic,
            &sm[0],&big[0],&sm[1],&big[1],&sm[2],&big[2]);
        if ((ia|ib|ic)==0) break;
        a = (double)ia; b =(double)ib;c=(double)ic;

        if (f) printf("\n\n"); f=1;
        double alpha2 = acos((a*a+c*c-b*b)/(2*a*c));
        double xx = a*cos(alpha2);
        if (xx < c/2){
            // if tri skewed left, then swap sides to make it skew right
            double t = b;
            b=a;
            a=t;
        }

        bool ok = doit();
        if (!ok){
            // swap so that we get all 3! combinations
            double t = big[0];
            big[0] = big[1];
            big[1] = t;
            t = sm[0];
            sm[0] = sm[1];
            sm[1] = t;
            ok = doit();
        }

        printf("Triangle number %d:\n", casen);casen++;
        if (ok) printf("All three stoppers will fit in the"
                    " triangular space");
        else printf("Stoppers will not fit in the triangular space");
    }
    return 0;
}

