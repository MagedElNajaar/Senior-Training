//https://vjudge.net/contest/497040#problem/D

#include <bits/stdc++.h>
#include<ext/numeric>
#pragma GCC optimize("Ofast")
using namespace std;
using namespace __gnu_cxx;
typedef vector<valarray<int>>matrix;
int mod;
struct mul{
    int operator()(int a,int b){
        return (a*1LL*b)%mod;
    }
}m;
int identity_element(const mul&){
    return 1;
}
int inv(int x){
    return power(x,mod-2,mul());
}
void make_one(matrix&mat,int i,int j){
    int d=mat[i][j];
    if(d==1)return;
    int inverse=inv(d);
    mat[i]*=inverse;
    mat[i]%=mod;
}
void make_zero(matrix&mat,int i,int j,int k){
    int d=mat[i][j];
    if(!d)return;
    mat[i]+=mod-(mat[k]*d)%mod;
    mat[i]%=mod;
}
bool make_non_zero(matrix&mat,int i,int j){
    for(int k=i;k<mat.size();k++){
        if(mat[k][j]!=0){
            swap(mat[i],mat[k]);
            return 1;
        }
    }
    return 0;
}
bool gaues(matrix&mat){
    for(int i=0;i<mat.size();i++){
        if(!make_non_zero(mat,i,i))return 0;
        make_one(mat,i,i);
        for(int j=0;j<mat.size();j++){
            if(i!=j)make_zero(mat,j,i,i);
        }
    }
    return 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>mod>>s;
        int n=s.size();
        matrix mat(n,valarray<int>(n+1));
        for(int i=0;i<n;i++){
            int k=1;
            for(int j=0;j<n;j++){
                mat[i][j]=k;
                k=m(k,i+1);
            }
            mat[i][n]=(s[i]=='*'?0:s[i]-'a'+1);
        }
        gaues(mat);
        for(auto&x:mat)cout<<x[n]<<" \n"[&x==&mat.back()];

    }
    return 0;
}
