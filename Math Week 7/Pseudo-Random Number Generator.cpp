//https://vjudge.net/contest/497040#problem/C

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
using namespace std;
const long long m=1LL<<40,pre_sz=350125310,cycle_sz=182129209,cnt_pre=175147925,cnt_cycle=91029304,cycle_bsz=4235563,before_bsz=35012531;
long long nxt(long long s){
    return (s+(s>>20)+12345)%m;
}
vector<pair<ll,ll>>_pre_cycle,_cycle;
void floyed(ll s0,ll&cnt,ll&num,ll&cnt_before,ll&num_before,ll&t){
    long long h=s0;t=s0;
    cnt=num=0;
    do{
        t=nxt(t);
        h=nxt(nxt(h));
    }while(t!=h);
    t=s0;
    do{
        if(!(cnt++%before_bsz))_pre_cycle.push_back({t,num});
        if(!(t&1))num++;
        t=nxt(t);
        h=nxt(h);
    }while(t!=h);
    cnt_before=cnt;
    num_before=num;
    cnt=num=0;
    do{
        if(!(cnt++%cycle_bsz))_cycle.push_back({t,num});
        if(!(t&1))num++;
        t=nxt(t);
    }while(t!=h);
}
pair<long long,long long>pre_cycle[]={
{ 1611516670,0 },
{ 120410903315,17523209 },
{ 1273471303,35055207 },
{ 117327198679,52584333 },
{ 943749230,70103052 },
{ 114307527999,87600494 },
{ 622001778,105119641 },
{ 111358905960,122648127 },
{ 307559631,140161962 },
{ 108465637480,157664636 }
};
pair<long long,long long>cycle[]={
{ 516914,0 },
{ 722172600894,2105942 },
{ 472806346872,4225186 },
{ 308052742172,6339898 },
{ 199176534330,8449319 },
{ 127227408650,10573250 },
{ 79682903349,12688489 },
{ 48262896011,14808790 },
{ 27500466030,16932739 },
{ 13782170500,19045274 },
{ 4716642344,21170144 },
{ 989997476217,23282006 },
{ 649789949201,25394305 },
{ 424988001815,27517285 },
{ 276449470830,29618421 },
{ 178287584026,31742469 },
{ 113420534293,33858590 },
{ 70557864520,35973712 },
{ 42235873330,38084776 },
{ 23518397683,40202723 },
{ 11151250295,42329130 },
{ 2978382196,44443032 },
{ 891283115538,46561900 },
{ 584562375724,48678967 },
{ 381898866767,50800656 },
{ 247973655048,52924892 },
{ 159470644093,55027943 },
{ 100991179524,57158965 },
{ 62346294230,59278764 },
{ 36809250290,61405488 },
{ 19932696632,63523140 },
{ 8780872696,65652213 },
{ 1412395593,67764883 },
{ 802352025774,69875475 },
{ 525825041052,71996291 },
{ 343068616732,74106809 },
{ 222306669521,76219240 },
{ 142517114866,78341016 },
{ 89783302557,80449615 },
{ 54941087530,82573763 },
{ 31915803012,84692170 },
{ 16700026933,86806997 },
{ 6645085030,88914989 }
};
long long solve(long long n,pair<long long,long long>*arr,long long bsz){
    long long q=n/bsz,r=n%bsz;
    long long x=arr[q].first;
    long long res=arr[q].second;
    while(r--){
        if(!(x&1))res++;
        x=nxt(x);
    }
    return res;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin>>n;
    long long res=0;
    if(n<pre_sz){
        res=solve(n,pre_cycle,before_bsz);
    }else{
        n-=pre_sz;
        long long q=n/cycle_sz,r=n%cycle_sz;
        res=cnt_pre+q*cnt_cycle+solve(r,cycle,cycle_bsz);
    }
    cout<<res;
    return 0;
}
