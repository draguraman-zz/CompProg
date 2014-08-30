#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

typedef unordered_map<int,int> intmap;
typedef pair<int,pair<int, int> > triplet;
typedef unordered_set<triplet> tripletset;

namespace std{
    template<>
    struct hash<triplet>{
        inline size_t operator()(const triplet&p)const{
            return p.first^p.second.first^p.second.second;
        };
    };
};

class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        intmap imap;
        tripletset tset;
        vector<vector<int> > ans;
        int i,j,k;
        const int n=num.size();
        for(i=0;i<n;i++){
            pair<intmap::iterator,bool> p=imap.emplace(make_pair(num[i],1));
            if(!p.second)
                ((p.first)->second)++;
        }
        vector<int> v;
        for(i=0;i<n;i++){
            int a=num[i];
            for(j=i+1;j<n;j++){
                int b=num[j],c=-a-b;
                intmap::iterator it=imap.find(c);
                if(it==imap.end())continue;
                int f=(a==c)+(b==c);
                if(it->second<=f)continue;
                v.clear();
                v.push_back(a); v.push_back(b); v.push_back(c);
                sort(v.begin(),v.end());
                triplet t = make_pair(v[0],make_pair(v[1],v[2]));
                pair<tripletset::iterator,bool> ret2=tset.insert(t);
                if(ret2.second){
                    ans.push_back(v);
                }
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    vector<int> num={-1,0,1,2,-1,-4};
    int i,j,k;
    vector<vector<int> > ans=s.threeSum(num);
    for(i=0;i<ans.size();i++){
        for(j=0;j<ans[i].size();j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
}
