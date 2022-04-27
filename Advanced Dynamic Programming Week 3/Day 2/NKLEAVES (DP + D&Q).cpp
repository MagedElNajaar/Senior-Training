#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int N = 1e5 + 9;
const ll OO = 0x3f3f3f3f3f3f3f3f;

ll dp[2][N];
int leaves[N], n, K;
ll sum1[N], sum2[N];

void solveRow(int k, int s, int e, int mn, int mx) {
    if (e < s) return;
    ll cost = 0;
    int st = (e + s) / 2;
    int best;
    ll &ref = dp[k & 1][st];
    ref = OO;
    for (int ed = mn; ed <= mx; ed++) {
        //cost += (ed - st) * leaves[ed];
        cost = sum1[ed] - sum1[st - 1] - st * (sum2[ed] - sum2[st - 1]) + dp[(k - 1) & 1][ed + 1];
        if (ref > cost) {
            ref = cost;
            best = ed;
        }
    }
    solveRow(k, s, st - 1, mn, best);
    solveRow(k, st + 1, e, best, mx);
}

ll solve() {
    fill(dp[0] + 1, dp[0] + n + 1, OO);
    dp[0][n + 1] = 0;
    for (int k = 1; k <= K; k++) {
        solveRow(k, 1, n, 1, n);
    }
    return dp[K & 1][1];
}

int main() {

    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &leaves[i]);
        sum1[i] = sum1[i - 1] + i * leaves[i];
        sum2[i] = sum2[i - 1] + leaves[i];
    }
    printf("%lld\n", solve());
    return 0;
}
