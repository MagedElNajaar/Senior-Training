// problem link: https://vjudge.net/problem/SPOJ-LPS
#include<bits/stdc++.h>
#include<ext/numeric>
#define FIO ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;

const int MOD=1e9+7, OO=0x3f3f3f3f;
const ll LOO=0x3f3f3f3f3f3f3f3f;
const long double EPS=1e-8;


const int N=5e5+5, M=1e3+5;


char str[N];
int p[N];

void extend(){
    int n=strlen(str);
    str[(n+1)*2+1]=0;
    for(int i=(n+1)*2; i; i-=2){
        str[i]=str[n--];
        str[i-1]='#';
    }
    str[0]='$';
}


void manasher(){
    extend();
    int m=p[0]=0;
    for(int i=1; str[i]; i++){
        int mirror=2*m-i;
        int &curr=p[i]=p[mirror];
        curr=min(curr, m+p[m]-i);
        while(str[i+curr+1]==str[i-curr-1]) curr++;
        if(p[i]+i>p[m]+m) m=i;
    }
}


int main(){
  FIO 
  // freopen("input.txt","rt",stdin);
  // freopen("output.txt","wt",stdout);
    int n;
    scanf("%d %s", &n, str);
    manasher();
    printf("%d\n", *max_element(p,p+strlen(str)));



  return 0;
}
