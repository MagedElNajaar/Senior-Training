//https://vjudge.net/contest/488773#problem/A
#include<bits/stdc++.h>
#include<ext/numeric>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;


const int N=1e7+5, M=1e3+5;

char str[N];
int Z[N];

void computeZ(){
    int s=0,e=0;
    int &i=Z[0];
    for(i=1; str[i]; i++){
        if(i>=e) {
            s=e=i;
            Z[i]=0;
        }
        else Z[i]=Z[i-s];
        if(i+Z[i]==e){
            s=i;
            while(str[e]==str[e-s]) e++;
            Z[i]=e-s;
        }
    }
}



int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
   int n;
   while(~scanf("%d", &n)){
       scanf("%s %s", str, str+n+1);
       str[n]=-1;
       computeZ();
       for(int i=n+1; str[i]; i++)
           if(Z[i]==n) cout<<i-n-1<<'\n';
   }

  return 0;
}
