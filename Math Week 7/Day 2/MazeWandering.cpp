//https://vjudge.net/contest/497040#problem/E
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
typedef vector<valarray<double>> matrix;
const double EPS=1e-15;
int cmp(double a,double b){
    if(fabs(a-b)<EPS)return 0;
    return (a>b)*2-1;
}
void make_one(matrix&mat,int i,int j){
    double d=mat[i][j];
    if(!cmp(d,1))return;
    mat[i]*=1.0/d;
}
void make_zero(matrix&mat,int i,int j,int k){
    double d=mat[i][j];
    if(!cmp(d,0))return;
    mat[i]-=d*mat[k];
}
bool make_non_zero(matrix&mat,int i,int j){
    for(int k=i;k<mat.size();k++){
        if(cmp(mat[k][j],0)){
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
struct MazeWandering{
    double expectedTime(vector<string>grid){
        int n=grid.size(),m=grid[0].size(),cnt=0,ci,cj;
        vector<vector<int>>id(n,vector<int>(m));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]!='X')id[i][j]=cnt++;
                if(grid[i][j]=='*')ci=i,cj=j;
            }
        }
        matrix mat(cnt,valarray<double>(0.0,cnt+1));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]!='X'){
                    int di=0,dj=-1,my_id=id[i][j];
                    mat[my_id][my_id]=1.0;
                    if(my_id==id[ci][cj])continue;
                    vector<int>v;
                    for(int k=0;k<4;k++){
                        int ni=i+di,nj=j+dj;
                        if(ni>=0&&ni<n&&nj>=0&&nj<m&&grid[ni][nj]!='X'){
                            v.push_back(id[ni][nj]);
                        }
                        swap(di,dj);
                        if(k==1)dj=1;
                    }
                    for(auto&x:v)mat[my_id][x]=-1.0/v.size();
                    mat[my_id][cnt]=1.0;
                }
            }
        }
        gaues(mat);
        double res=0.0;
        for(auto&x:mat)res+=x[cnt];
        res/=cnt;
        return res;
    }
};
