/**
 * Long division in binary. If someone has a better method, please tell me.
 */
#include<iostream>
using namespace std;
typedef long long ll;

class Solution {
public:
    int divide(int n_, int d_) {
        ll ans=0,sign=1;
        if((n_<0&&d_>=0)||(n_>=0&&d_<0))
            sign=-1;
        ll n=abs((ll)n_);
        ll d=abs((ll)d_);
        while(n>=d){
            ll a=d;
            ll m=1;
            while((a<<1) < n){a<<=1;m<<=1;}
            ans+=m;
            n-=a;
        }
        return ans*sign;
    }
};

int main(){
    int i,j;
    Solution s;
    cout<<s.divide(2147483647,1)<<endl;
    cout<<s.divide(-1010369383, -2147483648)<<endl;
    cout<<s.divide(-2147483647, -1)<<endl;
    cout<<s.divide(-2147483648, 1)<<endl;
    for(i=-10000;i<10000;i++){
        for(j=1;j<1000;j++){
            if(s.divide(i,j)!=i/j){
                cout<<i<<","<<j<<endl;
            }
        }
    }

}
