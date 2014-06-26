#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int N,K;
int p[101];
int w[202];
int cleft[101];
int cright[101];

int main(){
    int cases; cin>>cases;
    while(cases--){
        cin>>N>>K;
        memset(p,1,sizeof p);
        memset(cleft,0,sizeof cleft);
        memset(cright,0, sizeof cright);
        int i,j,numInequal=0;
        for (i=0;i<K;i++){
            int n;
            cin>>n;
            for (j=0;j<n*2;j++){
                cin>>w[j];
            }
            char ch;cin>>ch;
            if (ch=='=')
                for(j=0;j<2*n;j++)p[w[j]]=0;
            else {
                numInequal++;
                int*l = (ch == '<'?cleft:cright);
                int*r = (ch == '<'?cright:cleft);
                for(j=0;j<n;j++){
                    l[w[j]]++;
                    r[w[j+n]]++;
                }
            }
        }
        int found=0;
        int idx=0;
        for(i=1;i<=N;i++){
            if((cleft[i]==numInequal || cright[i]==numInequal) && p[i]){found++;idx=i;}
        }
        if(found==1)cout<<idx;
        else cout<<0;
        cout<<endl;
        if(cases)cout<<endl;
    }
}
