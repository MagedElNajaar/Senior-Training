//https://vjudge.net/problem/SPOJ-HIST2
#include <bits/stdc++.h>

using namespace std;


int arr[20], dp[1 << 15][16];
long long dp2[1 << 15][16];
int n;

int solve(int mask, int prev) {
    if (mask == (1 << n) - 1) return arr[prev];
    int &ret = dp[mask][prev];
    if (~ret) return ret;
    ret = 0;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) continue;
        ret = max(ret, solve(mask | 1 << i, i) + abs(arr[prev] - arr[i]));
    }
    return ret;
}

long long Count(int mask, int prev) {
    if (mask == (1 << n) - 1) return  1;
    int ret = solve(mask, prev);
    long long &res = dp2[mask][prev];
    if (~res) return res;
    res = 0;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) continue;
        if (ret == solve(mask | 1 << i, i) + abs(arr[prev] - arr[i]))
            res += Count(mask | 1 << i, i);
    }
    return res;
}

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++)
            scanf("%d", arr + i);
        memset(dp, -1, sizeof dp);
        memset(dp2, -1, sizeof dp2);
        arr[n] = 0;
        printf("%d %lld\n", solve(0, n) + 2 * n, Count(0, n));
    }
    return 0;
}
