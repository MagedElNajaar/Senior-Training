//https://vjudge.net/problem/SPOJ-LINEGAR
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 9;
int dp[N][5][5][5];
int m;

int solve(int n, int d, int minD, int maxD) {
    if (maxD - minD > 2) return 0;
    if (!n) return 1;
    int &ret = dp[n][d][minD][maxD];
    if (~ret) return ret;
    int op1 = solve(n - 1, d - 1, min(minD, d - 1), maxD);
    int op2 = solve(n - 1, d + 1, minD, max(maxD, d + 1));
    return ret = (op1 + op2) % m;
}

char str[N];

int main() {
    memset(dp, -1, sizeof(dp));
    int n, d = 2, minD = 2, maxD = 2, ret = 1;
    scanf("%d%d%s", &n, &m, str);
    for (char *s = str; *s; s++) {
        if (*s == 'P') {
            ret += solve(n - 1, d - 1, min(minD, d - 1), maxD);
            ret %= m;
            maxD = max(maxD, ++d);
        } else
            minD = min(minD, --d);
        n--;
    }
    cout << ret << "\n";
    return 0;
}
