//https://vjudge.net/problem/UVA-10304
#include <bits/stdc++.h>

using namespace std;
int dp[251][251], vis[251][251], vid;
int freq[251];

int solve(int s, int e) {
    if (s > e) return 0;
    int &ret = dp[s][e];
    if (vis[s][e] == vid) return ret;
    vis[s][e] = vid;
    ret = INT_MAX;
    for (int i = s; i <= e; i++) {
        int cur = solve(s, i - 1) + solve(i + 1, e) + freq[i-1] - freq[s-1] + freq[e] - freq[i];
        ret = min(cur, ret);
    }
    return ret;
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        vid++;
        for (int i = 1; i <= n; i++)
            scanf("%d", &freq[i]),freq[i] += freq[i-1];
        printf("%d\n", solve(1, n));
    }
    return 0;
}
