//https://vjudge.net/contest/490713#problem/Q
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp[0],num,n*sizeof dp[0]);
const int N = 40 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;

ll dp[N][N];

ll nCr(int n, int r) {
    if (n < 0 or r < 0) return 0;
    if (n < r) return 0;
    if (n == r or r == 0) return 1;
    ll &ret = dp[n][r];
    if (~ret) return ret;
    return ret = nCr(n - 1, r) + nCr(n - 1, r - 1);
}


int n, k;
double memo[N];

double solve(int seen) {
    if (seen == n) return 0;
    auto &ret = memo[seen];
    if (ret == ret) return ret;
    double p = nCr(seen, k) * 1.0 / nCr(n, k), q = 0;
    for (int i = 1; i <= min(k, n - seen); i++)
        q += nCr(n - seen, i) * nCr(seen, k - i) * 1.0 / nCr(n, k) * (1 + solve(seen + i));
    //ret = q + p * (1 + ret)
    ret = (p + q) / (1 - p);
    return ret;
}

int main() {
    int t;
    mem(dp, -1);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n >> k;
        mem(memo, -1);
        printf("Case #%d: %.9lf\n", i, solve(0));
    }
    return 0;
}
