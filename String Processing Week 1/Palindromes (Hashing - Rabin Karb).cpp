// problem link: https://vjudge.net/problem/SPOJ-PLD
#include<bits/stdc++.h>
#include<ext/numeric>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;


const int N=3e4+5, M=1e3+5;

struct mul{
    int mod;
    int operator() (int a, int b){
        return a*1LL*b%mod;
    }
    mul(int _mod) : mod(_mod) {};
};

struct add{
    int mod;
    int operator() (int a, int b){
        return (a+b)%mod;
    }
    add(int _mod) : mod(_mod) {};
};


struct sub{
    int mod;
    int operator() (int a, int b){
        return (a+mod-b)%mod;
    }
    sub(int _mod) : mod(_mod) {};
};


int identity_element(const mul& ){
    return 1;
}

mul m(MOD);
add a(MOD);
sub s(MOD);


int modInverse(int base, int mod){
    return power(base, mod-2, mul(MOD));
}


const int BASE=128, INV=modInverse(BASE,MOD);
char str[N];

int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
    int h1=0, h2=0, p=1;
    int k;
    scanf("%d %s",&k, str);
    for(int i=0, j=k-1; i<k; i++,j--){
        h1=m(h1, BASE);
        h1=a(h1,str[i]);
        h2=m(h2, BASE);
        h2=a(h2, str[j]);
        if(i) p=m(p,BASE);
    }
    int res=0;
    for(int i=k, j=0; str[i-1]; i++,j++){
        res+=h1==h2;
        h1=s(h1, m(p, str[j]));
        h1=m(h1, BASE);
        h1=a(h1, str[i]);

        h2=s(h2, str[j]);
        h2=m(h2, INV);
        h2=a(h2, m(p, str[i]));
    }
    cout<<res<<'\n';
  return 0;
}
