//https://vjudge.net/contest/495976#problem/F

#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=1e5+5;


vector<int> factorize(int n){
  vector<int>res;
  for(int i=2; i<=n/i; i++){
    if(n%i) continue;
    res.push_back(i);
    while(!(n%i)) n/=i;
  }
  if(n>1) res.push_back(n);
  return res;
}

int main(){
  FIO
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  int t,tc=0;
  cin>>t;
  while(t--){
    ll a,b,n;
    ll res=0;
    cin>>a>>b>>n;
    auto factors=factorize(n);
    for(int mask=1; mask < (1<<factors.size()); mask++){
      int product=1;
      bool even=1;
      for(int i=0; i<factors.size(); i++){
        if((mask>>i) & 1){
          product*=factors[i];
          even^=1;
        } 
      }
      ll x=(a+product-1)/product;
      ll y=b/product;
      ll num=y-x+1;
      res+=((even) ? -num : num);
    }
    cout<<"Case #"<<++tc<<": "<<b-a+1-res<<'\n';
  }


  return 0;
}
