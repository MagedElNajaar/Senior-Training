//https://vjudge.net/contest/495976#problem/E

#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;

const int N=1e5+5;

int pos[N], cum[N], vis[N];
int vid;

int main(){
  FIO
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);

  int c,n;
  while(cin>>c>>n, n||c){
    bool found=0;
    vid++;
    pos[0]=0;
    vis[0]=vid;
    for(int i=1; i<=n; i++){
      int x;
      cin>>x;
      cum[i]=(x+cum[i-1])%c;
      if(vis[cum[i]]==vid && !found){
        for(int j=pos[cum[i]]+1; j<=i; j++) cout<<j<<" \n"[j==i];
        found=1;
      }
      pos[cum[i]]=i;
      vis[cum[i]]=vid;
    }
  }

  return 0;
}
