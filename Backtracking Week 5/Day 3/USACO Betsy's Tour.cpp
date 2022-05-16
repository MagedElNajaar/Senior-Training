//To read Problem: https://www.shuzhiduo.com/A/obzb8QNb5E/
//To Solve Problem: https://vjudge.net/problem/计蒜客-T3533

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;

int grid[9][9];
bool vis[9][9];
int res, numOfVis, n;

int visited(int i ,int j,int v,int &si,int &sj) {
    vis[i][j] = v == 1;
    numOfVis += v;
    int di = 0, dj = -1;
    int cnt = 0;
    for (int k = 0; k < 4; k++) {
        int ni = i + di;
        int nj = j + dj;
        if(!vis[ni][nj]){
            grid[ni][nj] -= v;
            if(grid[ni][nj] == 1 and (ni != n or nj != 1)){
                cnt++;
                si = ni;
                sj = nj;
            }
        }
        swap(di, dj);
        if (k == 1) dj = 1;

    }
    return cnt;
}

void BT(int i, int j) {
    if (numOfVis + 1 == n * n) {
        res++;
        return;
    }
    int si,sj;
    int ret = visited(i, j, 1,si,sj);
    if(ret == 1){
        BT(si,sj);
        visited(i,j,-1,si,sj);
        return;
    }
    if(ret == 2){
        visited(i,j,-1,si,sj);
        return;
    }
    int di = 0, dj = -1;
    for (int k = 0; k < 4; k++) {
        int ni = i + di;
        int nj = j + dj;
         if(!vis[ni][nj]) BT(ni,nj);
        swap(di, dj);
        if (k == 1) dj = 1;
    }
    visited(i,j,-1,si,sj);

}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        vis[0][i] = vis[n + 1][i] = vis[i][0] = vis[i][n + 1] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int di = 0, dj = -1;
            for (int k = 0; k < 4; k++) {
                int ni = i + di;
                int nj = j + dj;
                grid[i][j] += !vis[ni][nj];
                swap(di, dj);
                if (k == 1) dj = 1;
            }
        }
    }
    BT(1, 1);
    cout << res << endl;
    return 0;
}
