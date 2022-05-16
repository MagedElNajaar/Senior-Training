//https://vjudge.net/contest/495976#problem/I

#include <bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int primes[N],lpf[N],sz;

void sieve(int N){
    lpf[0]=lpf[1]=1;
    for(int i=2;i<N;i++){
        if(!lpf[i])lpf[i]=i,primes[sz++]=i;
        for(int j=0;j<sz&&primes[j]*i<N&&primes[j]<=lpf[i];j++){
            lpf[primes[j]*i]=primes[j];
        }
    }
}
int read_int(){
    int x;
    scanf("%d",&x);
    return x;
}
int isComp[100005],vid;
int main(){
    sieve(32000);
    int t=read_int();
    while(t--){
        vid++;
        int l,r;
        cin>>l>>r;
        for(int i=0;primes[i]<=r/primes[i];i++){
            for(int j=max(2*primes[i],(l+primes[i]-1)/primes[i]*primes[i]);j<=r;j+=primes[i]){
                isComp[j-l]=vid;
            }
        }
        for(int i=max(l,2);i<=r;i++)if(isComp[i-l]!=vid)printf("%d\n",i);
        puts("");
    }
    return 0;
}
