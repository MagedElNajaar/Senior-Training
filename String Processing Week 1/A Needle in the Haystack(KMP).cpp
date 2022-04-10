// Problem Link: https://vjudge.net/problem/SPOJ-NHAY
#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;


const int N=1e7+5;


char pat[N], str[N];
int f[N];



int newL(int l, char ch){
    while(l && ch!=pat[l]) l=f[l-1];
    return l+=(ch==pat[l]);
}


void computeF(){
    if(!pat[0]) return;
    f[0]=0;
    for(int i=1; pat[i]; i++)
        f[i]=newL(f[i-1], pat[i]);
    
}

vector<int>  match(){
    computeF();
    int l=0;
    vector<int>res;
    for(int i=0; str[i]; i++){
        l=newL(l, str[i]);
        if(!pat[l]) res.push_back(i-l+1);
    }
    return res;
}

int main(){
FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
    int n;
    while(~scanf("%d", &n)){
        scanf("%s %s", pat, str);
        auto ret=match();
        for(auto& x : ret) cout<<x<<'\n';
    }

  return 0;
}
