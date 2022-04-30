//https://vjudge.net/contest/490713#problem/O
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define mem(dp, num) memset(dp,num,sizeof dp);
#define memN(dp, num, n) memset(dp,num,(n)*sizeof dp[0]);
const int N = 1e5 + 9, M = 2e3 + 9, OO = 0x3f3f3f3f, MOD = 1e7;
int S[N], P[N], B[N], D[N], sorted[N];
ll dp[N];

ll solve(int ii) { //day index
    auto &ret = dp[ii];
    if (~ret) return ret;
    int i = sorted[ii];
    ret = 0;
    for (int jj = 0; jj < ii; jj++) {
        int j = sorted[jj];
        ll money = solve(jj);
        if (money < B[j]) continue;
        ll cur = money + S[j] - B[j] + (D[i] - D[j] - 1) * P[j];
        ret = max(ret, cur);
    }
    return ret;
}

int main() {
    int n, t = 0, days;
    while (scanf("%d%d%d", &n, &S[0], &days), n or S[0] or days) {
        D[n + 1] = days + 1;
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", D + i, B + i, S + i, P + i), sorted[i] = i;
        memN(dp, -1, n + 2);
        sorted[n + 1] = n + 1;
        sort(sorted, sorted + n + 1, [](int a, int b) { return D[a] < D[b]; });
        printf("Case %d: %lld\n", ++t, solve(n + 1));
    }
    return 0;
}
