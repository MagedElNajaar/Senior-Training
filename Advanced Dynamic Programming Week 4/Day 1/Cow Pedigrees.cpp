// Usaco Problem: nocows
// To read Problem use this link: https://vjudge.net/problem/UESTC_old-1135
// To Submit Problem use this link: https://vjudge.net/problem/洛谷-P1472

/*
 TASK: nocows
 LANG: C++17
 */
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 200 + 9, M = 100 + 9, OO = 0x3f3f3f3f, MOD = 9901;
int dp[N][M], dp2[N][M];

int countEqual(int n, int h);

int countLess(int n, int h) {
    if (h == 0) return !n;
    int &ret = dp[n][h];
    if (~ret) return ret;
    ret = 0;
    for (int i = 1; i < h; i++) {
        ret += countEqual(n, i);
        if (ret >= MOD) ret -= MOD;
    }
    return ret;
}

int countEqual(int n, int h) {
    if (h == 1) return n == 1;
    int &ret = dp2[n][h];
    if (~ret) return ret;
    ret = 0;
    for (int i = 1, j; j = n - i - 1, j >= i; i += 2) {
        int cnt = countEqual(i, h - 1) * countLess(j, h - 1) % MOD;
        cnt += countLess(i, h - 1) * countEqual(j, h - 1) % MOD;
        if (cnt >= MOD) cnt -= MOD;
        cnt += countEqual(i, h - 1) * countEqual(j, h - 1) % MOD;
        if (cnt >= MOD) cnt -= MOD;
        ret += cnt;
        if (ret >= MOD) ret -= MOD;
        if (i < j) {
            ret += cnt;
            if (ret >= MOD) ret -= MOD;
        }
    }
    return ret;
}

int main() {
    //freopen("nocows.in","rt",stdin);
    //freopen("nocows.out","wt",stdout);
    int n, h;
    scanf("%d%d", &n, &h);
    mem(dp, -1);
    mem(dp2, -1);
    printf("%d\n", countEqual(n, h));

    return 0;
}
