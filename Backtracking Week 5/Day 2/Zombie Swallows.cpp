//https://vjudge.net/contest/495975#problem/C

#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=150+5;

ll arr[N], n, a, b, cum[N];



bool solve(ll sum, int index){
  if(sum>=a && sum<=b) return 1;
  if(index>=n || sum>b || sum+cum[index]<a) return 0;
  if(solve(sum+arr[index], index+1)) return 1;
  return solve(sum, index+1);
}

int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
  int t;
  cin>>t;
  while(t--){
    cin>>a>>b>>n;
    for(int i=0; i<n; i++) cin>>arr[i];
    sort(arr, arr+n, greater<>());
    cum[n-1]=arr[n-1];
    for(int i=n-2; i>=0; i--) cum[i]=arr[i]+cum[i+1];
    if(solve(0,0))
      cout<<"Sallow swallow swallows.\n";
    else
      cout<<"Sallow swallow wallows in dust.\n";
  }

  
  return 0;
}
