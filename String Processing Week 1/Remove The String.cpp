// problem link: https://vjudge.net/problem/SPOJ-PSTRING
#include<bits/stdc++.h>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;


const int N=1e4+5, M=1e3+5;


char pat[M], str[N];
int f[M];
int mem[M][128], mem2[N][M];


int newL(int l, char ch){
    int &ret=mem[l][ch];
    if(~ret) return ret;
    while(l && ch!=pat[l]) l=f[l-1];
    return ret = l+=(ch==pat[l]);
}


int solve(int i, int l){
    if(!pat[l]) return OO;
    if(!str[i]) return 0;
    int &ret= mem2[i][l];
    if(~ret) return ret;
    return ret=min(solve(i+1, l)+1, solve(i+1, newL(l, str[i]))); 
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
    while(~scanf("%s %s", str, pat)){
        memset(mem, -1, sizeof mem);
        memset(mem2, -1, sizeof mem2);
        computeF();
        cout<<solve(0,0)<<'\n';
    }

  return 0;
}
