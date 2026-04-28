//https://vjudge.net/problem/LightOJ-1139
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<int>> matrix;
const int N=2e3+3,M=2e6+3,MOD=1e4;
int en_code(const matrix &m){
    int ret=0;
    for(auto &row:m){
        for(auto &cel:row){
            ret*=10;
            ret+=cel;
        }
    }
    return ret;
}
matrix de_code(int x){
    matrix ret(3,vector<int>(3));
    for (int i = 2; i>=0 ;--i) {
        for (int j = 2; j >=0 ; --j) {
            ret[i][j]=x%10;
            x/=10;
        }
    }
    return ret;
}
pair<int,int> find0(const matrix &m){
    for (int i = 2; i>=0 ;--i) {
        for (int j = 2; j >=0 ; --j) {
            if(!m[i][j])
                return {i,j};
        }
    }
}
bool valid(int i,int j){
    return i>=0&&j>=0&&i<3&&j<3;
}
vector<int> Get_neb(int x){
    auto m= de_code(x);
    int i,j;
    tie(i,j)=find0(m);
    int di=0,dj=-1;
    vector<int>ret;
    for (int k = 0; k <4 ; ++k) {
        int ni=i+di,nj=j+dj;
        if(valid(ni,nj)){
            swap(m[i][j],m[ni][nj]);
            ret.push_back(en_code(m));
            swap(m[i][j],m[ni][nj]);
        }
        swap(di,dj);
        if(k==1)dj=1;
    }
    return ret;
}
unordered_map<int,int>mem;
void bfs(){
    queue<int>q;
    int g=123456780,s;
    q.push(g);
    mem[g]=0;
    for (int steps = 1; s=q.size() ; ++steps) {
        while(s--){
            for (auto v:Get_neb(q.front())){
                if(!mem.emplace(v,steps).second) continue;
                q.push(v);
            }
            q.pop();
        }
    }
}
int main() {
    bfs();
    matrix ret(3,vector<int>(3));
    int tc,t=0;
    cin>>tc;
    while(tc--){
        cout<<"Case "<<++t<<": ";
        for (int i = 0; i <3 ; ++i) {
            for (int j = 0; j <3 ; ++j) {
                cin>>ret[i][j];
            }
        }
        auto it=mem.find(en_code(ret));
        if(it==mem.end())
            cout<<"impossible\n";
        else cout<<it->second<<'\n';
    }
}
