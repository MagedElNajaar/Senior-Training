//https://vjudge.net/contest/495976#problem/N

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
void nxt(long long&a,long long&b,const long long q){
    long long t=a-q*b;
    a=b;
    b=t;
}
long long egcd(long long r0,long long r1,long long&x0,long long&y0){
    long long y1=x0=1;
    long long x1=y0=0;
    while(r1){
        long long q=r0/r1;
        nxt(r0,r1,q);
        nxt(x0,x1,q);
        nxt(y0,y1,q);
    }
    return r0;
}
bool solve_lde(long long a,long long b,long long c,long long&x,long long&y,long long&g){
    g=egcd(a,b,x,y);
    long long m=c/g;
    x*=m;
    y*=m;
    return !(c%g);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long a,b,c,x,y,g;
    cin>>a>>b>>c;
    if(solve_lde(a,b,-c,x,y,g))cout<<x<<" "<<y;
    else cout<<"-1";

    return 0;
}
