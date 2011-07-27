
#include<stdio.h>
#include<iostream>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)
int  in[1024],n,m;
bool f(int  S){
    int  C=0;
    int  s=0;
    FOR(i,n){
        if(s+in[i]>S )s=in[i],C++;
        else s+=in[i];
    }
    C++;
    if(C<=m)return true;
    else return false;
}
int main(){
    //freopen("in.txt","r",stdin);
    while(scanf("%d%d",&n,&m)>0 ){
        FOR(i,n)scanf("%d",&in[i] );
        int Sum=0;
        FOR(i,n)Sum+=in[i];
        int  l=2147483647,r=Sum+1;
        FOR(i,n)l=min(l,in[i] );
        while(l<r){
            int  mid=(r+l)/2;
            if( f(mid)==true )r=mid;
            else l=mid+1;
        }
        printf("%d\n",l);
    }
    return 0;
}
