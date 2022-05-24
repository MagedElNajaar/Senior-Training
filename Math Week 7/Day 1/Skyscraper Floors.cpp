//https://vjudge.net/contest/497040#problem/B

#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
using namespace std;
int n,m,st,en;
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
long long mod(long long x,long long m){
    return (x%m+m)%m;
}
bool CRT(long long m1,long long r1,long long m2,long long r2,long long&m,long long&r){
    long long q1,q2,g;
    if(!solve_lde(m1,-m2,r2-r1,q1,q2,g))return 0;
    g=abs(g);
    q1=mod(q1,m2/g);
    m=m1/g*m2;
    r=mod((r1+q1*m1),m);
    return 1;
}
bool can_meet(long long d1,long long s1,long long d2,long long s2){
    long long s,d;
    if(!CRT(d1,s1,d2,s2,d,s))return 0;
    return max(s1,s2)-s<n-s;
}
bool stop_at(int d,int s,int x){
    return x>=s&&(x%d)==(s%d);
}
struct DSU{
    int p[105],sz[105];
    void init(int n){
        iota(p,p+n,0);
        fill(sz,sz+n,1);
    }
    int operator[](int x){
        return p[x]==x?x:p[x]=(*this)[p[x]];
    }
    bool operator()(int u,int v){
        u=(*this)[u];v=(*this)[v];
        if(u==v)return 0;
        if(sz[u]>sz[v])swap(u,v);
        p[u]=v;
        sz[v]+=sz[u];
        return 1;
    }
}dsu;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m>>st>>en;
        int d[m],s[m];
        dsu.init(m+2);
        for(int i=0;i<m;i++){
            cin>>d[i]>>s[i];
            if(stop_at(d[i],s[i],st))dsu(i,m);
            if(stop_at(d[i],s[i],en))dsu(i,m+1);
            for(int j=0;j<i;j++){
                if(can_meet(d[i],s[i],d[j],s[j]))dsu(i,j);
            }
        }
        if(st==en)dsu(m,m+1);
        cout<<(dsu[m]==dsu[m+1]?"It is possible to move the furniture.\n":"The furniture cannot be moved.\n");
    }
    return 0;
}
