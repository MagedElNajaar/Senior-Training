//https://vjudge.net/contest/497040#problem/A

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
void Nxt(long long&a,long long&b,const long long q){
    long long t=a-q*b;
    a=b;
    b=t;
}
long long egcd(long long r0,long long r1,long long&x0,long long&y0){
    long long y1=x0=1;
    long long x1=y0=0;
    while(r1){
        long long q=r0/r1;
        Nxt(r0,r1,q);
        Nxt(x0,x1,q);
        Nxt(y0,y1,q);
    }
    return r0;
}
bool solve_lde(long long a,long long b,long long c,long long&x,long long&y,long long&g){
    g=egcd(a,b,x,y);
    if(g<0)g*=-1,x*=-1,y*=-1;
    long long m=c/g;
    x*=m;
    y*=m;
    return !(c%g);
}
long long mod(long long x,long long m){
    long long res=x%m;
    if(res<0)res+=m;
    return res;
}
bool CRT(long long m1,long long r1,long long m2,long long r2,long long&m,long long&r){
    long long q1,q2,g;
    if(!solve_lde(m1,-m2,r2-r1,q1,q2,g))return 0;
   // if(g<0)g*=-1,q1*=-1,q2*=-1;
    q1=mod(q1,m2/g);
    m=m1/g*m2;
    r=mod((r1+q1*m1),m);
    return 1;
}
bool CRT(const vector<long long>&m,const vector<long long>&r,long long&M,long long&R){
    M=m[0],R=r[0];
    for(int i=1;i<5;i++){
        if(!CRT(M,R,m[i],r[i],M,R))return 0;
    }
    return 1;
}
int INIT[5005],nxt[5005],cid[5005],vis[5005],pos[5005],sz[5005],vid;
string convert(long long x){
    string s="";
    while(x){
        s+=char('0'+(x%10));
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("cards.in","r",stdin);
    //freopen("cards.my_out","w",stdout);
    int n;
    while(cin>>n,n){
        vid++;
        for(int k=0,i=0;i<3;i++){
            for(int j=0;j<n;j++){
                nxt[5*j+2*i]=k++;
                if(i<2)nxt[5*j+2*i+1]=k++;
            }
        }
        for(int i=0,num=0;i<5*n;i++){
            if(vis[i]==vid)continue;
            int j=i;
            sz[num]=0;
            do{
                cid[j]=num;
                vis[j]=vid;
                pos[j]=(sz[num]++);
                j=nxt[j];
            }while(j!=i);
            num++;
        }
        for(int i=0,x;i<5*n;i++){
            cin>>x;
            INIT[x]=i;
        }
        long long mn=LLONG_MAX,player=-1;
        int perm[]={1,2,3,4,5};
        do{
            for(int p=0;p<n;p++){
                vector<long long>m(5),r(5);

                for(int i=0;i<5;i++){
                    int st=INIT[perm[i]],en=5*p+i,c=cid[st];
                    if(c!=cid[en]){
                        m.clear();
                        break;
                    }
                    m[i]=sz[c];
                    r[i]=mod(pos[st]-pos[en],sz[c]);
                }
                long long M,R;
                if(m.size()&&CRT(m,r,M,R)){
                    if(R==0)R=M;
                    if(R<mn){
                        mn=R;
                        player=p;
                    }
                }
            }
        }while(next_permutation(perm,perm+5));
        if(~player)cout<<"Player "<<player+1<<" wins game number "<<mn<<".\n";
        else cout<<"Neverending game.\n";
    }
    return 0;
}
