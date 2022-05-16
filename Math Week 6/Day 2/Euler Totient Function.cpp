//https://vjudge.net/contest/495976#problem/H

/*
phi() calculate phi function for sungle number in O(Sqrt(N))
				  phi_to_n() calculate phi function to all numbers from 1 to N in O(NloglogN) using sieve
				  mod_inv_prime(int x,int mod) return the inverse to x if mod is prime in O(log(mod));
				  mod_inv(int x,int mod) return the inverse to x with any mod (even if it's not prime) if it's exist 
				  in O(log(mod) + (phi calculation complexity))
*/


#include <bits/stdc++.h>
#include <ext/numeric>
using namespace __gnu_cxx;
using namespace std;
const int N=1e6+1;
int Phi[N];
int phi(int n){
    int res=n;
    for(int i=2;i<=n/i;i++){
        if(n%i)continue;
        res-=res/i;
        while(n%i==0)n/=i;
    }
    if(n>1)res-=res/n;
    return res;
}
void phi_to_n(){
    iota(Phi,Phi+N,0);
    for(int i=2;i<N;i++){
        if(Phi[i]==i){
            for(int j=i;j<N;j+=i)Phi[j]-=Phi[j]/i;
        }
    }
}
struct mul{
    int mod;
    mul(int mod):mod(mod){}
    int operator()(int a,int b){
        return (a*1LL*b)%mod;
    }
};
int identity_element(const mul&){
    return 1;
}
int mod_inv_prime(int x,int mod){
    return power(x,mod-2,mul(mod));
}
int mod_inv(int x,int mod){
    if(__gcd(x,mod)>1)return -1;
    return power(x,phi(mod)-1,mul(mod));
}
int read_int(){
    int x;
    scanf("%d",&x);
    return x;
}
int main(){
    int t=read_int();
    phi_to_n();
    while(t--){
        int n=read_int();
        cout<<Phi[n]<<"\n";
    }
    return 0;
}
